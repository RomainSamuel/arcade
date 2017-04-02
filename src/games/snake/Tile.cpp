#include "Tile.hh"

arcade::Tile::Tile()
{
  this->_type = arcade::TileType::EMPTY;
  this->_typeEv = arcade::TileTypeEvolution::EMPTY;
  this->_spriteId = 0;
  this->_spritePos = 0;
}

arcade::Tile::Tile(TileType type,
                   TileTypeEvolution typeEv,
                   Color color,
                   size_t spriteId,
                   size_t spritePos)
{
  this->_type = type;
  this->_typeEv = typeEv;
  this->_color = color;
  this->_spriteId = spriteId;
  this->_spritePos = spritePos;
}

arcade::Tile::~Tile()
{
}

arcade::TileType arcade::Tile::getType() const
{
  return (this->_type);
}

void  arcade::Tile::setType(TileType type)
{
  this->_type = type;
}

arcade::TileTypeEvolution arcade::Tile::getTypeEv() const
{
  return (this->_typeEv);
}

void  arcade::Tile::setTypeEv(TileTypeEvolution typeEv)
{
  this->_typeEv = typeEv;
}

arcade::Color arcade::Tile::getColor() const
{
  return (this->_color);
}

void  arcade::Tile::setColor(union Color color)
{
  this->_color = color;
}

size_t  arcade::Tile::getSpriteId() const
{
  return (this->_spriteId);
}

void  arcade::Tile::setSprite(size_t spriteId)
{
  this->_spriteId = spriteId;
}

size_t  arcade::Tile::getSpritePos() const
{
  return (this->_spritePos);
}

void  arcade::Tile::setSpritePos(size_t spritePos)
{
  this->_spriteId = spritePos;
}

void  arcade::Tile::nextSprite()
{
  this->_spritePos++;
}

void  arcade::Tile::prevSprite()
{
  this->_spritePos--;
}
