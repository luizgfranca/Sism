#include "gtkmm/box.h"
#include "gtkmm/label.h"

namespace application::ui::component {
    enum HeaderLevel {
        H1, H2, H3, H4
    };

    class TitleHeader : public Gtk::Box {
        Gtk::Label m_label_header_message;
        
        HeaderLevel m_header_level;

        void setup_components();
        void setup_style();
    public:
        TitleHeader(HeaderLevel header_level = HeaderLevel::H2);
        void set_title(std::string title);
    };
}
