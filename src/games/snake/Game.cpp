#include "Game.hh"

arcade::Game::Game()
{
  this->_map = std::unique_ptr<IMap>(new Map(10, 10, 2));
  this->_state = NONE;
}

arcade::Game::~Game()
{
}

arcade::GameState arcade::Game::getGameState() const
{
  return (_state);
}

void  arcade::Game::notifyEvent(std::vector<arcade::Event> &&events)
{
  (void)events;
}

void  arcade::Game::notifyNetwork(std::vector<arcade::NetworkPacket> &&)
{
}

std::vector<arcade::NetworkPacket>&& arcade::Game::getNetworkToSend()
{
  return (std::move(std::vector<arcade::NetworkPacket>()));
}

void  arcade::Game::process()
{
}

std::vector<std::string> arcade::Game::getSoundsToLoad() const
{
  std::vector<std::string>  sounds;

  return (sounds);
}

std::vector<int>&& arcade::Game::getSoundsToPlay()
{
  return (std::move(std::vector<int>()));
}

arcade::IMap const &arcade::Game::getCurrentMap() const
{
  return (*this->_map);
}

arcade::IGUI const &arcade::Game::getGUI() const
{
  return (*this->_gui);
}

extern "C" arcade::IGame *maker()
{
  return (new arcade::Game());
}
