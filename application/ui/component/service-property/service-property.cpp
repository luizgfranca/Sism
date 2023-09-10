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


#include "service-property.h"
#include "cairomm/fontoptions.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include <string>

using namespace application::ui::component;

void ServiceProperty::configure() {
    auto text_size_provider = Gtk::CssProvider::create();
    text_size_provider->load_from_data("#label-name, #label-value{font-size: 1.2rem}");

    m_name_label.set_margin_start(10);
    m_name_label.set_margin_top(2);
    m_name_label.set_name("label-name");
    m_name_label.get_style_context()->add_provider(text_size_provider, 1);
    
    m_value_label.set_margin_start(10);
    m_value_label.set_margin_top(2);
    m_value_label.set_name("label-value");
    m_value_label.get_style_context()->add_provider(text_size_provider, 1);

    set_vexpand(false);

    append(m_name_label);
    append(m_value_label);
}

void ServiceProperty::set_name(std::string name) {
    m_name_label.set_markup("<b>" + name + "</b>");
}

void ServiceProperty::set_value(std::string value) {
    m_value_label.set_label(value);
}

ServiceProperty::ServiceProperty() {
    configure();
}

ServiceProperty::ServiceProperty(std::string name, std::string value) {
    configure();
    set_name(name);
    set_value(value);
}

