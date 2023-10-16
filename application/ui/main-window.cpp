/*
 *   SISM - Services manager for GNU/Linux based operating systems
 *   Copyright (C) 2023 Luiz Gustavo <luizgfc@proton.me>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as
 *   published by the Free Software Foundation, either version 3 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "main-window.h"
#include "gtkmm/scrolledwindow.h"
#include <optional>
#include <unistd.h>

using namespace application::ui;

MainWindow::MainWindow(SismApplication *application) {
    m_application = application;

    set_title("Sism");
    set_default_size(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    m_tree_store_mutex.lock();
    m_tree_store = Gtk::ListStore::create(m_model);
    m_treeview.set_model(m_tree_store);
    m_tree_store_mutex.unlock();

    m_treeview.append_column("Name", m_model.m_service_name);
    m_treeview.append_column("Status", m_model.m_service_status);
    m_treeview.append_column("Description", m_model.m_service_description);

    // m_treeview.get_selection()->set_mode(Gtk::SelectionMode::SINGLE);
    m_treeview.signal_cursor_changed().connect(sigc::mem_fun(*this, &MainWindow::on_row_selection));

    Gtk::ScrolledWindow service_grid_scroller;
    service_grid_scroller.set_min_content_width(850);
    service_grid_scroller.set_child(m_treeview);

    Gtk::ScrolledWindow service_information_scroller;
    service_information_scroller.set_min_content_width(450);

    Gtk::Box container;
    container.set_halign(Gtk::Align::FILL);
    container.append(service_grid_scroller);
    container.append(service_information_scroller);

    set_child(container);

    load_grid_data();

    m_stop_button.set_label("Stop");
    m_stop_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_stop_service_click));

    m_start_button.set_label("Start");
    m_start_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_start_service_click));

    m_restart_button.set_label("Restart");
    m_restart_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_restart_service_click));

    m_refresh_button.set_label("Refresh");
    m_refresh_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_refresh_service_list_click));

    m_header_bar.pack_end(m_stop_button);
    m_header_bar.pack_end(m_start_button);
    m_header_bar.pack_end(m_restart_button);
    m_header_bar.pack_end(m_refresh_button);
    set_titlebar(m_header_bar);

    service_information_scroller.set_child(m_service_details_section);
}


void MainWindow::reload_dataset() {
    m_application->system_services_controller().refresh();
    load_grid_data();    
}

void MainWindow::add_grid_item(const provider::systemd::Unit& unit) {
    Gtk::TreeModel::Row row = *(m_tree_store->append());
    row[m_model.m_service_name] = unit.name;
    row[m_model.m_service_status] = unit.sub_state;
    row[m_model.m_service_description] = unit.description;
}


void MainWindow::on_row_selection() {
    auto maybe_item = get_service_from_currently_selected_row();
    if(!maybe_item.has_value()) return;

    auto item = maybe_item.value();

    if(item.load_state == "not-found") {
        m_start_button.set_visible(false);
        m_restart_button.set_visible(false);
        m_stop_button.set_visible(false);
    } else {
        m_start_button.set_visible(true);
        m_restart_button.set_visible(true);
        m_stop_button.set_visible(true);
    }

    m_service_details_section.set_service(item);
}

std::optional<provider::systemd::Unit> MainWindow::get_service_from_currently_selected_row() {
    auto selected_rows = m_treeview.get_selection()->get_selected_rows();
    if(selected_rows.empty()) return std::nullopt;

    auto item = (*m_application->system_services_controller().get_services())[std::stoi(selected_rows.at(0).to_string())];
    
    return std::make_optional(item);
}

void MainWindow::on_stop_service_click() {
    auto maybe_service = get_service_from_currently_selected_row();
    if(!maybe_service.has_value()) return;

    m_application->system_services_controller().stop(maybe_service.value());

    sleep(SECONDS_TO_REFRESH_DATASET_AFTER_ACTION);
    reload_dataset();
}


void MainWindow::on_start_service_click() {
    auto maybe_service = get_service_from_currently_selected_row();
    if(!maybe_service.has_value()) return;

    m_application->system_services_controller().start(maybe_service.value());
    
    sleep(SECONDS_TO_REFRESH_DATASET_AFTER_ACTION);
    reload_dataset();
}


void MainWindow::on_restart_service_click() {
    auto maybe_service = get_service_from_currently_selected_row();
    if(!maybe_service.has_value()) return;

    m_application->system_services_controller().restart(maybe_service.value());

    sleep(SECONDS_TO_REFRESH_DATASET_AFTER_ACTION);
    reload_dataset();
}

std::unique_ptr<Gtk::TreeModel::Path> MainWindow::get_currently_selected_row_number() {
    auto selected_rows = m_treeview.get_selection()->get_selected_rows();
    if(selected_rows.size() > 0) {
        return std::make_unique<Gtk::TreeModel::Path>(selected_rows.at(0));
    }

    return nullptr;
}

void MainWindow::set_selected_row_number(Gtk::TreeModel::Path& tree_path) {
    m_treeview.set_cursor(tree_path);
}

void MainWindow::load_grid_data() {
    auto position = get_currently_selected_row_number();
    m_tree_store_mutex.lock();
    m_tree_store->clear();

    for(auto service : *m_application->system_services_controller().get_services()) {
        add_grid_item(service);
    }

    m_tree_store_mutex.unlock();
    if(position) {
        set_selected_row_number(*position);
    }
}

void MainWindow::on_refresh_service_list_click() {
    m_application->system_services_controller().refresh();
    load_grid_data();
}

void MainWindow::notify_data_refresh() {
    m_update_data_notification_dispatcher.emit();
}