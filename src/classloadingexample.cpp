#include <dlfcn.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../includes/Event.hpp"
#include "../includes/common/IGame.hpp"
#include "../includes/common/IMap.hpp"

void  display(arcade::IGame *snake)
{
  size_t type;

  for (size_t y = 0; y < snake->getCurrentMap().getHeight(); y++)
    {
      for (size_t x = 0; x < snake->getCurrentMap().getWidth(); x++)
        {
          type = snake->getCurrentMap().at(0, x, y).getSpriteId();
          if (snake->getCurrentMap().at(1, x, y).getSpriteId() != 0)
            type = snake->getCurrentMap().at(1, x, y).getSpriteId();
          printf("%ld ", type);
        }
      printf("\n");
    }
}

int main()
{
  std::srand(std::time(0));
  void *hndl = dlopen("../resources/games/lib_arcade_snake.so", RTLD_NOW);
  if(hndl == NULL){
    std::cerr << dlerror() << std::endl;
    exit(-1);
  }

  void *mkr = dlsym(hndl, "maker");
  arcade::IGame *snake = reinterpret_cast<arcade::IGame *(*)()>(mkr)();

  display(snake);
  std::cout << std::endl;
  snake->process();
  display(snake);
  std::cout << std::endl;
  snake->process();
  display(snake);
  std::cout << std::endl;
}
