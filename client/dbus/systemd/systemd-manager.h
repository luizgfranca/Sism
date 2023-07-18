#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/Types.h>

namespace client::dbus::systemd {
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
    > list_units_response_t;


    class SystemdManager {
        std::unique_ptr<sdbus::IProxy> proxy;
    public:
        SystemdManager();
        list_units_response_t list_units();
        void stop_unit(std::string unit_name);
    };
}