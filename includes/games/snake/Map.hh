#ifndef MAP_HPP_
# define MAP_HPP_

# include <memory>
# include <vector>
# include "IMap.hpp"
# include "Tile.hh"

namespace arcade
{
  class   Map : public IMap
  {
    size_t  _width;
    size_t  _height;
    size_t  _layersNb;
    std::vector<std::vector<std::vector<std::unique_ptr<ITile>>>> _layers;

  public:
    Map(size_t, size_t);
    virtual ~Map();

    virtual ITile const &at(size_t layer, size_t x, size_t y) const;
    virtual size_t getLayerNb() const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;

    void  createLayer(size_t);
    ITile &at(size_t layer, size_t x, size_t y);
  };
}

#endif
