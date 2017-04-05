#include "Shot.hh"

sf::Shot::Shot(size_t layer,
               double x,
               double y,
               size_t lifeDuration,
               int direction,
               double moveSpeed,
               mvType mv,
               bool player)
{
  this->layer = layer;
  this->x = x;
  this->y = y;
  this->lifeDuration = lifeDuration;
  this->direction = direction;
  this->moveSpeed = moveSpeed;
  this->mv = mv;
  this->player = player;
}

sf::Shot::~Shot()
{

}

void    sf::Shot::printOnMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(this->layer, static_cast<size_t>(this->x), static_cast<size_t>(this->y)).
    set(arcade::TileType::EMPTY,
        arcade::TileTypeEvolution::SHOT_ENEMY,
        arcade::Color::Yellow,
        false,
        6,
        0,
        this->x - 0.5 - static_cast<double>(static_cast<int>(this->x)),
        this->y - 0.5 - static_cast<double>(static_cast<int>(this->y)));
}

void    sf::Shot::eraseFromMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(this->layer, static_cast<size_t>(this->x), static_cast<size_t>(this->y)).
    set(arcade::TileType::EMPTY,
        arcade::TileTypeEvolution::EMPTY,
        arcade::Color::Black,
        false,
        0,
        0,
        0.0,
        0.0);
}

int   sf::Shot::move(std::unique_ptr<arcade::Map> &map)
{
  this->eraseFromMap(map);
  if (lifeDuration == 0)
    return (-1);
  if (this->mv == VERTICAL)
    {
      this->y += this->moveSpeed * static_cast<double>(this->direction);
    }
  else
    {
      this->x += this->moveSpeed * static_cast<double>(this->direction);
    }
  this->lifeDuration--;
  this->printOnMap(map);
  return (0);
}
