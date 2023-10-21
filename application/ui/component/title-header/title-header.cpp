#include "title-header.h"

using namespace application::ui::component;


void TitleHeader::setup_components() {
    append(m_label_header_message);
}

void TitleHeader::setup_style() {
    add_css_class("view");
    m_label_header_message.set_hexpand(true);
    
    switch (m_header_level) {
        case H1:
            m_label_header_message.add_css_class("title-1");
            break;
        case H2:
            m_label_header_message.add_css_class("title-2");
            break;
        case H3:
            m_label_header_message.add_css_class("title-3");
            break;
        case H4:
            m_label_header_message.add_css_class("title-4");
            break;
    }
}

TitleHeader::TitleHeader(HeaderLevel header_level) {
    m_header_level = header_level;

    setup_components();
    setup_style();
}

void TitleHeader::set_title(std::string title) {
    m_label_header_message.set_text(title);
}