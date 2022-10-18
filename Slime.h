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
  // Sprite
  sf::RectangleShape sprite;

  // variables for direction, movement and animation
  int count;
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int animationCount;

  // Standard Constructor & Destructor
  Slime();
  void deconstructor();

  // Collision Detection
  void attack();

  // Movement for Slime
  void movement();

  // Update function that loops to call other functions as nessecary
  bool updateEnemy();
};
#endif  // BEAST_H