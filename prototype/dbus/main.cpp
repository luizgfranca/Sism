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