#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#include <string>

namespace application::ui::component {
    class PropertyValueListRow : public Gtk::ListBoxRow {
        std::string m_property;
        std::string m_value;

        Gtk::Box m_content_box;
        Gtk::Label m_property_label;
        Gtk::Label m_value_label;

        void setup_components();
        void setup_style();
        void update_content();
    public:
        PropertyValueListRow(std::string initial_property_name = "", std::string initial_value = "");
        void set_property_name(std::string property_name);
        void set_value(std::string value);
    };
}