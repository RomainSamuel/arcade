//
// Created by maud on 26/03/17.
//

#include <iostream>
#include "Sfml.hh"

/*
 * Constructor
 */
arcade::LibSfml::LibSfml(unsigned int const width, unsigned int const height)
{
    std::cout << "Lib Sfml Launched" << std::endl;

    _window.create(sf::VideoMode(900, 800), "Arcade");
    std::cout << "toto" << std::endl;
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
  arcade::LibSfml toto(900, 600);
    toto.runGfx();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 600), "Test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        sf::Text text;
        sf::Font font;
        if (font.loadFromFile("Capture_it.ttf"))
        {
            text.setFont(font);
            text.setString("Arcade");
            text.setCharacterSize(26); // exprimée en pixels, pas en points !
            //text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);
            text.setPosition(350, 10);
        }

        window.draw(text);
        window.display();
    }
    return (0);
}
