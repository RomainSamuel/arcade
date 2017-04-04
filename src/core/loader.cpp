//
// Author: Maud Marel 
// Date: 2017-04-03 10:09:45 
//
// Last Modified by:   Maud Marel 
// Last Modified time: 2017-04-03 10:09:45
//

#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "Loader.hh"

arcade::Loader::Loader(const std::string &current)
:   _libPathHandle {},
    _currentLibHandle(0),
    _currentLib(current),
    _gamePathHandle {},
    _currentGameHandle(0),
    _currentGame(0)
{
    DIR *dir;
    dirent  *entry;
    std::size_t  pos;

    std::cout << "Loader" << std::endl;
    if ((dir = opendir("lib")) == nullptr)
        exit(1);
    while ((entry = readdir(dir)) != nullptr)
    {
        pos = std::string(entry->d_name).find(".so");
        if (pos != std::string::npos)
            _libPathHandle["lib/" + std::string(entry->d_name)] = dlopen(("lib" + std::string(entry->d_name)).c_str(), RTLD_LAZY | RTLD_GLOBAL);
    }
    closedir(dir);
}

arcade::Loader::~Loader()
{
}

arcade::Loader::Loader(const arcade::Loader &copy)
:   _libPathHandle(copy.getLibPathHandle()),
    _currentLibHandle(copy.getCurrentLibHandle()),
    _currentLib(copy.getCurrentLib()),
    _gamePathHandle(copy.getGamePathHandle()),
    _currentGameHandle(copy.getCurrentGameHandle()),
    _currentGame(copy.getCurrentGame())
{
}

arcade::Loader  &arcade::Loader::operator=(const arcade::Loader &copy)
{
    (void) copy;
    return (*this);
}

std::map<std::string, void*>    arcade::Loader::getLibPathHandle() const
{
    return (_libPathHandle);
}

void    *arcade::Loader::getCurrentLibHandle() const
{
    return (_currentLibHandle);
}

std::string     arcade::Loader::getCurrentLib() const
{
    return (_currentLib);
}

std::map<std::string, void*>    arcade::Loader::getGamePathHandle() const
{
    return (_gamePathHandle);
}
    
void    *arcade::Loader::getCurrentGameHandle() const
{
    return (_currentGameHandle);
}

std::string     arcade::Loader::getCurrentGame() const
{
    return (_currentGame);
}