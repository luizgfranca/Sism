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


//   CheckAuthorization(in  (sa{sv}) subject,
//                      in  s action_id,
//                      in  a{ss} details,
//                      in  u flags,
//                      in  s cancellation_id,
//                      out (bba{ss}) result);
#include <map>
#include <sdbus-c++/Types.h>

namespace provider::dbus::polkit::authority {
    
    // in  (sa{sv}) subject
    typedef std::map<std::string, sdbus::Variant> polkit_subject_value_t;
    typedef sdbus::Struct<
        std::string,
        polkit_subject_value_t
    > polkit_subject_t;
}