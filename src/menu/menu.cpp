//
// Created by maud on 22/03/17.
//

#include <memory>
#include <iostream>
#include "Menu.hh"

arcade::Menu::Menu()
{
  component.push_back(arcade::Component(10, 10, 250, 250, 3, /*arcade::Color::Black,*/ "ARCADE"));
    component.push_back(arcade::Component(10, 10, 250, 250, 3, /*arcade::Color::Red,*/ "Snake"));
    component.push_back(arcade::Component(10, 10, 250, 250, 3, /*arcade::Color::Blue,*/ "Solar Fox"));
    component.push_back(arcade::Component(10, 10, 250, 250, 3, /*arcade::Color::Blue,*/ "Centipede"));
    component.push_back(arcade::Component(10, 10, 250, 250, 3, /*arcade::Color::Green,*/ "Settings"));
}

arcade::Menu::~Menu()
{

}

void    arcade::Menu::display() const
{
    for (std::vector<arcade::Component>::const_iterator it = component.begin(); it != component.end(); it++)
    {
        std::cout << it->getText() << std::endl;
    }
}
