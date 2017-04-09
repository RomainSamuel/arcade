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

arcade::Core::~Core() {}

arcade::Core::Core(Core const &clone) : Core("", clone.getVolume()) {}

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
    _loader = getLoader();

    void *loader = _loader.getSym(getLoader().getCurrentLib(), "loader");
    _libLoad = ((arcade::IGfxLib *(*)())loader)();
    void *mkr = _loader.getSym(getLoader().getCurrentGame(), "maker");
    _gameLoad = ((arcade::IGame *(*)())mkr)();
    _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
    _libLoad->loadSounds(_gameLoad->getSoundsToLoad());

    while (getGameState() != arcade::GameState::QUIT)
    {
        _libLoad->clear();
        //if (getGameState() == arcade::GameState::MENU)
           //menu();
        //else if (getGameState() == arcade::GameState::INGAME)
        play();
    }
}

void    arcade::Core::menu()
{
    //Event   event;
    _libLoad->display();
}


void    arcade::Core::play()
{
    Event event;
    std::vector<Event> _events;

    if (_libLoad->pollEvent(event))
    {
        if (event.action == arcade::ActionType::AT_PRESSED)
        {
            switch (event.kb_key)
            {
                case arcade::KeyboardKey::KB_2 :
                {
                    std::cout << "2" << std::endl;
                    getLoader().getPrevLib();
                    void *loader = _loader.getSym(getLoader().getCurrentLib(), "loader");
                     _libLoad = ((arcade::IGfxLib *(*)())loader)();
                     break;
                }
                case arcade::KeyboardKey::KB_3 :
                {
                    std::cout << "3" << std::endl;
                    getLoader().getNextLib();
                    void *loader = _loader.getSym(getLoader().getCurrentLib(), "loader");
                    _libLoad = ((arcade::IGfxLib *(*)())loader)();
                    break;
                }
                case arcade::KeyboardKey::KB_4 :
                {
                    std::cout << "4" << std::endl;
                    getLoader().getPrevGame();
                    void *mkr = _loader.getSym(getLoader().getCurrentGame(), "maker");
                    _gameLoad = ((arcade::IGame *(*)())mkr)();
                    break;
                }            
                 case arcade::KeyboardKey::KB_5 :
                {
                    std::cout << "5" << std::endl;
                    getLoader().getNextGame();
                    void *mkr = _loader.getSym(getLoader().getCurrentGame(), "maker");
                    _gameLoad = ((arcade::IGame *(*)())mkr)();
                    break;
                }
                case arcade::KeyboardKey::KB_9 :
                {
                    std::cout << "9" << std::endl;
                 setGameState(arcade::GameState::MENU);
                 break;
                }
                case arcade::KeyboardKey::KB_ESCAPE :
                {  
                    std::cout << "ESCAPE" << std::endl;
                    setGameState(arcade::GameState::QUIT);
                }
            default:
                break;
            }   
        }
      _events.push_back(event);
      _gameLoad->notifyEvent(std::move(_events));
    }

    _gameLoad->process();

    if (_gameLoad->getGameState() == arcade::GameState::QUIT)
        setGameState(arcade::GameState::MENU);

    if (_gameState != arcade::GameState::QUIT)
    {
        _libLoad->updateMap(_gameLoad->getCurrentMap());
        _libLoad->updateGUI(_gameLoad->getGUI());
        _libLoad->display();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
} 
