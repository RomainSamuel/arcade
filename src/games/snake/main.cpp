#include <iostream>
#include "Game.hh"

void  display(arcade::IGame *snake)
{
  int type;

  for (size_t y = 0; y < snake->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < snake->getCurrentMap().getWidth(); x++)
        {
          if (snake->getCurrentMap().at(1, x, y).getSpriteId() != 0)
            type = snake->getCurrentMap().at(1, x, y).getSpriteId();
          else
            type = snake->getCurrentMap().at(0, x, y).getSpriteId();
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *snake = new arcade::Game();

  display(snake);
  std::cout << std::endl;
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  snake->process();
  return (0);
}
