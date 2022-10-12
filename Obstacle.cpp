#include "Obstacle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

extern double xpos, ypos;
extern sf::RenderWindow window;

Obstacle::Obstacle() {
  this->sprite.setScale(sf::Vector2f(2, 2));
  this->sprite.setOrigin(960, 960);
}

bool Obstacle::updateObstacle() {
  window.draw(this->sprite);
  return 1;
}

Obstacle::~Obstacle() {
  delete[] this->coordinates;
  return;
}
