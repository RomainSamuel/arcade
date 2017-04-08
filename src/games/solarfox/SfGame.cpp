#include "SfGame.hh"
#include <iostream>

arcade::SfGame::SfGame()
{
  this->_map = std::unique_ptr<Map>(new Map(20, 20, 5));
  this->_gui = std::unique_ptr<GUI>(new GUI());
  this->_state = arcade::GameState::LOADING;
  this->_score = 0;
  this->_cd = 5;
  this->_cdRemaining = 5;
  this->_player = std::unique_ptr<sf::Player>(new sf::Player());
  this->_player->printOnMap(this->_map);
  this->_remainingScrap = 10;
  this->_enemies.push_back(std::make_unique<sf::Enemy>(3, 10.5, 0.5, 1, 19, 1, 1, 0.1, sf::mvType::HORIZONTAL, 2, 2, 18, 9));
  this->_enemies.push_back(std::make_unique<sf::Enemy>(3, 9.5, 19.5, 1, 19, -1, -1, 0.1, sf::mvType::HORIZONTAL, 2, 2, 18, 9));

  for (size_t i = 0; i < this->_enemies.size(); i++)
    this->_enemies[i]->printOnMap(this->_map);

  // EVENTS
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

  // GUI
  std::unique_ptr<Component> comp = std::unique_ptr<Component>(new Component(0,
                                                                             0,
                                                                             1,
                                                                             1,
                                                                             false,
                                                                             0,
                                                                             arcade::Color::White,
                                                                             "Score : 0"));
  this->_gui->addComponent(std::move(comp));
}

arcade::SfGame::~SfGame()
{
}

arcade::GameState arcade::SfGame::getGameState() const
{
  return (_state);
}

void  arcade::SfGame::notifyEvent(std::vector<arcade::Event> &&events)
{
  for (std::vector<arcade::Event>::iterator it = events.begin(); it != events.end(); it++)
    this->_events.push_back(std::move(*it));
}

void  arcade::SfGame::notifyNetwork(std::vector<arcade::NetworkPacket> &&)
{
}

std::vector<arcade::NetworkPacket>&& arcade::SfGame::getNetworkToSend()
{
  return (std::move(std::vector<arcade::NetworkPacket>()));
}

int arcade::SfGame::getActionToPerform(arcade::Event event) const
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

void  arcade::SfGame::checkShots(std::unique_ptr<arcade::Map> &map)
{
  size_t  i = 0;

  while (i < this->_shots.size())
    {
      if (this->_shots[i]->isAlive() == false)
        {
          this->_shots[i]->eraseFromMap(this->_map);
          this->_shots.erase(this->_shots.begin() + i);
        }
      else if (this->_player->hasShot() &&
               this->_shots[i]->Collide(this->_player->getShot()))
        {
          this->_player->getShot().eraseFromMap(map);
          this->_player->deleteShot();
          this->_shots[i]->eraseFromMap(this->_map);
          this->_shots.erase(this->_shots.begin() + i);
        }
      else
        i++;
    }
}

void  arcade::SfGame::process()
{
  int actionNb = -1;

  if (this->_state == QUIT)
    return;
  if (this->_state != INGAME)
    this->_state = INGAME;
  this->_cdRemaining--;
  if (this->_cdRemaining == 0)
    {
      this->_cdRemaining = this->_cd;
      if (this->_events.size() > 0)
        {
          actionNb = this->getActionToPerform(this->_events.front());
          this->_events.erase(this->_events.begin());
        }
      if (actionNb >= 0 && actionNb < 4)
        this->_player->setDirection(static_cast<sf::Direction>(actionNb));
    }

  //HANDLE PLAYER SHOTS
  if (this->_player->hasShot() == true)
    {
      if (this->_player->checkShotDuration(this->_map))
        if (this->_player->getShot().move(this->_map))
          {
            this->_player->deleteShot();
            this->_score += 100;
            std::cout << "Score = " << this->_score << std::endl;
            this->_remainingScrap--;
            this->_gui->getComponent(0).setText("Score : " + std::to_string(this->_score));
            if (this->_remainingScrap == 0)
              {
                this->_state = QUIT;
                return;
              }
          }
    }

  //HANDLE ENEMIES
  for (size_t i = 0; i < this->_enemies.size(); i++)
    this->_enemies[i]->move(this->_map, this->_shots);

  //HANDLE ENEMY SHOTS
  this->checkShots(this->_map);
  for (size_t i = 0; i < this->_shots.size(); i++)
    this->_shots[i]->move(this->_map);

  //HANDLE PLAYER
  if (this->_player->move(this->_map) == -1)
    {
      this->_state = QUIT;
      return;
    }
}

std::vector<std::unique_ptr<arcade::ISprite>> &&arcade::SfGame::getSpritesToLoad() const
{
  return (std::move(std::vector<std::unique_ptr<arcade::ISprite>>()));
}

std::vector<std::pair<std::string, arcade::SoundType>> arcade::SfGame::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>>  sounds;

  return (sounds);
}

std::vector<int>&& arcade::SfGame::getSoundsToPlay()
{
  return (std::move(std::vector<int>()));
}

arcade::IMap const &arcade::SfGame::getCurrentMap() const
{
  return (*this->_map);
}

arcade::IGUI &arcade::SfGame::getGUI()
{
  return (*this->_gui);
}

extern "C" arcade::IGame *maker()
{
  return (new arcade::SfGame());
}
