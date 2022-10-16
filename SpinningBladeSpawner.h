#ifndef SPINNINGBLADESPAWNER_H
#define SPINNINGBLADESPAWNER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "SpinningBlade.h"

// Power up of a spinning blade around the player
class SpinningBladeSpawner {
 public:
  // Rotation count
  int sBladeCount;

    SpinningBlade* sBlades;
    
    Enemies* enemies;

  //Default constructor and destructor, 
  SpinningBladeSpawner(Enemies* enemies);  // Parameter for amount of spinning blades to spawn
  ~SpinningBladeSpawner();

  bool updateAbility();
};
#endif  // SPINNINGBLADESPAWNER_H