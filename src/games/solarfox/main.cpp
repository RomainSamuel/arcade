#include <iostream>
#include "SfGame.hh"

void  display(arcade::IGame *sf)
{
  int type;

  for (size_t y = 0; y < sf->getCurrentMap().getHeight(); y++)
    {
      type = -1;
      for (size_t x = 0; x < sf->getCurrentMap().getWidth(); x++)
        {
          for (size_t l = 0; l < sf->getCurrentMap().getLayerNb(); l++)
            {
              if (sf->getCurrentMap().at(l, x, y).hasSprite())
                type = sf->getCurrentMap().at(l, x, y).getSpriteId();
            }
          if (type != -1)
            std::cout << type << " ";
          else
            std::cout << ". ";
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *sf = new arcade::SfGame();

  display(sf);
  std::cout << std::endl;
  for (int i = 0; i < 60; i++)
    {
      sf->process();
      display(sf);
      std::cout << std::endl;
    }
  return (0);
}
