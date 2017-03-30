//
// Created by maud on 23/03/17.
//

#ifndef MENU_HH_
#define MENU_HH_

#include <string>

#include <vector>
#include "../Component.hh"

namespace arcade
{
    class Menu : public Component
    {
    protected:
        std::vector<arcade::Component> component;

    public:
        Menu();
        virtual ~Menu();

        void display() const;
    };
}

#endif //MENU_HH_
