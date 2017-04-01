//
// Created by maud on 26/03/17.
//

#include <iostream>
#include "Sfml.hh"

/*
 * Constructor
 */
arcade::LibSfml::LibSfml(unsigned int const width, unsigned int const height) : _width(width), _height(height)
{
    std::cout << "Lib Sfml Launched" << std::endl;

    _window.create(sf::VideoMode(_width, _height), "Arcade");
}

/*
 * Destructor
 */
arcade::LibSfml::~LibSfml()
{
}

/*
 * Run Gfx
 */
void    arcade::LibSfml::runGfx()
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
}

void    test()
{
  arcade::LibSfml toto(800, 600);
    toto.runGfx();
}

int main()
{
    test();
    return (0);
}
