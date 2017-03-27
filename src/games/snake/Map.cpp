#include "Map.hh"

arcade::Map::Map(size_t width, size_t height, size_t layersNb)
{
  this->_width = width;
  this->_height = height;
  this->_layersNb = layersNb;

  this->_layers.push_back(std::make_shared<arcade::Layer>(0));
  this->_layers.push_back(std::make_shared<arcade::Layer>(1));
}

arcade::Map::~Map()
{
}

arcade::ITile const &arcade::Map::at(size_t layer, size_t x, size_t y) const
{
  return (*(*this->_layers[layer])[x][y]);
}

size_t  arcade::Map::getLayerNb() const
{
  return (this->_layersNb);
}

size_t  arcade::Map::getWidth() const
{
  return (this->_width);
}

size_t  arcade::Map::getHeight() const
{
  return (this->_height);
}
