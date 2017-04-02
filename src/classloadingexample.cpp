#include <dlfcn.h>
#include <cstddef>
#include <iostream>
#include "../includes/common/IGame.hpp"

int main()
{
  void *hndl = dlopen("../resources/games/lib_arcade_snake.so", RTLD_NOW);
  if(hndl == NULL){
    std::cerr << dlerror() << std::endl;
    exit(-1);
  }
  void *mkr = dlsym(hndl, "maker");
  arcade::IGame *snake = reinterpret_cast<arcade::IGame *(*)()>(mkr)();
  printf("%d\n", snake->getCurrentMap().at(0, 0, 0).getTypeEv());
}
