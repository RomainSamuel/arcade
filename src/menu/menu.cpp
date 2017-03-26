//
// Created by maud on 22/03/17.
//

#include <memory>
#include <iostream>
#include "Menu.hh"

arcade::Menu::Menu()
{
    std::cout << "MENU init" << std::endl;
    std::unique_ptr<arcade::Component> component1 = std::make_unique<arcade::Component>(10, 10, 250, 250, 3, arcade::Color::Black, "HEllo");
    std::cout << component1->getX() << " " << component1->getY() << " " << component1->getWidth() << " " << component1->getHeight() << " " << component1->getBackgroundId() << " " << component1->getText() << std::endl;

}

arcade::Menu::~Menu()
{

}
