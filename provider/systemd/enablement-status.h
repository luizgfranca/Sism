#include <string>

namespace provider::systemd {
    enum EnablementStatus {
        INVALID,
        ALIAS,
        DISABLED,
        ENABLED,
        ENABLED_RUNTIME,
        GENERATED,
        INDIRECT,
        MASKED,
        STATIC,
        TRANSIENT
    };

    template <typename T>
    T from_string(std::string enablement_status_string);

    template <>
    inline EnablementStatus from_string(std::string enablement_status_string) {
        if(enablement_status_string == "alias") {
            return EnablementStatus::ALIAS;
        } else if(enablement_status_string == "disabled") {
            return EnablementStatus::DISABLED;
        } else if(enablement_status_string == "enabled") {
            return EnablementStatus::ENABLED;
        } else if(enablement_status_string == "enabled-runtime") {
            return EnablementStatus::ENABLED_RUNTIME;
        } else if(enablement_status_string == "generated") {
            return EnablementStatus::GENERATED;
        } else if(enablement_status_string == "indirect") {
            return EnablementStatus::INDIRECT;
        } else if(enablement_status_string == "masked") {
            return EnablementStatus::MASKED;
        } else if(enablement_status_string == "static") {
            return EnablementStatus::STATIC;
        } else if(enablement_status_string == "transient") {
            return EnablementStatus::TRANSIENT;
        } else {
            return EnablementStatus::INVALID;
        }
    }
}