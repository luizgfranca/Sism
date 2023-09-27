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
#include <cstdint>
#include <memory>
#include <vector>
#include "../module/string-tools/to-uppercase.h"
#include "../module/logger/logger.h"

using namespace provider::systemd;

Unit::Unit(
    std::string name,
    std::string description,
    std::string load_state,
    std::string active_state,
    std::string sub_state,
    std::string follows,
    std::string object_path,
    std::shared_ptr<UnitFile> unit_file
) {
    auto unit = Unit(
        name,
        description,
        load_state,
        active_state,
        sub_state,
        follows,
        object_path
    );

    unit_file = unit_file;
}


std::shared_ptr<std::vector<Unit>> Unit::from_dbus_list_units_response(
    provider::dbus::systemd::list_units_response_t response
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

std::shared_ptr<std::vector<Unit>> Unit::from_dbus_list_units_and_list_files_response(
            provider::dbus::systemd::list_units_response_t list_units_response,
            provider::dbus::systemd::list_unit_files_response_t list_unit_files_response
) {
    auto raw_units = Unit::from_dbus_list_units_response(list_units_response);
    
    auto unit_files = std::make_shared<std::vector<UnitFile>>(
        UnitFile::from_list_unit_file_response(list_unit_files_response)
    );

    Unit::sort_by_name_inplace(raw_units);
    UnitFile::sort_by_name_inplace(unit_files);

    
    auto final_unit_list = std::make_shared<std::vector<Unit>>();
 
    // assumptions:
    //  - both lists are ordered
    //  - there are items in unit_files not present in the raw_units_list
    //  - there are items in raw_units not present in unit_files
    // 
    //
    // to merge the information:
    // for each item in unit_files
    //
    //   save the units in the raw_units list until the position where the unit
    //   of the unit file selected should be
    //
    //   if there is a unit in the position save the file inside the unit and 
    //   put it un the final unit list
    //   
    //   otherwise, since both lists are ordered we know that the unit file doesn't
    //   have a corresponding unit, so create a unit containing just the basic
    //   information of the unit file still not loaded and save it to the final list   
    uint32_t unit_list_position = 0;
    for(auto& file : *unit_files) {
        
        while(
            unit_list_position < raw_units->size() && 
            file.name > raw_units->at(unit_list_position).name
        ) {
            final_unit_list->push_back((Unit&) raw_units->at(unit_list_position));
            unit_list_position ++;
        }

        if(
            unit_list_position < raw_units->size() &&
            file.name == raw_units->at(unit_list_position).name
        ) {
            auto& unit = raw_units->at(unit_list_position);
            unit.unit_file = std::make_shared<UnitFile>(file);
            final_unit_list->push_back(unit);
            unit_list_position ++;
            continue;
        }
        
        auto unit = new Unit(std::make_shared<UnitFile>(file));
        final_unit_list->push_back(*unit);
        
    }

    return final_unit_list;
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