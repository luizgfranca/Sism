#include "unit-operation-mode.h"

using namespace provider::dbus::systemd::dto;

const std::string start_unit_mode_strs[] = {
    "replace",
    "fail",
    "isolate",
    "ignore-dependencies",
    "ignore-requirements"
};

std::string provider::dbus::systemd::dto::to_string(UnitOperationMode mode) {
    return start_unit_mode_strs[mode];
}