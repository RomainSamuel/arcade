#include "Map.hh"

arcade::Map::Map(size_t width, size_t height)
{
  this->_width = width;
  this->_height = height;
  this->_layersNb = 2;

  this->createLayer(0);
  this->createLayer(1);
  // this->_layers.push_back(std::make_shared<arcade::Layer>(width, height, true));
  // this->_layers.push_back(std::make_shared<arcade::Layer>(width, height, false));
}

arcade::Map::~Map()
{
}

arcade::ITile const &arcade::Map::at(size_t layer, size_t x, size_t y) const
{
  return (*this->_layers[layer][x][y]);
}

arcade::ITile &arcade::Map::at(size_t layer, size_t x, size_t y)
{
  return (*this->_layers[layer][x][y]);
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

void arcade::Map::createLayer(size_t layer)
{
  this->_layers.push_back(std::vector<std::vector<std::unique_ptr<ITile>>>());
  for (size_t y = 0; y < this->_height; y++)
    {
      this->_layers[layer].push_back(std::vector<std::unique_ptr<arcade::ITile>>());
      for (size_t x = 0; x < this->_width; x++)
        {
          if (layer > 0 || (y > 0 && x > 0 && y < this->_height - 1 && x < this->_width - 1))
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY,
                                                                    arcade::TileTypeEvolution::EMPTY,
                                                                    arcade::Color::Black,
                                                                    0,
                                                                    0));
          else
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::BLOCK,
                                                                    arcade::TileTypeEvolution::BLOCK,
                                                                    arcade::Color::White,
                                                                    0,
                                                                    0));
        }
    }
}
