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


#include "polkit-provider.h"
#include "polkit-authorization.h"
#include "../../module/logger/logger.h"

using namespace provider::polkit;

constexpr size_t CHECK_AUTHORIZATION__IS_AUTHORIZED_POSITION = 0;
constexpr size_t CHECK_AUTHORIZATION__IS_CHALLENGE_POSITION  = 1;
constexpr size_t CHECK_AUTHORIZATION__DETAILS_POSITION       = 2;

PolkitProvider::PolkitProvider() {
    m_polkit_authority_interface = std::make_unique<dbus::polkit::PolicyKit1Authority>();
}

bool PolkitProvider::request_authorization(PolkitAction action) {
    dbus::polkit::authority::polkit_authorization_result_t result = m_polkit_authority_interface->checkAuthorization(to_string(action));
    module::logger::debug("Polkit authorization request details", result.get<CHECK_AUTHORIZATION__DETAILS_POSITION>());

    return result.get<CHECK_AUTHORIZATION__IS_AUTHORIZED_POSITION>();
}
