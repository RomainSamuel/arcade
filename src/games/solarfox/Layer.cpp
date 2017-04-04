#include "Layer.hh"

arcade::Layer::Layer(size_t width, size_t height, bool printBaseMap)
{
  for (size_t y = 0; y < height; y++)
    {
      this->_rows.push_back(std::vector<std::unique_ptr<arcade::ITile>>());
      for (size_t x = 0; x < width; x++)
        {
          if (!printBaseMap || (y > 0 && x > 0 && y < height - 1 && x < width - 1))
            this->_rows[y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY,
                                                                    arcade::TileTypeEvolution::EMPTY,
                                                                    arcade::Color::Black,
                                                                    0,
                                                                    0));
          else
            this->_rows[y].push_back(std::make_unique<arcade::Tile>(arcade::TileType::BLOCK,
                                                                    arcade::TileTypeEvolution::BLOCK,
                                                                    arcade::Color::White,
                                                                    0,
                                                                    0));
        }
    }
}

arcade::Layer::~Layer()
{
}

std::vector<std::unique_ptr<arcade::ITile>> const &arcade::Layer::operator[](int n) const
{
  return (this->_rows[n]);
}

std::vector<std::unique_ptr<arcade::ITile>> &arcade::Layer::operator[](int n)
{
  return (this->_rows[n]);
}

size_t  arcade::Layer::getWidth() const
{
  return (this->_width);
}

size_t  arcade::Layer::getHeight() const
{
  return (this->_height);
}
