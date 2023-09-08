#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "job.h"
#include "../dbus/systemd/dto/dto.h"


namespace provider::systemd {
    class Unit {
        bool m_has_running_job = false;
        std::shared_ptr<Job> m_running_job;
    public:
        // The primary unit name as string
        std::string name;

        // The human readable description string
        std::string description;

        // The load state (i.e. whether the unit file has been loaded successfully)
        std::string load_state;

        // The active state (i.e. whether the unit is currently started or not)
        std::string active_state;

        // The sub state (a more fine-grained version of the active state that is specific to the unit type, which the active state is not)
        std::string sub_state;

        // A unit that is being followed in its state by this unit, if there is any, otherwise the empty string
        std::string follows;

        // The unit object path
        std::string object_path;

        Unit(
            std::string name,
            std::string description,
            std::string load_state,
            std::string active_state,
            std::string sub_state,
            std::string follows,
            std::string object_path
        ): 
            name(name),
            description(description),
            load_state(load_state),
            active_state(active_state),
            sub_state(sub_state),
            follows(follows),
            object_path(object_path)
        {}

        bool is_follower() { return !follows.empty(); }

        bool has_running_job() { return m_has_running_job; }

        void set_running_job(Job& job) {
            m_has_running_job = true;
            m_running_job = std::make_shared<Job>(job);
        }

        std::shared_ptr<Job> get_running_job() { return m_running_job; }

        static std::unique_ptr<std::vector<Unit>> from_dbus_list_units_response(
            provider::dbus::systemd::dto::list_units_response_t response
        );

        static void sort_by_name_inplace(std::shared_ptr<std::vector<Unit>> units);

        static std::shared_ptr<std::vector<Unit>> filter_by_type(std::shared_ptr<std::vector<Unit>> units, std::string type);
    };
}
