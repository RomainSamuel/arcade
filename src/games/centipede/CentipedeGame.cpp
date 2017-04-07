#include "CentipedeGame.hh"
#include <iostream>

arcade::CentipedeGame::CentipedeGame()
{
  this->_map = std::unique_ptr<Map>(new Map(20, 20, 2));
  this->_gui = std::unique_ptr<GUI>(new GUI());
  this->_state = arcade::GameState::LOADING;
  this->_eaten = 0;
  this->_score = 0;
  this->_cd = 10;
  this->_cdRemaining = 10;

  // EVENTS
  arcade::Event event;
  event.type = arcade::EventType::ET_KEYBOARD;
  event.action = arcade::ActionType::AT_PRESSED;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_RIGHT;
  this->_eventsBound[0] = event;
  event.kb_key = arcade::KeyboardKey::KB_ARROW_LEFT;
  this->_eventsBound[1] = event;

  // GUI
  std::unique_ptr<Component> comp = std::unique_ptr<Component>(new Component(0,
                                                                             0,
                                                                             1,
                                                                             0.1,
                                                                             false,
                                                                             0,
                                                                             arcade::Color::Black,
                                                                             "Score : 0"));
  this->_gui->addComponent(std::move(comp));
}

arcade::CentipedeGame::~CentipedeGame()
{
}

arcade::GameState arcade::CentipedeGame::getGameState() const
{
  return (_state);
}

void  arcade::CentipedeGame::notifyEvent(std::vector<arcade::Event> &&events)
{
  for (std::vector<arcade::Event>::iterator it = events.begin(); it != events.end(); it++)
    this->_events.push_back(std::move(*it));
}

void  arcade::CentipedeGame::notifyNetwork(std::vector<arcade::NetworkPacket> &&)
{
}

std::vector<arcade::NetworkPacket>&& arcade::CentipedeGame::getNetworkToSend()
{
  return (std::move(std::vector<arcade::NetworkPacket>()));
}

int arcade::CentipedeGame::getActionToPerform(arcade::Event event) const
{
  for (size_t i = 0; i < 2; i++)
    {
      if (event.type == this->_eventsBound[i].type &&
          event.action == this->_eventsBound[i].action &&
          event.kb_key == this->_eventsBound[i].kb_key)
        return (i);
    }
  return (-1);
}

void  arcade::CentipedeGame::process()
{
  int actionNb = -1;

  if (this->_state != INGAME)
    this->_state = INGAME;
  if (this->_events.size() > 0)
    {
      actionNb = this->getActionToPerform(this->_events.front());
      this->_events.erase(this->_events.begin());
    }
}

std::vector<std::unique_ptr<arcade::ISprite>> &&arcade::CentipedeGame::getSpritesToLoad() const
{
  return (std::move(std::vector<std::unique_ptr<arcade::ISprite>>()));
}

std::vector<std::pair<std::string, arcade::SoundType>> arcade::CentipedeGame::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>>  sounds;

  return (sounds);
}

std::vector<int>&& arcade::CentipedeGame::getSoundsToPlay()
{
  return (std::move(std::vector<int>()));
}

arcade::IMap const &arcade::CentipedeGame::getCurrentMap() const
{
  return (*this->_map);
}

arcade::IGUI &arcade::CentipedeGame::getGUI()
{
  return (*this->_gui);
}

extern "C" arcade::IGame *maker()
{
  return (new arcade::CentipedeGame());
}
