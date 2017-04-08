#include "CentipedePart.hh"

centipede::CentipedePart::CentipedePart(int x,
                                        int y,
                                        int id,
                                        bool isLeader,
                                        bool isFollowed,
                                        arcade::Map &map,
                                        size_t initialMoveCD,
                                        int direction)
  : x(x), y(y), id(id), isLeader(isLeader), isFollowed(isFollowed), map(map), initialMoveCD(initialMoveCD), direction(direction)
{
}

centipede::CentipedePart::~CentipedePart()
{
}

int  centipede::CentipedePart::getX() const
{
  return (this->x);
}

int  centipede::CentipedePart::getY() const
{
  return (this->y);
}

int   centipede::CentipedePart::getId() const
{
  return (this->id);
}

void  centipede::CentipedePart::setFollower(std::shared_ptr<CentipedePart> &follower)
{
  this->follower = follower;
}
#include <iostream>
void  centipede::CentipedePart::die()
{
  std::cout << "yay" << std::endl;
  this->eraseFromMap();
  this->map.at(0, this->x, this->y).set(arcade::TileType::OBSTACLE,
                                        arcade::TileTypeEvolution::OBSTACLE,
                                        arcade::Color::White,
                                        false,
                                        1,
                                        5,
                                        0.0,
                                        0.0);
  this->follower->isLeader = true;
}

void  centipede::CentipedePart::printOnMap()
{
  if (this->x >= 0 && this->x < 40 && this->y >= 0 && this->y < 40)
    {
      this->map.at(1, this->x, this->y).set(arcade::TileType::EMPTY,
                                            arcade::TileTypeEvolution::ENEMY,
                                            arcade::Color::Red,
                                            false,
                                            2,
                                            0,
                                            0.0,
                                            0.0);
    }
}

void  centipede::CentipedePart::eraseFromMap()
{
  if (this->x >= 0 && this->x < 40 && this->y >= 0 && this->y < 40)
    {
      this->map.at(1, this->x, this->y).set(arcade::TileType::EMPTY,
                                            arcade::TileTypeEvolution::EMPTY,
                                            arcade::Color::Black,
                                            false,
                                            0,
                                            0,
                                            0.0,
                                            0.0);
    }
}

void  centipede::CentipedePart::move()
{
  this->eraseFromMap();
  if (this->y < 0)
    {
      this->y++;
      return;
    }
  if (this->x + this->direction < 0 ||
      this->x + this->direction >= 40 ||
      this->map.at(0, this->x + this->direction, this->y).getTypeEv() == arcade::TileTypeEvolution::OBSTACLE)
    {
      this->direction = - this->direction;
      this->y++;
    }
  else
    this->x += this->direction;
  this->printOnMap();
}
