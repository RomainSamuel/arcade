//
// Created by maud on 26/03/17.
//

#include "Component.hh"

arcade::Component::Component()
{
}

arcade::Component::Component(double const _x, double const _y, double const _width, double const _height, std::size_t _backgroundId, arcade::Color const _backgroundColor, std::string const _text)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    backgroundId = _backgroundId;
    backgroundColor = _backgroundColor;
    text = _text;
}

arcade::Component::~Component()
{
}

double  arcade::Component::getX() const
{
    return (x);
}

double  arcade::Component::getY() const
{
    return (y);
}

double  arcade::Component::getWidth() const
{
    return (width);
}

double  arcade::Component::getHeight() const
{
    return (height);
}

std::size_t arcade::Component::getBackgroundId() const
{
    return (backgroundId);
}

arcade::Color   arcade::Component::getBackgroundColor() const
{
    return (backgroundColor);
}

std::string const   &arcade::Component::getText() const
{
    return (text);
}
