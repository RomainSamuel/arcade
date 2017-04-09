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
    _loader = getLoader();

    void *loader = _loader.getSym(_loader.getCurrentLib(), "loader");
    _libLoad = ((arcade::IGfxLib *(*)())loader)();
    _libLoad->loadSprites(_menu.getSpritesToLoad());

    while (getGameState() != arcade::GameState::QUIT)
    {
        _libLoad->clear();
        if (getGameState() == arcade::GameState::MENU)
           menu();
        else if (getGameState() == arcade::GameState::INGAME)
            play();
    }
}

void    arcade::Core::menu()
{
    Event   event;
    std::vector<Event> _events;

    if (_libLoad->pollEvent(event))
    {
        if (event.kb_key == arcade::KeyboardKey::KB_SPACE)
        {
            setGameState(arcade::GameState::INGAME);
            void *mkr = _loader.getSym(_loader.getCurrentGame(), "maker");
            _gameLoad = ((arcade::IGame *(*)())mkr)();
            _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
            _libLoad->loadSounds(_gameLoad->getSoundsToLoad());
        }
        else if (event.kb_key == arcade::KeyboardKey::KB_ESCAPE)
            setGameState(arcade::GameState::QUIT);
        else if (event.kb_key == arcade::KeyboardKey::KB_ARROW_DOWN)
        {
            _menu.setPos(_menu.getPos() + 1);
            _menu.updateGUI();
        }
        else if (event.kb_key == arcade::KeyboardKey::KB_ARROW_UP)
        {
            _menu.setPos(_menu.getPos() - 1);
            _menu.updateGUI();
        }
        else if (event.kb_key == arcade::KeyboardKey::KB_ENTER)
        {
            if (_menu.getPos() != 4)
            {
                if (_menu.getPos() == 1)
                    _loader.setCurrentGame("games/lib_arcade_snake.so");
                else if (_menu.getPos() == 2)
                    _loader.setCurrentGame("games/lib_arcade_snake.so");
                else if( _menu.getPos() == 3)
                    _loader.setCurrentGame("games/lib_arcade_centipede.so");
                setGameState(arcade::GameState::INGAME);
                void *mkr = _loader.getSym(_loader.getCurrentGame(), "maker");
                _gameLoad = ((arcade::IGame *(*)())mkr)();
                _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
                _libLoad->loadSounds(_gameLoad->getSoundsToLoad());
            }
            else
                setGameState(arcade::GameState::QUIT);
        }
    }
    _libLoad->updateGUI(_menu.getGUI());
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
                    _loader.getPrevLib();
                    void *loader = _loader.getSym(_loader.getCurrentLib(), "loader");
                    delete _libLoad;
                     _libLoad = ((arcade::IGfxLib *(*)())loader)();
                    _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
                    _libLoad->loadSounds(_gameLoad->getSoundsToLoad());

                     break;
                }
                case arcade::KeyboardKey::KB_3 :
                {
                    _loader.getNextLib();
                    void *loader = _loader.getSym(_loader.getCurrentLib(), "loader");
                    delete _libLoad;
                    _libLoad = ((arcade::IGfxLib *(*)())loader)();
                        _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
                    _libLoad->loadSounds(_gameLoad->getSoundsToLoad());
                    break;
                }
                case arcade::KeyboardKey::KB_4 :
                {
                    _loader.getPrevGame();
                    void *mkr = _loader.getSym(_loader.getCurrentGame(), "maker");
                    delete _gameLoad;
                    _gameLoad = ((arcade::IGame *(*)())mkr)();
                    _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
                    _libLoad->loadSounds(_gameLoad->getSoundsToLoad());
                    break;
                }            
                 case arcade::KeyboardKey::KB_5 :
                {
                    _loader.getNextGame();
                    void *mkr = _loader.getSym(_loader.getCurrentGame(), "maker");
                    delete _gameLoad;
                    _gameLoad = ((arcade::IGame *(*)())mkr)();
                    _libLoad->loadSprites(_gameLoad->getSpritesToLoad());
                    _libLoad->loadSounds(_gameLoad->getSoundsToLoad());
                    break;
                }
                case arcade::KeyboardKey::KB_9 :
                {
                 setGameState(arcade::GameState::MENU);
                _libLoad->loadSprites(_menu.getSpritesToLoad());
                 break;
                }
                case arcade::KeyboardKey::KB_ESCAPE :
                       setGameState(arcade::GameState::QUIT);
            default:
                break;
            }   
        }
      _events.push_back(event);
      _gameLoad->notifyEvent(std::move(_events));
    }
    if (_gameLoad->getGameState() == arcade::GameState::MENU)
    {
        delete _libLoad;
        void *loader = _loader.getSym(_loader.getCurrentLib(), "loader");
        _libLoad = ((arcade::IGfxLib *(*)())loader)();
        _libLoad->loadSprites(_menu.getSpritesToLoad());
        setGameState(arcade::GameState::MENU);
    }
        _gameLoad->process();
    if (_gameState != arcade::GameState::MENU)
    {
        _gameLoad->getSoundsToPlay();
        _libLoad->updateMap(_gameLoad->getCurrentMap());
        _libLoad->updateGUI(_gameLoad->getGUI());
        _libLoad->display();
    }
} 
