#include <cstdint>
#include <string>


namespace provider::systemd {
    class Job {
    public:
        uint64_t id;
        std::string name;
        std::string path;


        Job(
            uint64_t id,
            std::string name,
            std::string path
        ): id(id), name(name), path(path) {}
    };
}
