//
// Created by maud on 22/03/17.
//

#include <memory>
#include <iostream>
#include "Menu.hh"

arcade::Menu::Menu()
{
    this->_gui = std::unique_ptr<GUI>(new GUI());
    this->_state = arcade::GameState::LOADING;
    this->_score = 0;
    this->_cd = 10;
    this->_cdRemaining = 10;

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

    std::unique_ptr<Component> comp = std::unique_ptr<Component>(new Component(0,
                                                                             0,
                                                                             1,
                                                                             0.1,
                                                                             false,
                                                                             0,
                                                                             arcade::Color::Black,
                                                                             arcade::Color::White,
                                                                             nullptr));
    this->_gui->addComponent(std::move(comp));                                                
}

arcade::Menu::~Menu()
{
}
arcade::GameState arcade::Menu::getGameState() const
{
  return (_state);
}

void  arcade::Menu::notifyEvent(std::vector<arcade::Event> &&events)
{
  for (std::vector<arcade::Event>::iterator it = events.begin(); it != events.end(); it++)
    this->_events.push_back(std::move(*it));
}

void  arcade::Menu::notifyNetwork(std::vector<arcade::NetworkPacket> &&)
{
}

std::vector<arcade::NetworkPacket>&& arcade::Menu::getNetworkToSend()
{
  return (std::move(std::vector<arcade::NetworkPacket>()));
}

int arcade::Menu::getActionToPerform(arcade::Event event) const
{
    (void)event;
  /*for (size_t i = 0; i < 4; i++)
    {
      if (event.type == this->_eventsBound[i].type &&
          event.action == this->_eventsBound[i].action &&
          event.kb_key == this->_eventsBound[i].kb_key)
        return (i);
    }*/
  return (-1);
}

void  arcade::Menu::process()
{
  /*int actionNb = -1;
  int ret;

  this->_sounds.clear();
  this->_cdRemaining -= (1.5 + static_cast<double>(this->_eaten) * 0.10);
  if (this->_cdRemaining <= 0)
    {
      this->_cdRemaining = this->_cd;
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
          this->_sounds.push_back(arcade::Sound(0));
          this->_eaten++;
          this->_score += 100 * this->_eaten;
          this->_gui->getComponent(0).setText("Score : " + std::to_string(this->_score));
        }
    }*/
}

std::vector<std::unique_ptr<arcade::ISprite>> arcade::Menu::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<arcade::ISprite>> vec;

  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(std::vector<std::pair<std::string, char>>
                                                           ({std::pair<std::string, char>("./resources/menu/arcade.png", ' ')}))));
  return (vec);
}

std::vector<std::pair<std::string, arcade::SoundType>> arcade::Menu::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>>  sounds;

  return (sounds);
}

std::vector<arcade::Sound> arcade::Menu::getSoundsToPlay()
{
  return (std::vector<arcade::Sound>());
}

arcade::IMap const &arcade::Menu::getCurrentMap() const
{
  return (*this->_map);
}

arcade::IGUI &arcade::Menu::getGUI()
{
  return (*this->_gui);
}

arcade::tick_t  arcade::Menu::getTickRate() const
{
  return (30.0);
}
