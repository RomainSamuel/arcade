#ifndef CORE_HH_
# define CORE_HH_

#include <string>
#include "GameState.hpp"

namespace arcade
{
    class Core
    {
    private:
        int volume;
        int level;
        arcade::GameState gameState;
    public:
        Core(const std::string, const int, const int);
        ~Core();

        int getVolume() const;
        void setVolume(const int);
        int getLevel() const;
        void setLevel(const int);
        arcade::GameState getGameState() const;
        void setGameState(const arcade::GameState);
        void menu();
        void play();
    };
}

#endif // !CORE_HH_