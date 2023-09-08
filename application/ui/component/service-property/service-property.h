#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include <string>

namespace application::ui::component {

    class ServiceProperty : public Gtk::Box {
        Gtk::Label m_name_label;
        Gtk::Label m_value_label;

        void configure();

        public:
            ServiceProperty();
            ServiceProperty(std::string name, std::string value);
            void set_name(std::string name);
            void set_value(std::string value);
    };

}

