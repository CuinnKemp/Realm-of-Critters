#ifndef PLAYERARROW_H
#define PLAYERARROW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "PowerUp.h"

class PlayerArrow : public PowerUp {
 public:

  // constants used to find rotation needed to face closest enemy
  double TWOPI = 6.2831853071795865;
  double RAD2DEG = 57.2957795130823209;

  // position in monster array of closest enemy
  int closestenemy;

  // Arrow coordinates
  double* arrowCoordinates = new double[2];

  // damage done to enemies
  int damage;

  // target coordinates and speed vector
  double* targetCoordinates = new double[2];
  double* speedVector = new double[2];

  // total arrow counter
  int counter;

  // constructor using current enemy array
  PlayerArrow(Enemies* enemies);
  PlayerArrow();

  // Out of bounds check
  bool outOfBounds();

  // Updating position of arrow
  bool UpdatePosition(Enemies* enemies);

  // Drawing the sprite on current position of arrow
  void DrawArrows();

  // Checking if enemy is colliding with arrow, dealing damage
  bool EnemycollisionDetection(Enemies* enemies);

  // Determining the movement of arrow
  bool movement(Enemies* enemies, PlayerArrow* arrow1);

  // Main function which calls others as necessary
  bool updateAbility(Enemies* enemies, PlayerArrow* arrow1);
};
#endif  // PlayerArrow_H