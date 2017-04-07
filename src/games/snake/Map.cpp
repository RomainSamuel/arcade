#include "Map.hh"

arcade::Map::Map(size_t width, size_t height, size_t lnb)
{
  this->_width = width;
  this->_height = height;
  this->_layersNb = lnb;

  this->createLayer(0);
  this->createLayer(1);
}

arcade::Map::~Map()
{
}

arcade::ITile const &arcade::Map::at(size_t layer, size_t x, size_t y) const
{
  return (*this->_layers[layer][x][y]);
}

arcade::Tile &arcade::Map::at(size_t layer, size_t x, size_t y)
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
  arcade::Color color = (layer == 0) ? arcade::Color(247, 230, 151) : arcade::Color::Transparent;

  this->_layers.push_back(std::vector<std::vector<std::unique_ptr<Tile>>>());
  for (size_t y = 0; y < this->_height; y++)
    {
      this->_layers[layer].push_back(std::vector<std::unique_ptr<arcade::Tile>>());
      for (size_t x = 0; x < this->_width; x++)
        {
          if (layer > 0 || (y > 0 && x > 0 && y < this->_height - 1 && x < this->_width - 1))
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY,
                                                                             arcade::TileTypeEvolution::EMPTY,
                                                                             color,
                                                                             false,
                                                                             0,
                                                                             0,
                                                                             0.0,
                                                                             0.0));
          else
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::BLOCK,
                                                                             arcade::TileTypeEvolution::BLOCK,
                                                                             arcade::Color(188, 174, 118),
                                                                             false,
                                                                             1,
                                                                             0,
                                                                             0.0,
                                                                             0.0));
        }
    }
}
