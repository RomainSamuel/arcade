//
// Created by maud on 23/03/17.
//

#ifndef COMPONENT_HH_
#define COMPONENT_HH_

#include <string>
#include "GameState.hpp"
#include "common/IComponent.hpp"

namespace arcade
{
    class Component : public IComponent
    {
    protected:
        double x;
        double y;
        double width;
        double height;
        std::size_t backgroundId;
      //arcade::Color backgroundColor;
        std::string text;

    public:
        Component();
      Component(double const, double const, double const, double const, std::size_t const, /*arcade::Color,*/ std::string);
        virtual ~Component();

        virtual double getX() const;
        virtual double getY() const;

        virtual double getWidth() const;
        virtual double getHeight() const;

        virtual std::size_t getBackgroundId() const;
      //virtual arcade::Color getBackgroundColor() const;
        virtual std::string const &getText() const;
    };
}

#endif //COMPONENT_HH_
