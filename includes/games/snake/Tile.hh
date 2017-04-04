#ifndef TILE_HPP_
# define TILE_HPP_

#include "ITile.hpp"

namespace arcade
{
  class   Tile : public ITile
  {
    TileType  _type;
    TileTypeEvolution _typeEv;
    Color     _color;
    size_t    _spriteId;
    size_t    _spritePos;

  public:
    Tile();
    Tile(TileType, TileTypeEvolution, Color, size_t, size_t);
    virtual ~Tile();

    virtual TileType getType() const;
    virtual void setType(TileType type);

    virtual TileTypeEvolution getTypeEv() const;
    virtual void setTypeEv(TileTypeEvolution type);

    virtual Color getColor() const;
    virtual void setColor(union Color color);

    virtual size_t getSpriteId() const;
    virtual void setSprite(size_t id);

    virtual size_t getSpritePos() const;
    virtual void setSpritePos(size_t pos);

    virtual void   nextSprite();
    virtual void   prevSprite();
  };
}

#endif /* TILE_HPP_ */
