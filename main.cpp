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

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/Message.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>
#include <cstring>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include "glibmm/dispatcher.h"
#include "glibmm/refptr.h"
#include "gtkmm/application.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/headerbar.h"
#include "gtkmm/label.h"
#include "gtkmm/liststore.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/treemodel.h"
#include "gtkmm/treeview.h"
#include "sigc++/functors/mem_fun.h"
#include "sigc++/functors/ptr_fun.h"
#include <gtkmm-4.0/gtkmm.h>
#include "application/state.h"
#include "component/service-property/service-property.h"


Glib::RefPtr<Gtk::Application> global_application = nullptr;
client::dbus::systemd::SystemdManager global_systemd_manager_client;
application::State global_state(global_systemd_manager_client);

const int DEFAULT_RELOAD_WAITING_SECONDS = 1;
class MainWindow : public Gtk::Window {
private:
    class ColumnModel : public Gtk::TreeModel::ColumnRecord {
    public:
        ColumnModel() {
            add(m_service_name);
            add(m_service_status);
            add(m_service_description);
        }


        Gtk::TreeModelColumn<Glib::ustring> m_service_name;
        Gtk::TreeModelColumn<Glib::ustring> m_service_status;
        Gtk::TreeModelColumn<Glib::ustring> m_service_description;
    };

    std::thread* m_background_reloader_thread = nullptr;
    Glib::Dispatcher m_update_data_notification_dispatcher;

    Gtk::TreeView m_treeview;
    ColumnModel m_model;

    std::mutex m_tree_store_mutex;
    Glib::RefPtr<Gtk::ListStore> m_tree_store;

    Gtk::HeaderBar m_header_bar;
    Gtk::Button m_stop_button;
    Gtk::Button m_start_button;
    Gtk::Button m_restart_button;
    Gtk::Button m_refresh_button;

    component::ServiceProperty m_serviceproperty_title = component::ServiceProperty("Title:", "example.service");
    component::ServiceProperty m_serviceproperty_description = component::ServiceProperty("Description:", "Example service description");
    component::ServiceProperty m_serviceproperty_loaded = component::ServiceProperty("Loaded:", "loaded");
    component::ServiceProperty m_serviceproperty_state = component::ServiceProperty("State:", "running/start");
    component::ServiceProperty m_serviceproperty_followed = component::ServiceProperty("Following:", "other.service");
    component::ServiceProperty m_serviceproperty_object_path = component::ServiceProperty("Object path:", "?");
    
    component::ServiceProperty m_serviceproperty_job_type = component::ServiceProperty("Type:", "type");
    component::ServiceProperty m_serviceproperty_job_object_path = component::ServiceProperty("Object Path:", "type");


    void add_grid_item(std::string name, std::string status, std::string description);

public:
    MainWindow();
    void notify_data_refresh();
    void stop_service(const int line);
    void start_service(const int line);
    void restart_service(const int line);
    std::unique_ptr<Gtk::TreeModel::Path> get_current_row();
    void set_row(Gtk::TreeModel::Path& tree_path);
    void load_grid_data();
    void on_row_selection();
    void on_dataset_change();
};

void row_selected_signal_handler() {
    dynamic_cast<MainWindow*>(global_application->get_run_window())->on_row_selection();
}

MainWindow* get_main_window() {
    return dynamic_cast<MainWindow*>(global_application->get_run_window());
}

std::unique_ptr<Gtk::TreeModel::Path> get_current_row(MainWindow* main_window) {
    return main_window->get_current_row();
}

void stop_clicked_signal_handler() {
    auto main_window = get_main_window();
    auto current_row = get_current_row(main_window);
    main_window->stop_service(std::stoi(current_row->to_string()));
    sleep(DEFAULT_RELOAD_WAITING_SECONDS);
    global_state.refresh();
    main_window->load_grid_data();
    // main_window->set_row(*current_row);
}

void start_clicked_signal_handler() {
    auto main_window = get_main_window();
    auto current_row = get_current_row(main_window);
    main_window->start_service(std::stoi(current_row->to_string()));
    sleep(DEFAULT_RELOAD_WAITING_SECONDS);
    global_state.refresh();
    main_window->load_grid_data();
    // main_window->set_row(*current_row);
}

void restart_clicked_signal_handler() {
    auto main_window = get_main_window();
    auto current_row = get_current_row(main_window);
    main_window->restart_service(std::stoi(current_row->to_string()));
    sleep(DEFAULT_RELOAD_WAITING_SECONDS);
    global_state.refresh();
    main_window->load_grid_data();
    // main_window->set_row(*current_row);
}

// void background_reload(MainWindow* window) {
//     while(true) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         std::cout << "refreshing grid\n";
//         global_state.refresh();
//         window->notify_data_refresh();
//     }
// }

MainWindow::MainWindow() {
    set_title("Sism");
    set_default_size(1300, 800);

    m_tree_store_mutex.lock();
    m_tree_store = Gtk::ListStore::create(m_model);
    m_treeview.set_model(m_tree_store);
    m_tree_store_mutex.unlock();

    m_treeview.append_column("Name", m_model.m_service_name);
    m_treeview.append_column("Status", m_model.m_service_status);
    m_treeview.append_column("Description", m_model.m_service_description);

    // m_treeview.get_selection()->set_mode(Gtk::SelectionMode::SINGLE);
    m_treeview.signal_cursor_changed().connect(sigc::ptr_fun(row_selected_signal_handler));

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
    m_stop_button.signal_clicked().connect(sigc::ptr_fun(stop_clicked_signal_handler));

    m_start_button.set_label("Start");
    m_start_button.signal_clicked().connect(sigc::ptr_fun(start_clicked_signal_handler));

    m_restart_button.set_label("Restart");
    m_restart_button.signal_clicked().connect(sigc::ptr_fun(start_clicked_signal_handler));

    m_refresh_button.set_label("Refresh");
    m_refresh_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_dataset_change));

    m_header_bar.pack_end(m_stop_button);
    m_header_bar.pack_end(m_start_button);
    m_header_bar.pack_end(m_restart_button);
    m_header_bar.pack_end(m_refresh_button);
    set_titlebar(m_header_bar);

    Gtk::Box service_information_box;
    service_information_scroller.set_child(service_information_box);

    service_information_box.set_orientation(Gtk::Orientation::VERTICAL);
    service_information_box.append(*(new component::ServiceProperty("Service details", "")));
    service_information_box.append(m_serviceproperty_title);
    service_information_box.append(m_serviceproperty_description);
    service_information_box.append(m_serviceproperty_loaded);
    service_information_box.append(m_serviceproperty_state);
    service_information_box.append(m_serviceproperty_followed);
    service_information_box.append(m_serviceproperty_object_path);
    service_information_box.append(*(new component::ServiceProperty("", "")));
    service_information_box.append(*(new component::ServiceProperty("Job currently processing", "")));
    service_information_box.append(m_serviceproperty_job_type);
    service_information_box.append(m_serviceproperty_job_object_path);

    // m_background_reloader_thread = new std::thread([this]{background_reload(this);});
    // m_update_data_notification_dispatcher.connect();
}


void MainWindow::add_grid_item(std::string name, std::string status, std::string description) {
    Gtk::TreeModel::Row row = *(m_tree_store->append());
    row[m_model.m_service_name] = name;
    row[m_model.m_service_status] = status;
    row[m_model.m_service_description] = description;
}

void MainWindow::on_row_selection() {
    auto selected = m_treeview.get_selection()->get_selected_rows();

    if(selected.empty()) return;

    auto item = global_state.get_services_list()[std::stoi(selected.at(0).to_string())];
    auto service = item.get<0>();
    
    if(item.get<2>() == "not-found") {
        m_start_button.set_visible(false);
        m_restart_button.set_visible(false);
        m_stop_button.set_visible(false);
    } else {
        m_start_button.set_visible(true);
        m_restart_button.set_visible(true);
        m_stop_button.set_visible(true);
    }

    m_serviceproperty_title.set_value(item.get<0>());
    m_serviceproperty_description.set_value(item.get<1>());
    m_serviceproperty_loaded.set_value(item.get<2>());
    m_serviceproperty_state.set_value(item.get<3>() + "/" + item.get<4>());
    m_serviceproperty_followed.set_value(item.get<5>());
    m_serviceproperty_object_path.set_value(item.get<6>());
    
    if(item.get<8>() == "") {
        m_serviceproperty_job_type.set_visible(false);
        m_serviceproperty_job_object_path.set_visible(false);
    } else {
        m_serviceproperty_job_type.set_visible(true);
        m_serviceproperty_job_object_path.set_visible(true);
        m_serviceproperty_job_type.set_value(item.get<8>());
        m_serviceproperty_job_object_path.set_value(item.get<9>());
    }
}

void MainWindow::stop_service(const int line) {
    const auto name = global_state.get_services_list()[line].get<0>();
    global_systemd_manager_client.stop_unit(name);
}


void MainWindow::start_service(const int line) {
    const auto name = global_state.get_services_list()[line].get<0>();
    global_systemd_manager_client.start_unit(name);
}


void MainWindow::restart_service(const int line) {
    const auto name = global_state.get_services_list()[line].get<0>();
    global_systemd_manager_client.reload_or_restart_unit(name);
}

std::unique_ptr<Gtk::TreeModel::Path> MainWindow::get_current_row() {
    auto selected_rows = m_treeview.get_selection()->get_selected_rows();
    if(selected_rows.size() > 0) {
        return std::make_unique<Gtk::TreeModel::Path>(selected_rows.at(0));
    }

    return nullptr;
}

void MainWindow::set_row(Gtk::TreeModel::Path& tree_path) {
    m_treeview.set_cursor(tree_path);
}

void MainWindow::load_grid_data() {

    std::cout << "load_grid_data";

    auto position = get_current_row();
    m_tree_store_mutex.lock();
    m_tree_store->clear();

    for(auto service : global_state.get_services_list()) {
        add_grid_item(service.get<0>(), service.get<4>(), service.get<1>());
    }
    m_tree_store_mutex.unlock();
    if(position) {
        set_row(*position);
    }
}

void MainWindow::on_dataset_change() {
    global_state.refresh();
    load_grid_data();
}

int main(int argc, char **argv) {
    global_application = Gtk::Application::create("io.github.luizgfranca.sism");
    global_application->make_window_and_run<MainWindow>(argc, argv);    

}

void MainWindow::notify_data_refresh() {
    m_update_data_notification_dispatcher.emit();
}