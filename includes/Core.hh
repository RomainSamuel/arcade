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
        void play();
    };
}

#endif // !CORE_HH_