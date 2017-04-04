//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include <memory>
#include "Core.hh"
#include "Menu.hh"

arcade::Core::Core(const std::string &lib, const int volume) : _lib(lib), _volume(volume), _gameState(arcade::GameState::MENU), _loader()
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
    
    _loader.setCurrentLib(lib);
}

arcade::Core::~Core()
{

}

arcade::Loader  arcade::Core::getLoader() const
{
    return (_loader);
}

int     arcade::Core::getVolume() const
{
    return (_volume);
}

void    arcade::Core::setVolume(const int volume)
{
    _volume = volume;
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