#include <iostream>
#include "SfGame.hh"

void  display(arcade::IGame *sf)
{
  for (size_t y = 0; y < sf->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < sf->getCurrentMap().getWidth(); x++)
        {
          if (sf->getCurrentMap().at(3, x, y).hasSprite())
            std::cout << sf->getCurrentMap().at(3, x, y).getSpriteId() << " ";
          else
            std::cout << ". ";
        }
      std::cout << std::endl;
    }
  std::cout << std::endl;
  for (size_t y = 0; y < sf->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < sf->getCurrentMap().getWidth(); x++)
        {
          if (sf->getCurrentMap().at(3, x, y).hasSprite())
            std::cout << sf->getCurrentMap().at(3, x, y).getSpritePos() << " ";
          else
            std::cout << ". ";
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *sf = new arcade::SfGame();

  sf->getSpritesToLoad();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  // sf->process();
  // display(sf);
  // std::cout << std::endl;
  return (0);
}
