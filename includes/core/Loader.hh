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
    public:
        static Loader   &getInstance()
        {
            static Loader  instance;
            return instance;
        }
    protected:
        std::map<std::string, void*>    _libPathHandle;
        void                            *_currentLibHandle;
        std::string                     _currentLib;
        std::map<std::string, void*>    _gamePathHandle;
        void                            *_currentGameHandle;
        std::string                     _currentGame;
        
    public:
        Loader();
        virtual ~Loader();
        Loader(const arcade::Loader &);
        Loader &operator=(const arcade::Loader &);

        void                        setCurrentLib(std::string const &);
        std::map<std::string, void*> getLibPathHandle() const;
        void                        *getCurrentLibHandle() const;
        std::string                 getCurrentLib() const;
        std::map<std::string, void*> getGamePathHandle() const;
        void                        *getCurrentGameHandle() const;
        std::string                 getCurrentGame() const;
        void                        *getSym(void *) const;
    };
}

#endif /* !LOADER_HH_ */