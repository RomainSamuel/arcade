//
// Author: Maud Marel 
// Date: 2017-04-03 10:10:55 
//
// Last Modified by:   Maud Marel 
// Last Modified time: 2017-04-03 10:10:55
//

#ifndef LOADER_HH_
# define LOADER_HH_

#include <map>
#include <string>

namespace arcade
{
    class Loader
    {
    private:
        std::map<std::string, void*>    _libPathHandle;
        void                            *_currentLibHandle;
        std::string                     _currentLib;
        std::map<std::string, void*>    _gamePathHandle;
        void                            *_currentGameHandle;
        std::string                     _currentGame;
        
    public:
        Loader(const std::string &);
        virtual ~Loader();
        Loader(const arcade::Loader &);
        Loader &operator=(const arcade::Loader &);

        std::map<std::string, void*> getLibPathHandle() const;
        void                        *getCurrentLibHandle() const;
        std::string                 getCurrentLib() const;
        std::map<std::string, void*> getGamePathHandle() const;
        void                        *getCurrentGameHandle() const;
        std::string                 getCurrentGame() const;
    };
}

#endif /* !LOADER_HH_ */