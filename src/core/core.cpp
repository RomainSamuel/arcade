//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include <memory>
#include "Core.hh"
#include "Menu.hh"

arcade::Core::Core(const std::string _lib, const int _level, const int _volume)
{
    std::ifstream fs(_lib);

    if (_lib.compare(_lib.size() - 3, 3, ".so") != 0
        || _lib.compare(0, 15, "lib/lib_arcade_") != 0)
    {
        std::cerr << "Usage : ./arcade lib_arcade_XXXX.so" << std::endl;
        exit(1);
    }
    if (!fs.is_open())
    {
        std::cerr << "Library : " << _lib << " doesn't exist!" << std::endl;
        exit(1);
    }
    level = _level;
    volume = _volume;
    lib = _lib;
    std::cout << "lib = " << lib;
    std::cout << " Level = " << level;
    std::cout << " Volume = " << volume << std::endl;
    gameState = arcade::GameState::MENU;
}

arcade::Core::~Core()
{

}

int     arcade::Core::getVolume() const
{
    return (volume);
}

void    arcade::Core::setVolume(const int _volume)
{
    volume = _volume;
}

int     arcade::Core::getLevel() const
{
    return (level);
}

void    arcade::Core::setLevel(const int _level)
{
    level = _level;
}

arcade::GameState    arcade::Core::getGameState() const
{
    return (gameState);
}

void    arcade::Core::setGameState(const arcade::GameState state)
{
    gameState = state;
}

void    arcade::Core::menu()
{
    std::unique_ptr<arcade::Menu> menu = std::make_unique<arcade::Menu>();
    menu->display();
}

void    arcade::Core::play()
{
    std::cout << "Let's play!" << std::endl;
}