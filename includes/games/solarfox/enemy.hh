#ifndef ENEMY_HH_
# define ENEMY_HH_

# include <cstddef>
# include "Map.hh"

namespace   sf
{
  enum      mvType
    {
      VERTICAL,
      HORIZONTAL
    };

  class     Enemy
  {
    size_t  x;
    size_t  y;
    size_t  firstBoundary;
    size_t  secondBoundary;
    int     direction;
    float   moveSpeed;
    mvType  mv;
    size_t  ammos_max;
    size_t  ammos;
    size_t  reload_cd;
    size_t  fire_cd;

  public:
    Enemy(size_t x,
          size_t y,
          float moveSpeed,
          mvType mv,
          size_t ammos_max,
          size_t ammos,
          size_t reload_cd,
          size_t fire_cd);
    ~Enemy();
  };
}

#endif
