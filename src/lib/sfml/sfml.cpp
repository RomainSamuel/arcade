//
// Created by maud on 26/03/17.
//

#include <iostream>
#include "Sfml.hh"

/*
 * Constructor
 */
arcade::LibSfml::LibSfml(const unsigned int width, const unsigned int height)
{
    std::cout << "Lib Sfml Launched" << std::endl;

    _window.create(sf::VideoMode(width, height), "Arcade");
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
        _window.display();
    }
}

void    test()
{
    arcade::LibSfml toto(900, 600);
    //toto.runGfx();
}

int main()
{
    test();
    return (0);
}

/*void arcade::Sfml::openWindow(double width, double height, std::string window_name)
{
    sf::RenderWindow window(sf::VideoMode(width, height), window_name);

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
            text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);
            text.setPosition(350, 10);
        }

        window.draw(text);
        window.display();
    }
}*/