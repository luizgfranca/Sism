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


#include <thread>

#include "glibmm/dispatcher.h"
#include "gtkmm/liststore.h"
#include "gtkmm/treemodelcolumn.h"
#include "gtkmm/treeview.h"
#include "gtkmm/headerbar.h"
#include "gtkmm/window.h"

#include "component//service-property/service-property.h"
#include "../../provider/systemd/unit.h"
#include "application.h"

namespace application::ui {

    const int DEFAULT_WIDTH = 1300;
    const int DEFAULT_HEIGHT = 800;

    const int SECONDS_TO_REFRESH_DATASET_AFTER_ACTION = 1;

    class MainWindow : public Gtk::Window {
    private:
        SismApplication *m_application;

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


        void add_grid_item(const provider::systemd::Unit& unit);

    public:
        MainWindow(SismApplication *application);
        void notify_data_refresh();
        std::unique_ptr<Gtk::TreeModel::Path> get_currently_selected_row_number();
        void set_selected_row_number(Gtk::TreeModel::Path& tree_path);
        void load_grid_data();
        void reload_dataset();

        std::optional<provider::systemd::Unit> get_service_from_currently_selected_row();        
        
        void on_row_selection();
        void on_start_service_click();
        void on_stop_service_click();
        void on_restart_service_click();
        void on_refresh_service_list_click();
    };

}

