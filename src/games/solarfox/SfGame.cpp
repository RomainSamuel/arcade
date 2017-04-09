#include "SfGame.hh"
#include <iostream>

arcade::SfGame::SfGame()
{
  this->setLevel(1);
  this->_gui = std::unique_ptr<GUI>(new GUI());
  this->_state = arcade::GameState::LOADING;
  this->_score = 0;
  this->_cd = 9;
  this->_cdRemaining = 0;
  this->_sounds.push_back(arcade::Sound(0, REPEAT));

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
                                                                             arcade::Color::Black,
                                                                             arcade::Color::White,
                                                                             "Score : 0"));
  this->_gui->addComponent(std::move(comp));
}

arcade::SfGame::~SfGame()
{
}

void  arcade::SfGame::setLevel(size_t lvl)
{
  this->_sounds.clear();
  free(this->_player.release());
  this->_enemies.clear();
  this->_shots.clear();
  this->_events.clear();
  this->_cdRemaining = 9;
  this->_cd = 0;
  this->_player = std::unique_ptr<sf::Player>(new sf::Player());
  if (lvl == 0)
    {
      this->_map = std::unique_ptr<Map>(new Map(20, 20, 5, 0));
      this->_remainingScrap = 44;
      this->_enemies.push_back(std::make_unique<sf::Enemy>(3, 10.5, 0.5, 1, 19, 1, 1, 0.05, sf::mvType::HORIZONTAL, 2, 2, 38, 19));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(4, 8.5, 19.5, 1, 19, -1, -1, 0.05, sf::mvType::HORIZONTAL, 2, 2, 38, 19));
    }
  else if (lvl == 1)
    {
      this->_map = std::unique_ptr<Map>(new Map(20, 20, 7, 1));
      this->_remainingScrap = 48;
      this->_enemies.push_back(std::make_unique<sf::Enemy>(3, 10.5, 0.5, 1, 19, 1, 1, 0.1, sf::mvType::HORIZONTAL, 8, 3, 78, 9));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(4, 9.5, 19.5, 1, 19, -1, -1, 0.1, sf::mvType::HORIZONTAL, 8, 3, 78, 9));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(5, 0.5, 10.5, 1, 19, 1, 1, 0.05, sf::mvType::VERTICAL, 3, 3, 38, 19));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(6, 19.5, 9.5, 1, 19, -1, -1, 0.05, sf::mvType::VERTICAL, 3, 3, 38, 19));
    }
  else
    {
      this->_map = std::unique_ptr<Map>(new Map(20, 20, 7, 2));
      this->_remainingScrap = 112;
      this->_enemies.push_back(std::make_unique<sf::Enemy>(3, 0.5, 10.5, 1, 19, 1, 1, 0.05, sf::mvType::VERTICAL, 5, 0, 38, 19));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(4, 19.5, 9.5, 1, 19, -1, -1, 0.05, sf::mvType::VERTICAL, 5, 0, 38, 19));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(5, 0.5, 15.5, 1, 19, 1, 1, 0.05, sf::mvType::VERTICAL, 5, 0, 38, 19));
      this->_enemies.push_back(std::make_unique<sf::Enemy>(6, 19.5, 14.5, 1, 19, -1, -1, 0.05, sf::mvType::VERTICAL, 5, 0, 38, 19));
    }
  this->_player->printOnMap(this->_map);
  for (size_t i = 0; i < this->_enemies.size(); i++)
    this->_enemies[i]->printOnMap(this->_map);
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
#include <chrono>
void  arcade::SfGame::process()
{
  // std::chrono::time_point<std::chrono::system_clock> start, end;
  // start = std::chrono::system_clock::now();
  int actionNb = -1;

  this->_sounds.clear();
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
      else if (actionNb == 4)
        if (this->_player->fire())
          this->_sounds.push_back(arcade::Sound(3));
    }

  //HANDLE PLAYER SHOTS
  if (this->_player->hasShot() == true)
    {
      if (this->_player->checkShotDuration(this->_map))
        if (this->_player->getShot().move(this->_map))
          {
            this->_sounds.push_back(arcade::Sound(4));
            this->_player->deleteShot();
            this->_score += 100;
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
    {
      if (this->_enemies[i]->isInRange(this->_player))
        if (this->_enemies[i]->fire(this->_shots))
          this->_sounds.push_back(arcade::Sound(1));
      this->_enemies[i]->move(this->_map);
    }

  //HANDLE ENEMY SHOTS
  this->checkShots(this->_map);
  for (size_t i = 0; i < this->_shots.size(); i++)
    this->_shots[i]->move(this->_map);

  //HANDLE PLAYER
  if (this->_player->move(this->_map) == -1)
    {
      this->_sounds.push_back(arcade::Sound(2));
      this->_state = QUIT;
      return;
    }
  // end = std::chrono::system_clock::now();

  // std::chrono::duration<double> elapsed_seconds = end-start;
  // std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  // std::cout << "finished computation at " << std::ctime(&end_time)
  //           << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

std::vector<std::unique_ptr<arcade::ISprite>> arcade::SfGame::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<arcade::ISprite>> vec;
  std::string str;

  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(std::vector<std::pair<std::string, char>>
                                                           ({std::pair<std::string, char>("./resources/games/sprites/solarfox/scrap.png", '@')}))));
  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(std::vector<std::pair<std::string, char>>
                                                           ({std::pair<std::string, char>("./resources/games/sprites/solarfox/laser_vertical.png", '-'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/laser_horizontal.png", '|')}))));
  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(std::vector<std::pair<std::string, char>>
                                                           ({std::pair<std::string, char>("./resources/games/sprites/solarfox/Red-Tail_north.png", '^'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/Red-Tail_east.png", '>'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/Red-Tail_south.png", 'v'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/Red-Tail_west.png", '<')}))));
  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(std::vector<std::pair<std::string, char>>
                                                           ({std::pair<std::string, char>("./resources/games/sprites/solarfox/drone_north.png", '^'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/drone_east.png", '>'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/drone_south.png", 'v'),
                                                               std::pair<std::string, char>("./resources/games/sprites/solarfox/drone_west.png", '<')}))));
  std::vector<std::pair<std::string, char>> pairs;
  for (size_t i = 0; i < 400; i++)
    {
      str = std::string("./resources/games/sprites/solarfox/Space/") + std::to_string(i) + std::string(".png");
      std::cout << str << std::endl;
      pairs.push_back(std::pair<std::string, char>(str, ' '));
    }
  vec.push_back(std::unique_ptr<arcade::Sprite>(new Sprite(pairs)));
  return (vec);
}

std::vector<std::pair<std::string, arcade::SoundType>> arcade::SfGame::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>>  sounds;

  sounds.push_back(std::pair<std::string, SoundType>("./resources/games/sounds/solarfox/DeepSpace_Battle.ogg", SoundType::MUSIC));
  sounds.push_back(std::pair<std::string, SoundType>("./resources/games/sounds/solarfox/Enemy_fire.ogg", SoundType::SOUND));
  sounds.push_back(std::pair<std::string, SoundType>("./resources/games/sounds/solarfox/Player_death.ogg", SoundType::SOUND));
  sounds.push_back(std::pair<std::string, SoundType>("./resources/games/sounds/solarfox/Player_fire.ogg", SoundType::SOUND));
  sounds.push_back(std::pair<std::string, SoundType>("./resources/games/sounds/solarfox/Scrap_destroy.ogg", SoundType::SOUND));
  return (sounds);
}

std::vector<arcade::Sound>  arcade::SfGame::getSoundsToPlay()
{
  return (std::vector<arcade::Sound>());
}

arcade::IMap const &arcade::SfGame::getCurrentMap() const
{
  return (*this->_map);
}

arcade::IGUI &arcade::SfGame::getGUI()
{
  return (*this->_gui);
}

arcade::tick_t  arcade::SfGame::getTickRate() const
{
  return (30.0);
}

extern "C" arcade::IGame *maker()
{
  return (new arcade::SfGame());
}
