//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include <memory>
#include "Core.hh"
#include "Exceptions.hh"

arcade::Core::Core(const std::string &lib, const int volume) : _lib(lib), _volume(volume), _gameState(arcade::GameState::MENU), _loader(), _libLoad(), _gameLoad(), _menu()
{
    std::ifstream fs(lib);

    if (lib.compare(lib.size() - 3, 3, ".so") != 0
        || lib.compare(0, 15, "lib/lib_arcade_") != 0)
        throw arcade::Error("Usage : ./arcade lib_arcade_XXXX.so");
    if (!fs.is_open())
        throw arcade::Error("Library : " + lib + " doesn't exist!");
    
    _loader.setCurrentLib(lib);
    _loader.setCurrentGame("games/lib_arcade_snake.so");
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

void    arcade::Core::display()
{
    _menu = new arcade::Menu();
    
    void *loader = getLoader().getSym(getLoader().getCurrentLib(), "loader");
    _libLoad = reinterpret_cast<arcade::IGfxLib *(*)()>(loader)();
    void *mkr = getLoader().getSym(getLoader().getCurrentGame(), "maker");
    _gameLoad = reinterpret_cast<arcade::IGame *(*)()>(mkr)();
    
    while (getGameState() != arcade::GameState::QUIT)
    {

        /*if (getGameState() == arcade::GameState::MENU)
        {
            _libLoad->display();
            menu();
        }
        else if (getGameState() == arcade::GameState::INGAME)*/
            play();
    }
}

void    arcade::Core::menu()
{
    _libLoad->clear();
    _menu->display();
}

void    arcade::Core::play()
{
    Event e;

    _libLoad->clear();
    if (_libLoad->pollEvent(e))
    {
    }
    _libLoad->updateMap(_gameLoad->getCurrentMap());
    //_libLoad->updateGUI(_gameLoad->getGUI());
    _libLoad->display();
    std::cout << "Let's play!!" << std::endl;
}