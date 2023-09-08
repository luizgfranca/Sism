#include <string>
namespace provider::dbus::systemd::manager::method {
    const std::string LIST_UNITS_METHOD = "ListUnits";
    const std::string STOP_UNIT_METHOD = "StopUnit";
    const std::string START_UNIT_METHOD = "StartUnit";
    const std::string RELOAD_OR_RESTART_UNIT_METHOD = "ReloadOrRestartUnit";
}