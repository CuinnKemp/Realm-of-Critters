#ifndef PLAYERARROWSPAWNER_H
#define PLAYERARROWSPAWNER_H

#include "PlayerArrow.h"

class PlayerArrowSpawner {
 public:
  double* coordinates;
  int playerArrowCounter;
  int fireCounter;
  PlayerArrow* playerArrows;

  PlayerArrowSpawner();

  void attack();

  void drawArrows();

  ~PlayerArrowSpawner();
};
#endif  // PLAYERARROWSPAWNER_H