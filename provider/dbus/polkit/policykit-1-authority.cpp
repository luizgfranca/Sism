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

#include "policykit-1-authority.h"
#include "../connection.h"
#include "properties.h"
#include "./interface-properties.h"
#include "method-names.h"
#include "dto/check-authorization-request.h"
#include "dto/check-authorization-result.h"
#include <map>
#include <sdbus-c++/Types.h>
#include <sys/types.h>

using namespace provider::dbus::polkit;

PolicyKit1Authority::PolicyKit1Authority() {
    sdbus::IConnection& connection = DBusConnection::instance().get_system_bus_connection();
    
    this->proxy = sdbus::createProxy(
        connection,
        DESTINATION_NAME, 
        OBJECT_PATH
    );

    proxy->finishRegistration();
}

authority::polkit_authorization_result_t PolicyKit1Authority::checkAuthorization(
    std::string action_id,
    std::map<std::string, std::string> details,
    CheckAuthorizationFlags flags
) {
    authority::polkit_subject_value_t bus_name_value    ;

    bus_name_value["name"] = DBusConnection::instance()
        .get_system_bus_connection()
        .getUniqueName();

    authority::polkit_subject_t subject = {"system-bus-name", bus_name_value};

    authority::polkit_authorization_result_t result;
    proxy->callMethod(authority::method::CHECK_AUTHORIZATION)
        .onInterface(authority::INTERFACE_NAME)
        .withArguments(
            subject, 
            action_id, 
            details,
            (u_int32_t) flags,
            ""
        )
        .storeResultsTo(result);

    return result;
}