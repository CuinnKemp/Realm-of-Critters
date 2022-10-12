#ifndef SLIME_H
#define SLIME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"

// Similair to Beast.h, A simple Enemy collides with player to do damage
class Slime : public Enemy {
 public:

  // Sprites and Animation cycle
  sf::RectangleShape sprite;
  sf::Texture walkDown1, walkDown2, walkDown3, walkDown4, walkUp1, walkUp2,
      walkUp3, walkUp4, walkLeft1, walkLeft2, walkLeft3, walkLeft4, walkRight1,
      walkRight2, walkRight3, walkRight4;

  // variables for direction, movement and animation
  int count;
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int animationCount;

  // Standard Constructor & Destructor
  Slime();
  ~Slime();

  // Collision Detection
  void attack();

  // Movement for Slime
  void movement();

  // Update function that loops to call other functions as nessecary
  bool updateEnemy();
};
#endif  // BEAST_H