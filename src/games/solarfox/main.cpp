#include <iostream>
#include "SfGame.hh"

void  display(arcade::IGame *sf)
{
  int type;

  for (size_t y = 0; y < sf->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < sf->getCurrentMap().getWidth(); x++)
        {
          // type = 0;
          // if (sf->getCurrentMap().at(, x, y).hasSprite())
          std::cout << sf->getCurrentMap().at(2, x, y).hasSprite() << " ";
          // else
          //   std::cout << ". ";
          // type = 0;
          // for (size_t i = 0; i < sf->getCurrentMap().getLayerNb(); i++)
          //   {
          //     if (sf->getCurrentMap().at(i, x, y).hasSprite() == true)
          //       type = sf->getCurrentMap().at(i, x, y).getSpriteId();
          //   }
          // if (type > 0)
          //   std::cout << type << " ";
          // else
          //   std::cout << "." << " ";
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *sf = new arcade::SfGame();

  display(sf);
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
