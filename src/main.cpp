//
// main.cpp for main in /home/marwane/Projets/cpp_arcade/src
// 
// Made by Marwane
// Login   <marwane.khsime@epitech.eu>
// 
// Started on  Tue Mar 21 21:25:10 2017 Marwane
// Last update Tue Mar 21 21:25:31 2017 Marwane
//

#include <iostream>
#include <memory>
#include <dlfcn.h>
#include "Core.hh"
#include "IGfxLib.hpp"

int	main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        std::cerr << "Usage : ./arcade lib/lib_arcade_XXX.so" << std::endl;
        return 1;
    }
    std::unique_ptr<arcade::Core> core = std::make_unique<arcade::Core>(av[1], 50);
    core->menu();
    //core->play();
    return 0;
}
