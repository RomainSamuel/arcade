#include "Map.hh"

arcade::Map::Map(size_t width, size_t height, size_t lnb)
{
  this->_width = width;
  this->_height = height;
  this->_layersNb = lnb;

  for (size_t i = 0; i < lnb; i++)
    this->createLayer(i);
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
  this->_layers.push_back(std::vector<std::vector<std::unique_ptr<Tile>>>());
  for (size_t y = 0; y < this->_height; y++)
    {
      this->_layers[layer].push_back(std::vector<std::unique_ptr<arcade::Tile>>());
      for (size_t x = 0; x < this->_width; x++)
        {
          if (layer != 0)
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY,
                                                                             arcade::TileTypeEvolution::EMPTY,
                                                                             arcade::Color::Transparent,
                                                                             false,
                                                                             0,
                                                                             0,
                                                                             0.0,
                                                                             0.0));
          if (x > 2 && y > 2 && x + 3 < this->_width && y + 3 < this->_height)
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY,
                                                                             arcade::TileTypeEvolution::EMPTY,
                                                                             arcade::Color::Black,
                                                                             true,
                                                                             4 + (y * this->_height) + x,
                                                                             0,
                                                                             0.0,
                                                                             0.0));
          else
            this->_layers[layer][y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::BLOCK,
                                                                             arcade::TileTypeEvolution::BLOCK,
                                                                             arcade::Color::Black,
                                                                             true,
                                                                             4 + (y * this->_height) + x,
                                                                             0,
                                                                             0.0,
                                                                             0.0));
        }
    }
  if (layer == 1)
    {
      this->_layers[layer][3][5]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][7][5]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][5][3]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][10][7]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][12][14]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][3][11]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][15][16]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][13][10]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
      this->_layers[layer][8][13]->set(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::White, true, 0, 0, 0.0, 0.0);
    }
}
