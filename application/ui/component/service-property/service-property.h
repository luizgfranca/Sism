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

