#ifndef GAME_HH_
# define GAME_HH_

#include <memory>
#include <utility>
#include <map>
#include <functional>
#include <array>
#include "Map.hh"
#include "GUI.hh"
#include "IGame.hh"
#include "Centipede.hh"

namespace arcade
{
  class   CentipedeGame : public IGame
  {
    std::unique_ptr<Map>                          _map;
    std::unique_ptr<GUI>                          _gui;
    GameState                                     _state;
    std::vector<int>                              _soundsToPlay;
    size_t                                        _eaten;
    size_t                                        _score;
    std::vector<arcade::Event>                    _events;
    std::array<arcade::Event, 4>                  _eventsBound;
    double                                        _cd;
    double                                        _cdRemaining;
    size_t                                        _initialCentipedeCD;
    size_t                                        _centipedeCD;
    std::vector<std::shared_ptr<centipede::CentipedePart>>  _centipedes;

  public:
    CentipedeGame();
    virtual ~CentipedeGame();

    virtual GameState                   getGameState() const;
    virtual void                        notifyEvent(std::vector<Event> &&events);
    virtual void                        notifyNetwork(std::vector<NetworkPacket> &&events);
    virtual std::vector<NetworkPacket>  &&getNetworkToSend();
    virtual void                        process();
    virtual std::vector<std::unique_ptr<ISprite>> &&getSpritesToLoad() const;
    virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;
    virtual std::vector<int>            &&getSoundsToPlay();
    virtual IMap const                  &getCurrentMap() const;
    virtual IGUI                        &getGUI();

    Map                                 &getMap();
    int                                 getActionToPerform(arcade::Event) const;
    void                                createCentipede(size_t nb);
  };
}

#endif
