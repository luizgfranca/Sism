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

#include <iostream>
#include <string>
#include <format>
#include <map>

namespace module::logger {
    template<typename... T>
    void debug(std::format_string<T...> __fmt, T&&... __args) {
        std::cout << "[DEBUG] " + std::format( __fmt, __args...) + "\n";
    }

    inline void debug(std::string description, std::map<std::string, std::string> dictionary) {
        std::string str = "[DEBUG] " + description + ": {\n";
        for (auto item : dictionary) {
            str += "  " + item.first + ": " + item.second + "\n";
        }
        str += "}\n";
        std::cout << str;
    }
}