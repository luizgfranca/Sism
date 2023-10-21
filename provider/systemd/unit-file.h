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


#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "../dbus/systemd/dto/dto.h"


namespace provider::systemd {
    class UnitFile {
    public:
        std::string name;
        std::string containing_folder;
        std::string complete_path;
        std::string enabled_status;

        UnitFile(
            std::string name,
            std::string containing_folder,
            std::string complete_path,
            std::string enablement_status
        ):
            name(name),
            containing_folder(containing_folder),
            complete_path(complete_path),
            enabled_status(enablement_status) {}

        static UnitFile from_list_unit_file_response_item(dbus::systemd::list_unit_files_response_unit_file_t& unit_file);
        static std::vector<UnitFile> from_list_unit_file_response(dbus::systemd::list_unit_files_response_t& response);
        static void sort_by_name_inplace(std::shared_ptr<std::vector<UnitFile>> unit_files);
    };
}
