#ifndef SLIME_H
#define SLIME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"

class Slime : public Enemy {
 public:
  sf::RectangleShape sprite;
  sf::Texture walkDown1, walkDown2, walkDown3, walkDown4, walkUp1, walkUp2,
      walkUp3, walkUp4, walkLeft1, walkLeft2, walkLeft3, walkLeft4, walkRight1,
      walkRight2, walkRight3, walkRight4;

  int count;
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int animationCount;

  Slime();

  ~Slime();

  void attack();

  void movement();

  bool updateEnemy();
};
#endif  // BEAST_H