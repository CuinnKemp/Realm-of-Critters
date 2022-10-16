#ifndef SPINNINGBLADE_H
#define SPINNINGBLADE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "PowerUp.h"

// Power up of a spinning blade around the player
class SpinningBlade : public PowerUp {
 public:
  // Rotation count
  int count;

  //Default constructor and destructor, 
  SpinningBlade();  // Parameter for amount of spinning blades to spawn
  ~SpinningBlade();

  // Collision Detection into enemy array
  void hitEnemy(Enemies* enemies);

  // movement of spinning blade
  void movement(int num, SpinningBlade* sBlades);

    //void updatePosition();

  //updates ability by calling movement and other functions
  bool updateAbility();
};
#endif  // SPINNINGBLADE_H