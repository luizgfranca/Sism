#include "../client/dbus/systemd/systemd-manager.h"
#include <memory>

namespace application {
    class State { 
        client::dbus::systemd::SystemdManager* m_systemd_manager;
        client::dbus::systemd::list_units_response_t m_units_list;
        
        void load();
    public:
        State(client::dbus::systemd::SystemdManager& systemd_manager);
        void refresh();
        client::dbus::systemd::list_units_response_t& get_units_list();
        client::dbus::systemd::list_units_response_t& get_services_list();
    };
}
