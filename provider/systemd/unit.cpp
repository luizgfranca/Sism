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