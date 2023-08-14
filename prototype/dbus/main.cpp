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

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/Message.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>
#include <cstring>
#include <string>
#include <vector>


void onConcatenated(sdbus::Signal& signal)
{
    std::string concatenatedString;
    signal >> concatenatedString;

    std::cout << "Received signal with concatenated string " << concatenatedString << std::endl;
}

int main() {
    const char* destinationName = "org.freedesktop.systemd1";
    const char* objectPath = "/org/freedesktop/systemd1";
    const char* interfaceName = "org.freedesktop.systemd1.Manager";

    auto proxy = sdbus::createProxy(destinationName, objectPath);
    // concatenatorProxy->uponSignal("concatenated").onInterface(interfaceName).call([](const std::string& str){ onConcatenated(str); });
    proxy->finishRegistration();

    // std::vector<int> numbers = {1, 2, 3};
    // std::string separator = ":";

    // Invoke concatenate on given interface of the object
    // {

    std::vector<
        sdbus::Struct<
            std::string,
            std::string,
            std::string,
            std::string,
            std::string,
            std::string,
            sdbus::ObjectPath,
            uint32_t,
            std::string,
            sdbus::ObjectPath
        >
    > result;
    proxy->callMethod("ListUnits").onInterface(interfaceName).storeResultsTo(result);
    if(result.empty()) {
        std::cout << "empty";
        return 0;
    }
    // }

    for(auto item : result)  {
        std::cout << item.get<0>() << std::endl;
    }

    // Give sufficient time to receive 'concatenated' signal from the first concatenate invocation
    sleep(1);

    return 0;

}