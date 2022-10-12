#ifndef BEAST_H
#define BEAST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "Enemy.h"

class Beast : public Enemy {
 public:
  int arrowCounter;
  int fireCounter;
  Arrow* Arrows;
  sf::RectangleShape sprite;

  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int animationCount;

  Beast();

  ~Beast();

  void attack();

  void drawArrows();

  void movement();

  void updatePosition();

  bool updateEnemy();
};
#endif  // BEAST_H