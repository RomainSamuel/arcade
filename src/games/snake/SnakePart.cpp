#include <iostream>
#include "SnakePart.hh"

snake::SnakePart::SnakePart(size_t x, size_t y, PartType type, Direction direction)
{
  this->x = x;
  this->y = y;
  this->type = type;
  this->direction = direction;
  this->pos[snake::Direction::NORTH] = std::pair<int, int>(0, -1);
  this->pos[snake::Direction::EAST] = std::pair<int, int>(1, 0);
  this->pos[snake::Direction::SOUTH] = std::pair<int, int>(0, 1);
  this->pos[snake::Direction::WEST] = std::pair<int, int>(-1, 0);
}

snake::SnakePart::~SnakePart()
{
}

// GETTERS
size_t  snake::SnakePart::getX() const
{
  return (this->x);
}

size_t  snake::SnakePart::getY() const
{
  return (this->y);
}

snake::PartType  snake::SnakePart::getType() const
{
  return (this->type);
}

snake::Direction  snake::SnakePart::getDirection() const
{
  return (this->direction);
}

std::string snake::SnakePart::getAssociatedSprite(std::unique_ptr<snake::SnakePart> &prev, std::unique_ptr<snake::SnakePart> &next) const
{
  return (std::string());
}

arcade::Color snake::SnakePart::getAssociatedColor() const
{
  if (this->type == snake::PartType::HEAD)
    return (arcade::Color::Red);
  else
    return (arcade::Color::Green);
}

//SETTERS
void  snake::SnakePart::setX(size_t x)
{
  this->x = x;
}

void  snake::SnakePart::setY(size_t y)
{
  this->y = y;
}

void  snake::SnakePart::setPartType(PartType type)
{
  this->type = type;
}

void  snake::SnakePart::setDirection(Direction direction)
{
  if (static_cast<int>(this->direction) + 2 == static_cast<int>(direction) ||
      static_cast<int>(this->direction) - 2 == static_cast<int>(direction))
    return;
  this->direction = direction;
}

// ACTIONS
void  snake::SnakePart::eraseFromMap(std::list<std::unique_ptr<SnakePart>> &list,
                                     std::unique_ptr<arcade::Map> &map)
{
  for (std::list<std::unique_ptr<SnakePart>>::iterator it = list.begin(); it != list.end(); it++)
    {
      map->at(1, it->get()->getX(), it->get()->getY()).setType(arcade::TileType::EMPTY);
      map->at(1, it->get()->getX(), it->get()->getY()).setTypeEv(arcade::TileTypeEvolution::EMPTY);
      map->at(1, it->get()->getX(), it->get()->getY()).setHasSprite(false);
      map->at(1, it->get()->getX(), it->get()->getY()).setSpriteId(0);
      map->at(1, it->get()->getX(), it->get()->getY()).setColor(arcade::Color::Transparent);
    }
}

void  snake::SnakePart::printOnMap(std::list<std::unique_ptr<SnakePart>> &list,
                                     std::unique_ptr<arcade::Map> &map)
{
  for (std::list<std::unique_ptr<SnakePart>>::iterator it = list.begin(); it != list.end(); it++)
    {
      map->at(1, it->get()->getX(), it->get()->getY()).setType(arcade::TileType::EMPTY);
      map->at(1, it->get()->getX(), it->get()->getY()).setTypeEv(arcade::TileTypeEvolution::PLAYER);
      map->at(1, it->get()->getX(), it->get()->getY()).setHasSprite(false);
      map->at(1, it->get()->getX(), it->get()->getY()).setSpriteId(7);
      map->at(1, it->get()->getX(), it->get()->getY()).setColor(this->getAssociatedColor());
    }
}

void  snake::SnakePart::goLeft()
{
  int dir;

  dir = static_cast<int>(this->direction);
  if (dir == 0)
    dir = 3;
  else
    dir--;
  this->direction = static_cast<snake::Direction>(dir);
}

void  snake::SnakePart::goRight()
{
  int dir;

  dir = static_cast<int>(this->direction);
  if (dir == 3)
    dir = 0;
  else
    dir++;
  this->direction = static_cast<snake::Direction>(dir);
}

void  snake::SnakePart::follow(std::unique_ptr<snake::SnakePart> &prev)
{
  size_t  prev_x;
  size_t  prev_y;

  prev_x = prev->x - this->pos[prev->direction].first;
  prev_y = prev->y - this->pos[prev->direction].second;
  if (this->x == prev_x && this->y - 1 == prev_y)
    this->direction = snake::Direction::NORTH;
  else if (this->x + 1 == prev_x && this->y == prev_y)
    this->direction = snake::Direction::EAST;
  else if (this->x == prev_x && this->y + 1 == prev_y)
    this->direction = snake::Direction::SOUTH;
  else
    this->direction = snake::Direction::WEST;
  this->x = prev_x;
  this->y = prev_y;
}

int snake::SnakePart::lead(std::list<std::unique_ptr<SnakePart>> &list,
                           std::unique_ptr<arcade::Map> &map,
                           std::unique_ptr<snake::Food> &food)
{
  size_t  next_x = this->x + this->pos[this->direction].first;
  size_t  next_y = this->y + this->pos[this->direction].second;

  if (map->at(0, next_x, next_y).getTypeEv() == arcade::TileTypeEvolution::BLOCK ||
      map->at(1, next_x, next_y).getTypeEv() == arcade::TileTypeEvolution::PLAYER)
    return (-1);
  this->x += this->pos[this->direction].first;
  this->y += this->pos[this->direction].second;
  for (std::list<std::unique_ptr<snake::SnakePart>>::iterator it = list.begin(); it != list.end(); it++)
    {
      if (it != list.begin())
        it->get()->follow(*std::prev(it, 1));
    }
  if (this->x == food->getX() && food->getY())
    return (1);
  else
    return (0);
}

int snake::SnakePart::move(std::list<std::unique_ptr<SnakePart>> &list,
                           std::unique_ptr<arcade::Map> &map,
                           std::unique_ptr<snake::Food> &food)
{
  int ret;

  this->eraseFromMap(list, map);
  ret = this->lead(list, map, food);
  if (ret == -1)
    {
      this->printOnMap(list, map);
      return (-1);
    }
  if (ret == 1)
    {
      this->addToBack(list);
      this->printOnMap(list, map);
      if (food->beEaten(map) == 1)
        return (2);
    }
  else
    this->printOnMap(list, map);
  return (ret);
}

void  snake::SnakePart::addToBack(std::list<std::unique_ptr<SnakePart>> &list)
{
  list.push_back(std::make_unique<snake::SnakePart>(list.back()->x - list.back()->pos[list.back()->direction].first,
                                                    list.back()->y - list.back()->pos[list.back()->direction].second,
                                                    snake::PartType::TAIL,
                                                    list.back()->direction));
}
