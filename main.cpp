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
#include "gtkmm/liststore.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/treemodel.h"
#include "gtkmm/treeview.h"
#include "sigc++/functors/ptr_fun.h"
#include <gtkmm-4.0/gtkmm.h>

Glib::RefPtr<Gtk::Application> global_application = nullptr;

typedef     
    std::vector<
        sdbus::Struct<
            std::string,
            std::string,
            std::string,
            std::string,
            std::string,
            std::string,
            sdbus::ObjectPath,
            uint32_t,
            std::string,
            sdbus::ObjectPath
        >
    > ListUnitsResponse;

void onConcatenated(sdbus::Signal& signal)
{
    std::string concatenatedString;
    signal >> concatenatedString;

    std::cout << "Received signal with concatenated string " << concatenatedString << std::endl;
}

ListUnitsResponse get_unit_list() {
    const char* destinationName = "org.freedesktop.systemd1";
    const char* objectPath = "/org/freedesktop/systemd1";
    const char* interfaceName = "org.freedesktop.systemd1.Manager";

    auto proxy = sdbus::createProxy(destinationName, objectPath);

    proxy->finishRegistration();

    ListUnitsResponse result;
    proxy->callMethod("ListUnits").onInterface(interfaceName).storeResultsTo(result);

    return result;
}

void stop_unit(std::string unit_name) {
    const char* destinationName = "org.freedesktop.systemd1";
    const char* objectPath = "/org/freedesktop/systemd1";
    const char* interfaceName = "org.freedesktop.systemd1.Manager";

    auto proxy = sdbus::createProxy(destinationName, objectPath);

    proxy->finishRegistration();

    sdbus::ObjectPath result;
    proxy->callMethod("StopUnit").onInterface(interfaceName).withArguments(unit_name, "replace").storeResultsTo(result);

    std::cout << "job: " << result.data() << "\n";
}


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
    ListUnitsResponse m_units_list;

    void add_grid_item(std::string name, std::string status, std::string description);

public:
    MainWindow();
    void on_row_selected(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
};

void row_selected_signal_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    dynamic_cast<MainWindow*>(global_application->get_run_window())->on_row_selected(path, column);
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

    m_units_list = get_unit_list();
    for(auto unit : m_units_list) {
        add_grid_item(unit.get<0>(), unit.get<2>(), unit.get<1>());
    }
}


void MainWindow::add_grid_item(std::string name, std::string status, std::string description) {
    Gtk::TreeModel::Row row = *(m_tree_store->append());
    row[m_model.m_service_name] = name;
    row[m_model.m_service_status] = status;
    row[m_model.m_service_description] = description;
}

void MainWindow::on_row_selected(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    const auto name = m_units_list[std::stoi(path.to_string())].get<0>();
    std::cout << "on_row_selected  " << name << "\n";
    stop_unit(name);
}

int main(int argc, char **argv) {
    global_application = Gtk::Application::create("io.github.luizgfranca.sism");
    return global_application->make_window_and_run<MainWindow>(argc, argv);
}