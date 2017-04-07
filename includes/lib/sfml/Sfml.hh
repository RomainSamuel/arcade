//
// Created by maud on 26/03/17.
//

#ifndef CPP_ARCADE_SFML_HH
# define CPP_ARCADE_SFML_HH

#include <SFML/Graphics.hpp>
#include "IGfxLib.hh"

# define WIDTH_RATIO        _tileWidth
# define HEIGHT_RATIO       _tileHeight

namespace arcade
{
    class LibSfml : public IGfxLib
    {
    private:
        sf::RenderWindow    _window;
        size_t              _tileWidth;
        size_t              _tileHeight;

        size_t              _width;
        size_t              _height;

        void            putTileColor(ITile const &tile, size_t x, size_t y);
            void            putTileSprite(ITile const &tile, size_t x, size_t y);
            //bool            loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);

    public:
        //Constructor / Destructor
        LibSfml();
        virtual ~LibSfml();

        virtual bool pollEvent(Event &e);
        virtual bool doesSupportSound() const;
        virtual void loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds);
        virtual void soundControl(const Sound &sound);
        virtual void loadSprites(std::vector<std::unique_ptr<ISprite> > &&sprites);
        virtual void updateMap(IMap const &map);
        virtual void updateGUI(IGUI &gui);
        virtual void display();
        virtual void clear();
    };
}

#endif //CPP_ARCADE_SFML_HH
