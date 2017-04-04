//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include <memory>
#include "Core.hh"
#include "Loader.hh"
#include "Menu.hh"

arcade::Core::Core(const std::string lib, const int level, const int volume) : _lib(lib), _level(level), _volume(volume), _gameState(arcade::GameState::MENU)
{
    std::ifstream fs(lib);

    if (lib.compare(lib.size() - 3, 3, ".so") != 0
        || lib.compare(0, 15, "lib/lib_arcade_") != 0)
    {
        std::cerr << "Usage : ./arcade lib_arcade_XXXX.so" << std::endl;
        exit(1);
    }
    if (!fs.is_open())
    {
        std::cerr << "Library : " << lib << " doesn't exist!" << std::endl;
        exit(1);
    }
    std::cout << "lib = " << lib;
    std::cout << " Level = " << level;
    std::cout << " Volume = " << volume << std::endl;
    std::unique_ptr<arcade::Loader> loader = std::make_unique<arcade::Loader>(lib);
}

arcade::Core::~Core()
{

}

int     arcade::Core::getVolume() const
{
    return (_volume);
}

void    arcade::Core::setVolume(const int volume)
{
    _volume = volume;
}

int     arcade::Core::getLevel() const
{
    return (_level);
}

void    arcade::Core::setLevel(const int level)
{
    _level = level;
}

arcade::GameState    arcade::Core::getGameState() const
{
    return (_gameState);
}

void    arcade::Core::setGameState(const arcade::GameState state)
{
    _gameState = state;
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