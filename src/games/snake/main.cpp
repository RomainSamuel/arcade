#include <iostream>
#include "SnakeGame.hh"

void  display(arcade::IGame *snake)
{
  int type;
  const arcade::Color color;

  for (size_t y = 0; y < snake->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < snake->getCurrentMap().getWidth(); x++)
        {
          type = 0;
          if (snake->getCurrentMap().at(1, x, y).hasSprite())
            type = snake->getCurrentMap().at(1, x, y).getSpriteId();
          else
            type = snake->getCurrentMap().at(0, x, y).getSpriteId();
          std::cout << type << " ";
        }
      std::cout << std::endl;
    }

  std::cout << std::endl;
  for (size_t y = 0; y < snake->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < snake->getCurrentMap().getWidth(); x++)
        {
          if (snake->getCurrentMap().at(1, x, y).hasSprite())
            type = snake->getCurrentMap().at(1, x, y).getSpritePos();
          else
            type = snake->getCurrentMap().at(0, x, y).getSpritePos();
          std::cout << type << " ";
        }
      std::cout << std::endl;
    }
}

int main()
{
  arcade::IGame  *snake = new arcade::SnakeGame();

  display(snake);
  // std::cout << std::endl;
  // snake->process();
  // display(snake);
  // std::cout << std::endl;
  // snake->process();
  // display(snake);
  // std::cout << std::endl;
  // snake->process();
  // display(snake);
  // std::cout << std::endl;
  // snake->process();
  // display(snake);
  // std::cout << std::endl;
  return (0);
}
