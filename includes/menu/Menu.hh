//
// Created by maud on 23/03/17.
//

#ifndef MENU_HH_
#define MENU_HH_

#include <string>

#include <vector>
#include "AItem.hh"
#include "IGUI.hpp"

namespace arcade
{
    class Menu : public IGUI
    {
    protected:
        std::vector<arcade::AItem> _items;

    public:
        Menu();
        virtual ~Menu();

        void display() const;
        virtual std::size_t size() const;
        virtual IComponent &at(std::size_t n);
    };
}

#endif //MENU_HH_
