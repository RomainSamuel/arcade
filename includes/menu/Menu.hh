//
// Created by maud on 23/03/17.
//

#ifndef MENU_HH_
#define MENU_HH_

#include <string>

#include <vector>
#include "AItem.hh"

namespace arcade
{
    class Menu : public AItem
    {
    protected:
        std::vector<arcade::AItem> _items;

    public:
        Menu();
        virtual ~Menu();

        void display() const;
    };
}

#endif //MENU_HH_
