#ifndef PLAYERARROWSPAWNER_H
#define PLAYERARROWSPAWNER_H

#include "PlayerArrow.h"

class PlayerArrowSpawner {
 public:
  double* coordinates;
  int playerArrowCounter;
  PlayerArrow** playerArrows;

  PlayerArrowSpawner();

  void spawnNewArrow();

  void updateArrows();

  ~PlayerArrowSpawner();
};
#endif  // PLAYERARROWSPAWNER_H