#include "Layer.hh"

arcade::Layer::Layer()
{
}

arcade::Layer::Layer(int n)
{
  size_t  i = -1;
  size_t  j = -1;

  if (n == 0)
    {
      while (++i < 10)
        {
          j = -1;
          this->_rows.push_back(std::vector<std::unique_ptr<arcade::ITile>>());
          while (++j < 10)
            {
              if (i > 0 && i < 9 && j > 0 && j < 9)
                this->_rows[i].push_back(std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::EMPTY, arcade::Color::White, 0, 0));
              else
                this->_rows[i].push_back(std::make_unique<arcade::Tile>(arcade::TileType::BLOCK, arcade::TileTypeEvolution::BLOCK, arcade::Color::Black, 0, 0));
            }
        }
    }
  else
    {
      while (++i < 10)
        {
          j = -1;
          this->_rows.push_back(std::vector<std::unique_ptr<arcade::ITile>>());
          while (++j < 10)
            this->_rows[i].push_back(std::make_unique<arcade::Tile>());
        }
      this->_rows[4][4] = std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::PLAYER, arcade::Color::Red, 0, 0);
      this->_rows[4][5] = std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::PLAYER, arcade::Color::Green, 0, 0);
      this->_rows[4][6] = std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::PLAYER, arcade::Color::Green, 0, 0);
      this->_rows[5][6] = std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::PLAYER, arcade::Color::Green, 0, 0);
      this->_rows[7][3] = std::make_unique<arcade::Tile>(arcade::TileType::EMPTY, arcade::TileTypeEvolution::FOOD, arcade::Color::Yellow, 0, 0);
    }
}

arcade::Layer::~Layer()
{
}

std::vector<std::unique_ptr<arcade::ITile>> const &arcade::Layer::operator[](int n) const
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
