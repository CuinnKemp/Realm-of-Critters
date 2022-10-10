#ifndef PLAYERARROWSPAWNER_H
#define PLAYERARROWSPAWNER_H

#include "PlayerArrow.h"

class PlayerArrowSpawner {
 public:
  double* coordinates;
  int playerArrowCounter;
  int fireCounter;
  PlayerArrow* playerArrows;
  Enemies* a1;
  sf::Texture texturearrow;

  PlayerArrowSpawner(Enemies* a1);

  void attack();

  void drawArrows();

  ~PlayerArrowSpawner();
};
#endif  // PLAYERARROWSPAWNER_H