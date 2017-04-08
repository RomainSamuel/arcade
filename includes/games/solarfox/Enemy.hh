#ifndef ENEMY_HH_
# define ENEMY_HH_

# include <cstddef>
# include "Map.hh"
# include "Shot.hh"

namespace   sf
{
  class     Enemy
  {
    size_t  layer;
    double  x;
    double  y;
    double  firstBoundary;
    double  secondBoundary;
    int     direction;
    int     fireDirection;
    double  moveSpeed;
    mvType  mv;
    size_t  ammos_max;
    size_t  ammos;
    size_t  reload_cd;
    size_t  fire_cd;
    size_t  rcd;
    size_t  fcd;

  public:
    Enemy(size_t layer,
          double x,
          double y,
          double firstBoundary,
          double secondBoundary,
          int    direction,
          int    fireDirection,
          double moveSpeed,
          mvType mv,
          size_t ammos_max,
          size_t ammos,
          size_t reload_cd,
          size_t fire_cd);
    ~Enemy();

    int     getAssociatedSpritePos() const;
    void    printOnMap(std::unique_ptr<arcade::Map> &) const;
    void    eraseFromMap(std::unique_ptr<arcade::Map> &) const;
    int     fire();
    void    move(std::unique_ptr<arcade::Map> &, std::vector<std::unique_ptr<sf::Shot>> &);
  };
}

#endif
