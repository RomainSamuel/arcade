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

bool    sf::Shot::Collide(sf::Shot &other) const
{
  if (this->mv == other.mv &&
      this->direction == - other.direction &&
      this->player != other.player &&
      ((this->mv == VERTICAL && (this->x == other.x)) ||
       (this->mv == HORIZONTAL && (this->y == other.y))))
    {
      if (this->mv == VERTICAL)
        {
          if (this->y + 1.0 >= other.y && this->y - 1.0 <= other.y)
            return (true);
          else
            return (false);
        }
      else
        {
          if (this->x + 1.0 >= other.x && this->x - 1.0 <= other.x)
            return (true);
          else
            return (false);
        }
    }
  return (false);
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
  if (this->mv == VERTICAL)
    this->y += this->moveSpeed * static_cast<double>(this->direction);
  else
    this->x += this->moveSpeed * static_cast<double>(this->direction);
  if (map->at(1, static_cast<size_t>(this->x), static_cast<size_t>(this->y)).getTypeEv() == arcade::TileTypeEvolution::FOOD)
    {
      map->at(1, static_cast<size_t>(this->x), static_cast<size_t>(this->y)).set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::EMPTY, arcade::Color::Black, false, 0, 0, 0.0, 0.0);
      return (1);
    }
  this->lifeDuration--;
  this->printOnMap(map);
  return (0);
}

bool  sf::Shot::isAlive()
{
  return (this->lifeDuration > 0);
}

double  sf::Shot::getX() const
{
  return (this->x);
}

double  sf::Shot::getY() const
{
  return (this->y);
}