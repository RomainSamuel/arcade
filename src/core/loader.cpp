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
#include "Exceptions.hh"

arcade::Loader::Loader()
:   _libPath {},
    _currentLib(),
    _gamePath {},
    _currentGame()
{
    DIR *dir;
    dirent  *entry;
    std::size_t  pos;

    if ((dir = opendir("lib")) == nullptr)
        throw arcade::Error("Failed open lib directory");
    while ((entry = readdir(dir)) != nullptr)
    {
        pos = std::string(entry->d_name).find(".so");
        if (pos != std::string::npos)
            _libPath.push_back(std::string(entry->d_name));
    }
    closedir(dir);
}

arcade::Loader::~Loader()
{
}

arcade::Loader::Loader(const arcade::Loader &copy)
:   _libPath(copy.getLibPath()),
    _currentLib(copy.getCurrentLib()),
    _gamePath(copy.getGamePath()),
    _currentGame(copy.getCurrentGame())
{
}

arcade::Loader  &arcade::Loader::operator=(const arcade::Loader &copy)
{
    (void) copy;
    return (*this);
}

void    arcade::Loader::setCurrentLib(std::string const &lib)
{
    _currentLib = lib;
}

std::vector<std::string>    arcade::Loader::getLibPath() const
{
    return (_libPath);
}

std::string     arcade::Loader::getCurrentLib() const
{
    return (_currentLib);
}

std::vector<std::string>    arcade::Loader::getGamePath() const
{
    return (_gamePath);
}
 
std::string     arcade::Loader::getCurrentGame() const
{
    return (_currentGame);
}

void    *arcade::Loader::getSym(std::string const &lib) const
{
    void    *mkr;
    void    *handle;

    if ((handle = dlopen(lib.c_str(), RTLD_NOW)) == NULL)
        throw arcade::Error("dlopene Failed");
    if ((mkr = dlsym(handle, "loader")) == NULL)
        throw arcade::Error("dlsym Failed");
    return (mkr);
}