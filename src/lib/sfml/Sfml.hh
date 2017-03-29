//
// Created by maud on 26/03/17.
//

#ifndef CPP_ARCADE_SFML_HH
#define CPP_ARCADE_SFML_HH

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

#include "../../../includes/Event.hpp"

namespace arcade
{
    static std::vector<arcade::Event> _lastEvents;

    class LibSfml
    {
    private:
        sf::RenderWindow    _window;
        unsigned int  _width;
        unsigned int  _height;

        // Sound
        //std::map<size_t> _sounds;

        // Member functions
    public:
        void    runGfx();
        bool    initSfml() const;
        void    shutDownSfml();
    public:
        //Constructor / Destructor
        LibSfml(const unsigned int, const unsigned int);
        ~LibSfml();

        //Keyboard Management

        // Pool event

        // Sound

    };
}

#endif //CPP_ARCADE_SFML_HH
