#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/Message.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>
#include <cstring>
#include <string>
#include <vector>
#include "glibmm/refptr.h"
#include "gtkmm/application.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/headerbar.h"
#include "gtkmm/liststore.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/treemodel.h"
#include "gtkmm/treeview.h"
#include "sigc++/functors/ptr_fun.h"
#include <gtkmm-4.0/gtkmm.h>
#include "application/state.h"


Glib::RefPtr<Gtk::Application> global_application = nullptr;
client::dbus::systemd::SystemdManager global_systemd_manager_client;
application::State global_state(global_systemd_manager_client);

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

    Gtk::TreeView m_treeview;
    ColumnModel m_model;
    Glib::RefPtr<Gtk::ListStore> m_tree_store;

    Gtk::HeaderBar m_header_bar;
    Gtk::Button m_start_stop_button;

    void add_grid_item(std::string name, std::string status, std::string description);

public:
    MainWindow();
    void on_row_selected(const int line);
    int get_current_row();
};

void row_selected_signal_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    dynamic_cast<MainWindow*>(global_application->get_run_window())->on_row_selected(std::stoi(path.to_string()));
}

void start_stop_clicked_signal_handler() {
    std::cout << "start_stop_clicked_signal_handler\n";
    auto main_window = dynamic_cast<MainWindow*>(global_application->get_run_window());
    auto row = main_window->get_current_row();
    std::cout << "selected " << row << "\n";
    main_window->on_row_selected(row);
}

MainWindow::MainWindow() {
    set_title("Sism");
    set_default_size(1600, 800);

    m_tree_store = Gtk::ListStore::create(m_model);
    m_treeview.set_model(m_tree_store);
    m_treeview.append_column("Name", m_model.m_service_name);
    m_treeview.append_column("Status", m_model.m_service_status);
    m_treeview.append_column("Description", m_model.m_service_description);

    m_treeview.signal_row_activated().connect(sigc::ptr_fun(row_selected_signal_handler));

    Gtk::ScrolledWindow scroller;
    scroller.set_child(m_treeview);

    set_child(scroller);

    for(auto service : global_state.get_services_list()) {
        add_grid_item(service.get<0>(), service.get<4>(), service.get<1>());
    }

    m_start_stop_button.set_label("Start / Stop service");
    m_start_stop_button.signal_clicked().connect(sigc::ptr_fun(start_stop_clicked_signal_handler));

    m_header_bar.pack_end(m_start_stop_button);
    set_titlebar(m_header_bar);
}


void MainWindow::add_grid_item(std::string name, std::string status, std::string description) {
    Gtk::TreeModel::Row row = *(m_tree_store->append());
    row[m_model.m_service_name] = name;
    row[m_model.m_service_status] = status;
    row[m_model.m_service_description] = description;
}

void MainWindow::on_row_selected(const int line) {
    const auto name = global_state.get_services_list()[line].get<0>();
    std::cout << "on_row_selected  " << name << "\n";
    global_systemd_manager_client.stop_unit(name);
}

int MainWindow::get_current_row() {
    auto selected_rows = m_treeview.get_selection()->get_selected_rows();
    if(selected_rows.size() > 0) {
        return std::stoi(selected_rows[0].to_string());
    }

    return -1;
}

int main(int argc, char **argv) {
    global_application = Gtk::Application::create("io.github.luizgfranca.sism");
    return global_application->make_window_and_run<MainWindow>(argc, argv);
}