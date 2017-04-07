#include <iostream>
#include "CentipedeGame.hh"

void  display(arcade::IGame *centipede)
{
  int type;

  for (size_t y = 0; y < centipede->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < centipede->getCurrentMap().getWidth(); x++)
        {
          if (centipede->getCurrentMap().at(1, x, y).getSpriteId() != 0)
            type = centipede->getCurrentMap().at(1, x, y).getSpriteId();
          else
            type = centipede->getCurrentMap().at(0, x, y).getSpriteId();
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *centipede = new arcade::CentipedeGame();

  display(centipede);
  std::cout << std::endl;
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  centipede->process();
  return (0);
}
