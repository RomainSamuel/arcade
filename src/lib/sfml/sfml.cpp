//
// Created by maud on 26/03/17.
//

#include <iostream>
#include "Sfml.hh"
 
/*
 * Constructor
 */
arcade::LibSfml::LibSfml()
{
    std::cout << "Lib Sfml Launched" << std::endl;

    _window.create(sf::VideoMode(800, 600), "Arcade");
}

/*
 * Destructor
 */
arcade::LibSfml::~LibSfml()
{
}

bool    arcade::LibSfml::pollEvent(Event &e)
{
    std::cout << "pollEvent" << std::endl;
    (void) e;
    return (true);
}

bool    arcade::LibSfml::doesSupportSound() const
{
    std::cout << "doesSupportSound" << std::endl;
    return (true);
}

void    arcade::LibSfml::loadSounds(std::vector<std::pair<std::string, SoundType>> const &sounds)
{
    (void)sounds;
    std::cout << "loadSounds" << std::endl;
}

void    arcade::LibSfml::soundControl(const Sound &sound)
{
    (void)sound;
    std::cout << "soundControl" << std::endl;
}

void    arcade::LibSfml::loadSprites(std::vector<std::unique_ptr<ISprite> > &&sprites)
{
    (void)sprites;
    std::cout << "loadSprites" << std::endl;
}

void    arcade::LibSfml::updateMap(IMap const &map)
{
    (void)map;
    std::cout << "updateMap" << std::endl;
}

void    arcade::LibSfml::updateGUI(IGUI &gui)
{
    (void)gui;
    std::cout << "updateGUI" << std::endl;
}

void    arcade::LibSfml::display()
{
        // Game loop
  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    _window.close();        
	}
      _window.clear(sf::Color::Black);
      _window.display();
    }
    std::cout << "display" << std::endl;
}

void    arcade::LibSfml::clear()
{
    std::cout << "clear" << std::endl;
}

extern "C" arcade::IGfxLib  *loader()
{
    return (new arcade::LibSfml());
}
