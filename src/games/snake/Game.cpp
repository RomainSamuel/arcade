#include "Game.hh"

arcade::Game::Game()
{
  this->_map = std::unique_ptr<Map>(new Map(10, 10));
  this->_state = NONE;
  this->_snake.push_back(std::make_unique<snake::SnakePart>(4, 4, snake::PartType::HEAD, snake::Direction::WEST));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(5, 4, snake::PartType::BODY, snake::Direction::WEST));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(6, 4, snake::PartType::BODY, snake::Direction::NORTH));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(6, 5, snake::PartType::TAIL, snake::Direction::NORTH));
  this->_snake.front()->printOnMap(this->_snake, this->_map);
  this->_food = std::unique_ptr<snake::Food>(new snake::Food(this->_map));
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
