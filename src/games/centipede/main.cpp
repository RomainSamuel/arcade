#include <iostream>
#include "CentipedeGame.hh"

void  display(arcade::IGame *centipede)
{
  int type;

  for (size_t y = 0; y < centipede->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < centipede->getCurrentMap().getWidth(); x++)
        {
          type = 0;
          for (size_t i = 0; i < centipede->getCurrentMap().getLayerNb(); i++)
            {
              if (centipede->getCurrentMap().at(i, x, y).getSpriteId() != 0)
                type = centipede->getCurrentMap().at(i, x, y).getSpriteId();
            }
          if (type > 0)
            std::cout << type << " ";
          else
            std::cout << "." << " ";
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *centipede = new arcade::CentipedeGame();

  display(centipede);
  std::cout << std::endl;
  for (size_t i = 0; i < 15; i++)
    {
      centipede->process();
      display(centipede);
      std::cout << std::endl;
    }
  return (0);
}
