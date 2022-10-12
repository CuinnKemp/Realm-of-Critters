#ifndef SPINNINGBLADE_H
#define SPINNINGBLADE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "PowerUp.h"

class SpinningBlade : public PowerUp {
 public:
  int count;

  SpinningBlade(int num);

  ~SpinningBlade();

  void hitEnemy(Enemies* enemies);

  void movement();

  void updatePosition();

  bool updateAbility();
};
#endif  // SPINNINGBLADE_H