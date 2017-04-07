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
    arcade::Loader _loader = getLoader();

    void *loader = _loader.getSym(getLoader().getCurrentLib(), "loader");
    _libLoad = ((arcade::IGfxLib *(*)())loader)();
    void *mkr = _loader.getSym(getLoader().getCurrentGame(), "maker");
    _gameLoad = ((arcade::IGame *(*)())mkr)();

    while (getGameState() != arcade::GameState::QUIT)
    {
        _libLoad->clear();
        //if (getGameState() == arcade::GameState::MENU)
          //  menu();
        //else if (getGameState() == arcade::GameState::INGAME)
            play();
    }
}

void    arcade::Core::menu()
{
    Event   event;

    if (_libLoad->pollEvent(event))
    {

    }
    _menu->display();
}

void    arcade::Core::play()
{
    //Event event;
    //std::vector<Event> _events;

    //if (_libLoad->pollEvent(event))
    //{
      //_events.push_back(event);
      //_gameLoad->notifyEvent(&&_events);
    //}
    _gameLoad->process();
    //if (_gameLoad->getGameState() == arcade::GameState::QUIT)
      //  setGameState(arcade::GameState::QUIT);
    //if (_gameState != arcade::GameState::QUIT)
    //{
       _libLoad->updateMap(_gameLoad->getCurrentMap());
        //_libLoad->updateGUI(_gameLoad->getGUI());
        _libLoad->display();
    //}
}
