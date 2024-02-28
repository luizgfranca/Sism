/*
 *   SISM - Services manager for GNU/Linux based operating systems
 *   Copyright (C) 2024 Luiz Gustavo <luizgfc@proton.me>
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
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include "dto/check-authorization-result.h"
#include "dto/check-authorization-flags.h"

namespace provider::dbus::polkit {

    class PolicyKit1Authority {
        std::unique_ptr<sdbus::IProxy> proxy;
    public:
        PolicyKit1Authority();
        authority::polkit_authorization_result_t checkAuthorization(
            std::string action_id,
            std::map<std::string, std::string> details = {},
    CheckAuthorizationFlags flags = CheckAuthorizationFlags::ALLOW_USER_INTERACTION
        );
    };
}