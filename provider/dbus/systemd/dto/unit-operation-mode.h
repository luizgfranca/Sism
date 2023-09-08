#pragma once

#include <cstdint>
#include <string>

namespace provider::dbus::systemd::dto {
    enum UnitOperationMode : uint8_t {
        // the call will start the unit and its dependencies, 
        // possibly replacing already queued jobs that conflict with this. 
        REPLACE, 

        // the call will start the unit and its dependencies, 
        // but will fail if this would change an already queued job.
        FAIL, 

        // the call will start the unit in question and terminate all units that aren't dependencies of it. 
        ISOLATE, 
        
        //It is not recommended to make use of the latter two options
        IGNORE_DEPENDENCIES, // it will start a unit but ignore all its dependencies.
        IGNORE_REQUIREMENTS, //  it will start a unit but only ignore the requirement dependencies. 
    };

    std::string to_string(UnitOperationMode mode);
}