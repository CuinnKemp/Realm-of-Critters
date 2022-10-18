#ifndef SPINNINGBLADESPAWNER_H
#define SPINNINGBLADESPAWNER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "SpinningBlade.h"

// Spinning blade spawner
class SpinningBladeSpawner {
 public:
  // how many blades
    int sBladeCount;

  // array of spinning blades
    SpinningBlade* sBlades;
  
  // pointer to enemies array
    Enemies* enemies;

  //onstructor and destructor, 
  SpinningBladeSpawner(Enemies* enemies);  // Parameter for amount of spinning blades to spawn
  ~SpinningBladeSpawner();

// resets spawner for new game
  void resetSpawner();

//updates the spawner and all blades
  bool updateAbility();
};
#endif  // SPINNINGBLADESPAWNER_H