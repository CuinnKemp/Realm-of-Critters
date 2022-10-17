#ifndef PLAYERARROWSPAWNER_H
#define PLAYERARROWSPAWNER_H

#include "PlayerArrow.h"

//This is an aggregator of the PlayerArrow class
class PlayerArrowSpawner {
 public:

  // coordinates of each arrow
  double* coordinates;
  
  // Total amount of arrows
  int playerArrowCounter;

  // Counter when to spawn a new arrow
  int fireCounter;

  // Array of PlayerArrows
  PlayerArrow* playerArrows;

  // Array of Enemies
  Enemies* a1;

  // texture for arrows
  sf::Texture texturearrow;

  // Initilisation for arrows
  PlayerArrowSpawner(Enemies* a1);

  // Attack and Spawner
  void attack();

  // Drawing Sprite for current map
  void drawArrows();

  void resetSpawner();

  // standard Destructor
  ~PlayerArrowSpawner();
};
#endif  // PLAYERARROWSPAWNER_H