#include "Scrap.hh"

sf::Scrap::Scrap(size_t x, size_t y)
{
  this->x = x;
  this->y = y;
}
sf::Scrap::~Scrap()
{
}

size_t  sf::Scrap::getX() const
{
  return (this->x);
}

size_t  sf::Scrap::getY() const
{
  return (this->y);
}

void    sf::Scrap::printOnMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(1, this->x, this->y).set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, false, 2, 0, 0.0, 0.0);
}

void    sf::Scrap::eraseFromMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(1, this->x, this->y).set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::EMPTY, arcade::Color::White, false, 0, 0, 0.0, 0.0);
}
