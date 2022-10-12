#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>


// Virtual Class for All Powerups
class PowerUp {
 public:

  // Coordinates for either player or powerup- pickup
  double* coordinates = new double[2];

  // Sprite shape
  sf::RectangleShape sprite;

  // Update Ability is main function to be looped in the game.cpp files
  virtual bool updateAbility();
};
#endif  // POWERUP_H