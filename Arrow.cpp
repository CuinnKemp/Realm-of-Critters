// include the Arrow header file
#include "Arrow.h"

//include required inclusions
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

//include player class definition
#include "Player.h"

// External variables:
extern Player P1;                // Player
extern double xpos, ypos;        // Player Position
extern sf::RenderWindow window;  // Render Window

//define default constructor
Arrow::Arrow() {}

// Arrow Constructor with Beast Coordinates as parameters
Arrow::Arrow(double xspawn, double yspawn) {
  // initialise damage, Starting Coordinates
  this->damage = 1;
  this->arrowCoordinates[0] = xspawn;
  this->arrowCoordinates[1] = yspawn;

  // Target coordinates are external player position
  this->targetCoordinates[0] = xpos;
  this->targetCoordinates[1] = ypos;

  // Calculates Speed vector
  double divisor = sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
                        pow(targetCoordinates[1] - arrowCoordinates[1], 2));
  this->speedVector[0] =
      10 * (this->targetCoordinates[0] - this->arrowCoordinates[0]) / divisor;
  this->speedVector[1] =
      10 * (this->targetCoordinates[1] - this->arrowCoordinates[1]) / divisor;

  // Sets Sprite and initial position for Arrow
  this->ArrowShape.setFillColor(sf::Color::Red);
  this->ArrowShape.setPosition(
      sf::Vector2f(this->arrowCoordinates[0], this->arrowCoordinates[1]));
  this->ArrowShape.setSize(sf::Vector2f(10, 10));
}

// define the arrow collision detection function
bool Arrow::collisionDetection() {
  // Detects the sprite collision of the projectile and the player
  if (P1.sprite.getGlobalBounds().intersects(ArrowShape.getGlobalBounds())) {
    P1.health = P1.health - this->damage;
    return 1;
  }
  return 0;
}

// define the arrow out of bounds function
bool Arrow::outOfBounds() {
  // detects whether or not the projectile is out of Bounds
  if (sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
           pow(targetCoordinates[1] - arrowCoordinates[1], 2)) == 0) {
    return 1;
  }
  return 0;
}

//define the arrow update position function
bool Arrow::UpdatePosition() {
  // detects either collision or out of bounds to remove the projectile
  if (this->collisionDetection() || this->outOfBounds()) {
    return 0;
  }

  // updates the arrow with position and speed vector, updates sprite with new
  // position
  this->arrowCoordinates[0] = this->arrowCoordinates[0] + this->speedVector[0];
  this->arrowCoordinates[1] = this->arrowCoordinates[1] + this->speedVector[1];
  this->ArrowShape.setPosition(
      sf::Vector2f(this->arrowCoordinates[0], this->arrowCoordinates[1]));
  return 1;
}
