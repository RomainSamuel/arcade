#ifndef CORE_HH_
# define CORE_HH_

#include <string>
#include <memory>
#include "Loader.hh"
#include "../GameState.hpp"

namespace arcade
{
    class Core
    {
    private:
        std::string _lib;
        int _volume;
        arcade::GameState _gameState;
        arcade::Loader    _loader;
        
    public:
        Core(const std::string &, const int);
        ~Core();

        arcade::Loader  getLoader() const;
        int getVolume() const;
        void setVolume(const int);
        arcade::GameState getGameState() const;
        void setGameState(const arcade::GameState);
        void menu();
        void play();
    };
}

#endif // !CORE_HH_