#ifndef SPINNINGBLADE_H
#define SPINNINGBLADE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"

// Power up of a spinning blade around the player
class SpinningBlade {
 public:
  // Rotation count
  int count;

  // Coordinates for either player or powerup- pickup
  double* coordinates = new double[2];

  // Sprite shape
  sf::RectangleShape sprite;

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