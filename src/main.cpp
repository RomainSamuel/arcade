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
#include "Core.hh"

int	main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Usage : ./arcade lib_arcade_XXX.so" << std::endl;
        return 1;
    }
    arcade::Core(av[1], 19, 27);
    return 0;
}
