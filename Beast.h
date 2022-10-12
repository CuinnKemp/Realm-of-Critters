#ifndef BEAST_H
#define BEAST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "Enemy.h"

// Standard Enemy, Shoots at the Player
class Beast : public Enemy {
 public:

  // A counter for total Arrows
  int arrowCounter;

  // A threshold value to tell when projectile to fire
  int fireCounter;

  // Enemy Projectile
  Arrow* Arrows;

  // Sprite and Textures for animation, Walk cycle
  sf::RectangleShape sprite;

  // Direction of movement, boolean value for movement, current animation count
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int animationCount;

  //Default constructors & Destructors
  Beast();
  ~Beast();

  // Spawns a projectile to fire at the Player
  void attack();

  // Updates the position and sprites of the arrows
  void drawArrows();

  // moves toward the player
  void movement();

  // Updates the enemy Position
  void updatePosition();

  // Updates enemy attributes, checks status, calls other class functions as necessary
  bool updateEnemy();
};
#endif  // BEAST_H