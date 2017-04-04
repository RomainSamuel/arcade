#ifndef LAYER_HPP_
# define LAYER_HPP_

# include "Tile.hh"
# include "ILayer.hpp"

namespace arcade
{
  class Layer : public ILayer
  {
    size_t  _width;
    size_t  _height;
    std::vector<std::vector<std::unique_ptr<ITile>>>  _rows;

  public:
    Layer(size_t, size_t, bool);
    virtual ~Layer();

    virtual std::vector<std::unique_ptr<ITile>> const &operator[](int n) const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;

    std::vector<std::unique_ptr<ITile>> &operator[](int n);
  };
}

#endif
