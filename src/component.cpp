//
// Created by maud on 26/03/17.
//

#include "Component.hh"

arcade::Component::Component()
{
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
