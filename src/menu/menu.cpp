//
// Created by maud on 22/03/17.
//

#include <memory>
#include <iostream>
#include "Text.hh"
#include "gameButton.hh"
#include "settingsButton.hh"
#include "Menu.hh"
#include "IComponent.hh"

arcade::Menu::Menu() : _items {}
{
    _items.push_back(arcade::Text(10, 10, 250, 250, 3, arcade::Color::Black, "ARCADE", 25));
    _items.push_back(arcade::gameButton(10, 10, 250, 250, 3, arcade::Color::Red, "Snake", "snake"));
    _items.push_back(arcade::gameButton(10, 10, 250, 250, 3, arcade::Color::Blue, "Solar Fox", "solar fox"));
    _items.push_back(arcade::gameButton(10, 10, 250, 250, 3, arcade::Color::Blue, "Centipede", "centipede"));
    _items.push_back(arcade::settingsButton(10, 10, 250, 250, 3, arcade::Color::Green, "Settings"));
    _items.push_back(arcade::Text(10, 10,  250, 250, 3, arcade::Color::White, "Made By: Khsime Marwane, Marel Maud & Samuel Romain - Epitech", 13));
}

arcade::Menu::~Menu()
{

}

void    arcade::Menu::display() const
{
    for (std::vector<arcade::AItem>::const_iterator it = _items.begin(); it != _items.end(); it++)
    {
    }
}

std::size_t     arcade::Menu::size() const
{
    return (_items.size());
}

arcade::IComponent      &arcade::Menu::at(std::size_t n)
{
    return (_items.at(n));
}
