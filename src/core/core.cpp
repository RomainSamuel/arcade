//
// Created by maud on 22/03/17.
//

#include <fstream>
#include <iostream>
#include "Core.hh"

arcade::Core::Core(const std::string _lib, const int _level, const int _volume)
{
    std::ifstream fs(_lib);

    if (_lib.compare(_lib.size() - 3, 3, ".so") != 0
        || _lib.compare(0, 11, "lib_arcade_") != 0)
    {
        std::cerr << "Usage : ./arcade lib_arcade_XXXX.so" << std::endl;
        exit(1);
    }
    if (!fs.is_open())
    {
        std::cerr << "Library : " << _lib << " doesn't exist!" << std::endl;
        exit(1);
    }
    level = _level;
    volume = _volume;
    std::cout << "lib = " << _lib << std::endl;
    std::cout << "Level = " << level << std::endl;
    std::cout << "Volume = " << volume << std::endl;
    gameState = arcade::GameState::MENU;
}

arcade::Core::~Core()
{

}