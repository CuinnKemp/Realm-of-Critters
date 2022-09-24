#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

class PowerUp {
 public:
  double* coordinates = new double[2];
  sf::RectangleShape sprite;
  virtual bool updateAbility();
};
#endif  // POWERUP_H