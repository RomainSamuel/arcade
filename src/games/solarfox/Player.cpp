#include "Player.hh"

sf::Player::Player()
{
  this->x = 10.5;
  this->y = 10.5;
  this->xCell = 10;
  this->yCell = 10;
  this->direction = sf::Direction::NORTH;
  this->pos[sf::Direction::NORTH] = std::pair<double, double>(0, -0.2);
  this->pos[sf::Direction::EAST] = std::pair<double, double>(0.2, 0);
  this->pos[sf::Direction::SOUTH] = std::pair<double, double>(0, 0.2);
  this->pos[sf::Direction::WEST] = std::pair<double, double>(-0.2, 0);
}

sf::Player::~Player()
{
}

sf::Direction  sf::Player::getDirection() const
{
  return (this->direction);
}

void  sf::Player::setDirection(sf::Direction direction)
{
  if (static_cast<int>(this->direction) + 2 == static_cast<int>(direction) ||
      static_cast<int>(this->direction) - 2 == static_cast<int>(direction))
    return;
  this->direction = direction;
}

void  sf::Player::printOnMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(2, this->xCell, this->yCell).set(arcade::TileType::EMPTY,
                                           arcade::TileTypeEvolution::PLAYER,
                                           arcade::Color::Red,
                                           false,
                                           1,
                                           0,
                                           this->x - 0.5 - static_cast<double>(this->xCell),
                                           this->y - 0.5 - static_cast<double>(this->yCell));
}

void  sf::Player::eraseFromMap(std::unique_ptr<arcade::Map> &map) const
{
  map->at(2, this->xCell, this->yCell).set(arcade::TileType::EMPTY,
                                           arcade::TileTypeEvolution::EMPTY,
                                           arcade::Color::Black,
                                           false,
                                           0,
                                           0,
                                           0.0,
                                           0.0);
}

int   sf::Player::move(std::unique_ptr<arcade::Map> &map)
{
  double  next_x = this->x + this->pos[this->direction].first;
  double  next_y = this->y + this->pos[this->direction].second;
  int     ret = 0;

  this->eraseFromMap(map);
  if (static_cast<int>(next_x) != this->xCell ||
      static_cast<int>(next_y) != this->yCell)
    {
      this->xCell = static_cast<int>(next_x);
      this->yCell = static_cast<int>(next_y);
      if (map->at(1, this->xCell, this->yCell).getTypeEv() == arcade::TileTypeEvolution::FOOD)
        {
          ret = 1;
          map->at(1, this->xCell, this->yCell).set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::EMPTY, arcade::Color::Black, false, 0, 0, 0.0, 0.0);
        }
      else if (map->at(0, this->xCell, this->yCell).getTypeEv() == arcade::TileTypeEvolution::BLOCK)
        ret = -1;
    }
  this->x = next_x;
  this->y = next_y;
  this->printOnMap(map);
  return (ret);
}
