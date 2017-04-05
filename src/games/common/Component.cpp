#include "Component.hh"

arcade::Component::Component(double x,
                             double y,
                             double width,
                             double height,
                             bool hasSprite,
                             size_t backgroundId,
                             Color backgroundColor,
                             std::string text)
{
  this->_x = x;
  this->_y = y;
  this->_width = width;
  this->_height = height;
  this->_hasSprite = hasSprite;
  this->_backgroundId = backgroundId;
  this->_backgroundColor = backgroundColor;
  this->_text = text;
}

arcade::Component::~Component()
{
}

double  arcade::Component::getX() const
{
  return (this->_x);
}

double  arcade::Component::getY() const
{
  return (this->_y);
}

double  arcade::Component::getWidth() const
{
  return (this->_width);
}

double  arcade::Component::getHeight() const
{
  return (this->_height);
}

bool  arcade::Component::hasSprite() const
{
  return (this->_hasSprite);
}

size_t  arcade::Component::getBackgroundId() const
{
  return (this->_backgroundId);
}

arcade::Color arcade::Component::getBackgroundColor() const
{
  return (this->_backgroundColor);
}

std::string const &arcade::Component::getText() const
{
  return (this->_text);
}

void  arcade::Component::setClicked()
{
  this->_clicked = true;
}

void  arcade::Component::setText(const std::string &text)
{
  this->_text = text;
}
