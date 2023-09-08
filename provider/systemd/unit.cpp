#include "unit.h"
#include <algorithm>
#include <memory>
#include "../module/string-tools/to-uppercase.h"

using namespace provider::systemd;

std::unique_ptr<std::vector<Unit>> Unit::from_dbus_list_units_response(
    provider::dbus::systemd::dto::list_units_response_t response
) {
    auto list = std::make_unique<std::vector<Unit>>();

    for (auto item : response) {
        Unit unit(item.get<0>(),
            item.get<1>(),
            item.get<2>(),
            item.get<3>(),
            item.get<4>(),
            item.get<5>(),
            item.get<6>()
        );

        if(item.get<8>() != "") {
            Job running_job(
                item.get<7>(),
                item.get<8>(),
                item.get<9>()
            );
            unit.set_running_job(running_job);
        }

        list->push_back(unit);
    }

    return std::move(list);
}

void Unit::sort_by_name_inplace(std::shared_ptr<std::vector<Unit>> units) {
    std::sort(
        units->begin(), 
        units->end(),
        [](Unit a, Unit b) {
            return string_tools::to_uppercase(b.name) > string_tools::to_uppercase(a.name);
        }
    );
}

std::shared_ptr<std::vector<Unit>> Unit::filter_by_type(std::shared_ptr<std::vector<Unit>> units, std::string type) {
    auto filtered_list = std::make_shared<std::vector<Unit>>();

    for(auto unit : *units) {
        if(unit.name.ends_with("." + type)) {
            filtered_list->push_back(unit);
        }
    }

    return filtered_list;
}