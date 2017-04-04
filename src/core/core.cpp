//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include <memory>
#include "Core.hh"
#include "Menu.hh"
#include "Exceptions.hh"

arcade::Core::Core(const std::string &lib, const int volume) : _lib(lib), _volume(volume), _gameState(arcade::GameState::MENU), _loader(), _libLoad()
{
    std::ifstream fs(lib);

    if (lib.compare(lib.size() - 3, 3, ".so") != 0
        || lib.compare(0, 15, "lib/lib_arcade_") != 0)
        throw arcade::Error("Usage : ./arcade lib_arcade_XXXX.so");
    if (!fs.is_open())
        throw arcade::Error("Library : " + lib + " doesn't exist!");
    
    _loader.setCurrentLib(lib);
}

arcade::Core::~Core()
{

}

arcade::Core::Core(Core const &clone) : Core("", clone.getVolume())
{
}

arcade::Core    &arcade::Core::operator=(Core const &clone)
{
    (void) clone;
    return (*this);
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
    void *mkr = getLoader().getSym(getLoader().getCurrentLib());
    _libLoad = reinterpret_cast<arcade::IGfxLib *(*)()>(mkr)();
    _libLoad->display();
    menu->display();
}

void    arcade::Core::play()
{
    std::cout << "Let's play!" << std::endl;
}