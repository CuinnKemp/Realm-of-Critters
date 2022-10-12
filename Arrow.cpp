#include "Arrow.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Player.h"

extern Player P1;
extern double xpos, ypos;
extern sf::RenderWindow window;

Arrow::Arrow() {}

Arrow::Arrow(double xspawn, double yspawn) {
  this->damage = 3;
  this->arrowCoordinates[0] = xspawn;
  this->arrowCoordinates[1] = yspawn;

  this->targetCoordinates[0] = xpos;
  this->targetCoordinates[1] = ypos;

  double divisor = sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
                        pow(targetCoordinates[1] - arrowCoordinates[1], 2));
  this->speedVector[0] =
      10 * (this->targetCoordinates[0] - this->arrowCoordinates[0]) / divisor;
  this->speedVector[1] =
      10 * (this->targetCoordinates[1] - this->arrowCoordinates[1]) / divisor;

  this->ArrowShape.setFillColor(sf::Color::Red);
  this->ArrowShape.setPosition(
      sf::Vector2f(this->arrowCoordinates[0], this->arrowCoordinates[1]));
  this->ArrowShape.setSize(sf::Vector2f(10, 10));
}

bool Arrow::collisionDetection() {
  if (P1.sprite.getGlobalBounds().intersects(ArrowShape.getGlobalBounds())) {
    P1.health = P1.health - this->damage;
    return 1;
  }
  return 0;
}

bool Arrow::outOfBounds() {
  if (sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
           pow(targetCoordinates[1] - arrowCoordinates[1], 2)) == 0) {
    return 1;
  }
  return 0;
}

bool Arrow::UpdatePosition() {
  if (this->collisionDetection() || this->outOfBounds()) {
    return 0;
  }

  this->arrowCoordinates[0] = this->arrowCoordinates[0] + this->speedVector[0];
  this->arrowCoordinates[1] = this->arrowCoordinates[1] + this->speedVector[1];
  this->ArrowShape.setPosition(
      sf::Vector2f(this->arrowCoordinates[0], this->arrowCoordinates[1]));
  return 1;
}
