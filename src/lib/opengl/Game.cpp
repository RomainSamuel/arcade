#include "Game.hh"
#include <string>
#include <iostream>

arcade::Game::Game()
{
  this->_map = std::unique_ptr<Map>(new Map(20, 20));
  this->_state = NONE;
  this->_snake.push_back(std::make_unique<snake::SnakePart>(4, 4, snake::PartType::HEAD, snake::Direction::WEST));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(5, 4, snake::PartType::BODY, snake::Direction::WEST));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(6, 4, snake::PartType::BODY, snake::Direction::NORTH));
  this->_snake.push_back(std::make_unique<snake::SnakePart>(6, 5, snake::PartType::TAIL, snake::Direction::NORTH));
  this->_snake.front()->printOnMap(this->_snake, this->_map);
  this->_food = std::unique_ptr<snake::Food>(new snake::Food(this->_map));
  this->_eaten = 0;
  this->_score = 0;

  arcade::Event event;
  event.type = arcade::EventType::ET_KEYBOARD;
  event.action = arcade::ActionType::AT_PRESSED;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_UP;
  this->_eventsBound[0] = event;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_RIGHT;
  this->_eventsBound[1] = event;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_DOWN;
  this->_eventsBound[2] = event;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_LEFT;
  this->_eventsBound[3] = event;

  // TEST
  arcade::Event e;
  e.type = arcade::EventType::ET_KEYBOARD;
  e.action = arcade::ActionType::AT_PRESSED;
  e.kb_key = arcade::KeyboardKey::KB_ARROW_UP;
  this->_events.push_back(e);
  e.kb_key = arcade::KeyboardKey::KB_ARROW_LEFT;
  this->_events.push_back(e);
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
  for (std::vector<arcade::Event>::iterator it = events.begin(); it != events.end(); it++)
    this->_events.push_back(std::move(*it));
}

void  arcade::Game::notifyNetwork(std::vector<arcade::NetworkPacket> &&)
{
}

std::vector<arcade::NetworkPacket>&& arcade::Game::getNetworkToSend()
{
  return (std::move(std::vector<arcade::NetworkPacket>()));
}

int arcade::Game::getActionToPerform(arcade::Event event) const
{
  for (size_t i = 0; i < 4; i++)
    {
      if (event.type == this->_eventsBound[i].type &&
          event.action == this->_eventsBound[i].action &&
          event.kb_key == this->_eventsBound[i].kb_key)
        return (i);
    }
  return (-1);
}

void  arcade::Game::process()
{
  int actionNb = -1;
  int ret;

  if (this->_state != INGAME)
    this->_state = INGAME;
  if (this->_events.size() > 0)
    {
      actionNb = this->getActionToPerform(this->_events.front());
      this->_events.erase(this->_events.begin());
    }
  if (actionNb >= 0 && actionNb < 4)
    this->_snake.front()->setDirection(static_cast<snake::Direction>(actionNb));
  ret = this->_snake.front()->move(this->_snake, this->_map, this->_food);
  if (ret == -1 || ret == 2)
    this->_state = QUIT;
  else if (ret == 1)
    {
      this->_eaten++;
      this->_score += 100 * this->_eaten;
    }
}

std::vector<std::unique_ptr<arcade::ISprite>> &&arcade::Game::getSpritesToLoad() const
{
  return (std::move(std::vector<std::unique_ptr<arcade::ISprite>>()));
}

std::vector<std::pair<std::string, arcade::SoundType>> arcade::Game::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>>  sounds;

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

arcade::IGUI &arcade::Game::getGUI()
{
  return (*this->_gui);
}

extern "C" arcade::IGame *maker()
{
  return (new arcade::Game());
}
