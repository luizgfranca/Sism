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
#include "polkit-authorization.h"
#include "../dbus/polkit/policykit-1-authority.h"

namespace provider::polkit {
    class PolkitProvider {
        std::unique_ptr<dbus::polkit::PolicyKit1Authority> m_polkit_authority_interface;
    public:
        PolkitProvider();

        // returns if the action was authorized
        bool request_authorization(PolkitAction action);
    };
}