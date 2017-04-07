//
// Created by maud on 26/03/17.
//

#include <iostream>
#include "Sfml.hh"
 
/*
 * Constructor
 */
arcade::LibSfml::LibSfml() : _width(800), _height(600)
{
    std::cout << "Lib Sfml Launched" << std::endl;
    _window.create(sf::VideoMode(_width, _height), "Arcade", sf::Style::Close);
}

/*
 * Destructor
 */
arcade::LibSfml::~LibSfml()
{
}

bool    arcade::LibSfml::pollEvent(Event &e)
{
    sf::Event event;

    (void)e;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            {
            }
	}
    return (true);
}

bool    arcade::LibSfml::doesSupportSound() const
{ 
    return (true);
}

void    arcade::LibSfml::loadSounds(std::vector<std::pair<std::string, SoundType>> const &sounds)
{
    (void)sounds;
}

void    arcade::LibSfml::soundControl(const Sound &sound)
{
    (void)sound;
}

void    arcade::LibSfml::loadSprites(std::vector<std::unique_ptr<ISprite> > &&sprites)
{
    (void)sprites;
}

void    arcade::LibSfml::updateMap(IMap const &map)
{
    // Save Map properties
    size_t  nbLayers = map.getLayerNb();
    size_t  height = map.getHeight();
    size_t  width = map.getWidth();

 // Adjust the ratio between the game map and de window
    _tileWidth = _width / map.getWidth();
    _tileHeight = _height / map.getHeight();

   for (std::size_t layer = 0; layer < nbLayers; layer++) {

        for (std::size_t x = 0; x < width; x++) {

            for (std::size_t y = 0; y < height; y++) {

                // Check if the tile is a sprite
                //if (map.at(layer, x, y).hasSprite()) {
                    putTileSprite(map.at(layer, x, y), x, y);
                //}
                // If not, get the color
                //else {
                    putTileColor(map.at(layer, x, y), x, y);
                //}
            }
        }
    }
}   

void    arcade::LibSfml::putTileColor(arcade::ITile const &tile, size_t x, size_t y) {

    (void)tile;
    // Adapt the coordinates for the viewport
    double  x_begin = (x * WIDTH_RATIO);
    double  x_end = (x + 1) * WIDTH_RATIO;
    double  y_begin = (y * HEIGHT_RATIO);
    double  y_end = (y + 1) * HEIGHT_RATIO;

    sf::RectangleShape rectangle(sf::Vector2f(x_end - x_begin, y_end - y_begin));
    rectangle.setPosition(x_begin, y_begin);

    // Set Color
    rectangle.setFillColor(sf::Color((double)tile.getColor().r,
                            (double)tile.getColor().g,
                            (double)tile.getColor().b,
                            (double)tile.getColor().a));

    _window.draw(rectangle);
}

void    arcade::LibSfml::putTileSprite(arcade::ITile const &tile, size_t x, size_t y) {

(void)tile;
(void)x;
(void)y;

}

void    arcade::LibSfml::updateGUI(IGUI &gui)
{
    (void)gui;

}

void    arcade::LibSfml::display()
{
    sf::Texture texture;
    texture.loadFromFile("resources/menu/arcade.png");
    
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(200, 10));
    _window.draw(sprite);

    _window.display();
    }

void    arcade::LibSfml::clear()
{
    _window.clear(sf::Color::Black);
}

extern "C" arcade::IGfxLib  *loader()
{
    return (new arcade::LibSfml());
}
