#ifndef MAP_HPP_
# define MAP_HPP_

# include <memory>
# include "Layer.hh"
# include "IMap.hpp"

namespace arcade
{
  class   Map : public IMap
  {
    size_t  _width;
    size_t  _height;
    size_t  _layersNb;
    std::vector<std::shared_ptr<ILayer>> _layers;

  public:
    Map(size_t, size_t, size_t);
    virtual ~Map();

    ITile const &at(size_t layer, size_t x, size_t y) const;
    virtual size_t getLayerNb() const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;
  };
}

#endif
