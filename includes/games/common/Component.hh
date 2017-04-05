#ifndef COMPONENT_HH_
# define COMPONENT_HH_

# include "IComponent.hpp"
# include "Color.hpp"

namespace arcade
{
  class   Component : public IComponent
  {
    double  _x;
    double  _y;
    double  _width;
    double  _height;
    bool    _hasSprite;
    size_t  _backgroundId;
    Color   _backgroundColor;
    std::string _text;
    bool    _clicked;

  public:
    Component(double,
              double,
              double,
              double,
              bool,
              size_t,
              Color,
              std::string);

    virtual ~Component();

    virtual double getX() const;

    virtual double getY() const;

    virtual double getWidth() const;

    virtual double getHeight() const;

    virtual bool hasSprite() const;

    virtual size_t getBackgroundId() const;

    virtual arcade::Color getBackgroundColor() const;

    virtual std::string const &getText() const;

    virtual void setClicked();

    void  setText(const std::string &);
  };
}

#endif
