#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <map>
# include "Map.hh"

namespace sf
{
  enum    Direction
    {
      NORTH,
      EAST,
      SOUTH,
      WEST
    };

  class   Player
  {
    double  x;
    double  y;
    int     xCell;
    int     yCell;
    Direction direction;
    std::map<Direction, std::pair<double, double>>  pos;

  public:
    Player();
    ~Player();

    Direction getDirection() const;
    void    setDirection(Direction);

    void    printOnMap(std::unique_ptr<arcade::Map> &) const;
    void    eraseFromMap(std::unique_ptr<arcade::Map> &) const;

    int     move(std::unique_ptr<arcade::Map> &);
  };
}

#endif
