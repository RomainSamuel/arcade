#include "Player.hh"

sf::Player::Player()
{
  this->x = 10.5;
  this->y = 10.5;
  this->xCell = 10;
  this->yCell = 10;
  this->direction = sf::Direction::NORTH;
  this->pos[sf::Direction::NORTH] = std::pair<double, double>(0, -0.05);
  this->pos[sf::Direction::EAST] = std::pair<double, double>(0.05, 0);
  this->pos[sf::Direction::SOUTH] = std::pair<double, double>(0, 0.05);
  this->pos[sf::Direction::WEST] = std::pair<double, double>(-0.05, 0);
  this->fire_cd = 18;
  this->fcd = 0;
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

bool  sf::Player::fire()
{
  if (this->fcd == 0)
    {
      this->shot = std::make_unique<sf::Shot>(1,
                                              this->x,
                                              this->y,
                                              40,
                                              (this->direction == EAST || this->direction == SOUTH) ? 1 : -1,
                                              0.015,
                                              (this->direction == NORTH || this->direction == SOUTH) ? VERTICAL : HORIZONTAL,
                                              true);
      this->fcd = this->fire_cd;
      return (true);
    }
  return (false);
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
      if (map->at(0, this->xCell, this->yCell).getTypeEv() == arcade::TileTypeEvolution::BLOCK ||
          map->at(1, this->xCell, this->yCell).getTypeEv() == arcade::TileTypeEvolution::FOOD)
        ret = -1;
    }
  this->x = next_x;
  this->y = next_y;
  if (this->fcd != 0)
    this->fcd--;
  this->printOnMap(map);
  return (ret);
}

bool  sf::Player::hasShot() const
{
  if (this->shot == nullptr)
    return (false);
  else
    return (true);
}

sf::Shot  &sf::Player::getShot() const
{
  return (*this->shot);
}

bool  sf::Player::checkShotDuration(std::unique_ptr<arcade::Map> &map)
{
  sf::Shot  *shot;

  if (this->shot->isAlive() == true)
    return (true);
  else
    {
      this->shot->eraseFromMap(map);
      shot = this->shot.release();
      delete shot;
      return (false);
    }
}

void  sf::Player::deleteShot()
{
  sf::Shot  *shot;

  shot = this->shot.release();
  delete shot;
}
