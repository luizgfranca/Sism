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


#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "job.h"
#include "../dbus/systemd/dto/dto.h"
#include "unit-file.h"


namespace provider::systemd {
    class Unit {
        bool m_has_running_job = false;
        std::shared_ptr<Job> m_running_job;
    public:
        // The primary unit name as string
        std::string name;

        // The human readable description string
        std::string description;

        // The load state (i.e. whether the unit file has been loaded successfully)
        std::string load_state;

        // The active state (i.e. whether the unit is currently started or not)
        std::string active_state;

        // The sub state (a more fine-grained version of the active state that is specific to the unit type, which the active state is not)
        std::string sub_state;

        // A unit that is being followed in its state by this unit, if there is any, otherwise the empty string
        std::string follows;

        // The unit object path
        std::string object_path;

        std::shared_ptr<UnitFile> unit_file;

        Unit(
            std::string name,
            std::string description,
            std::string load_state,
            std::string active_state,
            std::string sub_state,
            std::string follows,
            std::string object_path
        ): 
            name(name),
            description(description),
            load_state(load_state),
            active_state(active_state),
            sub_state(sub_state),
            follows(follows),
            object_path(object_path)
        {}

        Unit(
            std::string name,
            std::string description,
            std::string load_state,
            std::string active_state,
            std::string sub_state,
            std::string follows,
            std::string object_path,
            std::shared_ptr<UnitFile> unit_file
        );

        Unit(std::shared_ptr<UnitFile> unit_file): 
            name(unit_file->name),
            description("(not loaded)"),
            load_state("not-loaded"),
            active_state("inactive"),
            sub_state("inactive"),
            unit_file(unit_file)
        {}

        bool is_follower() { return !follows.empty(); }

        bool has_running_job() { return m_has_running_job; }

        void set_running_job(Job& job) {
            m_has_running_job = true;
            m_running_job = std::make_shared<Job>(job);
        }

        std::shared_ptr<Job> get_running_job() { return m_running_job; }

        
        static std::shared_ptr<std::vector<Unit>> from_dbus_list_units_response(
            provider::dbus::systemd::list_units_response_t response
        );

        static std::shared_ptr<std::vector<Unit>> from_dbus_list_units_and_list_files_response(
            provider::dbus::systemd::list_units_response_t list_units_response,
            provider::dbus::systemd::list_unit_files_response_t list_unit_files_response
        );

        static void sort_by_name_inplace(std::shared_ptr<std::vector<Unit>> units);
        
        static std::shared_ptr<std::vector<Unit>> filter_by_type(std::shared_ptr<std::vector<Unit>> units, std::string type);
    };
}
