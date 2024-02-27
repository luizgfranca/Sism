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

// {
//   Boolean             is_authorized,
//   Boolean             is_challenge,
//   Dict<String,String> details
// }
   
#include <map>
#include <sdbus-c++/Types.h>

namespace provider::dbus::polkit::authority {
    typedef sdbus::Struct<
        bool,
        bool,
        std::map<std::string, std::string>
    > polkit_authorization_result_t;
}