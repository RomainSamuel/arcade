#ifndef GAME_HH_
# define GAME_HH_

#include <memory>
#include <utility>
#include "Map.hh"
#include "GUI.hh"
#include "IGame.hpp"

namespace arcade
{
  class   Game : public IGame
  {
    std::unique_ptr<IMap> _map;
    std::unique_ptr<IGUI> _gui;
    GameState             _state;
    std::vector<int>      _soundsToPlay;

  public:
    Game();
    virtual ~Game();

    virtual GameState                   getGameState() const;
    virtual void                        notifyEvent(std::vector<Event> &&events);
    virtual void                        notifyNetwork(std::vector<NetworkPacket> &&events);
    virtual std::vector<NetworkPacket>  &&getNetworkToSend();
    virtual void                        process();
    virtual std::vector<std::string>    getSoundsToLoad() const;
    virtual std::vector<int>            &&getSoundsToPlay();
    virtual IMap const                  &getCurrentMap() const;
    virtual IGUI const                  &getGUI() const;
  };
}

#endif
