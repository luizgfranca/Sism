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

#include "gtkmm/box.h"
#include "gtkmm/liststore.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/treemodel.h"
#include "gtkmm/treeview.h"
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>


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

    Gtk::Box m_box;
    Gtk::TreeView m_treeview;
    Gtk::ScrolledWindow m_scrolled_window;
    ColumnModel m_model;

public:
    MainWindow() {
        set_title("Test Window");
        set_default_size(800, 800);
        set_child(m_treeview);
        // set_child(m_box);
        // m_scrolled_window.set_child(m_treeview);
        // m_box.insert_child_at_start(m_scrolled_window);


        auto store = Gtk::ListStore::create(m_model);
        m_treeview.set_model(store);

        m_treeview.append_column("Name", m_model.m_service_name);
        m_treeview.append_column("Status", m_model.m_service_status);
        m_treeview.append_column("Description", m_model.m_service_description);

        Gtk::TreeModel::Row row = *(store->append());
        row[m_model.m_service_name] = "test.service";
        row[m_model.m_service_status] = "active";
        row[m_model.m_service_description] = "My test service";
    }
};


int main(int argc, char **argv) {

    auto app = Gtk::Application::create("io.github.luizgfranca");
    return app->make_window_and_run<MainWindow>(argc, argv);
}