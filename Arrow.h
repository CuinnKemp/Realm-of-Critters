#ifndef ARROW_H
#define ARROW_H

// include sfml headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// include player class definition
#include "Player.h"

// Projectile fired by Beast
class Arrow {
 public:
 
  // Coordinates for Projectile and Target as well as velocity vector
  double* arrowCoordinates = new double[2];
  double* targetCoordinates = new double[2];
  double* speedVector = new double[2];

  // arrows sprite
  sf::RectangleShape ArrowShape;

  // variable to control damage of arrow
  int damage;

  // variable that acts as a clock (+ 1 every loop loop is 1/fps seconds)
  int counter;

  // default constructor
  Arrow();
  
  // constructor with designated spawn point
  Arrow(double xspawn, double yspawn);

  // Detects collision with target
  bool collisionDetection();

  // Detects if Arrow is out of bounds
  bool outOfBounds();

  // Update Position of arrow and calls other funcitons
  bool UpdatePosition();

  // Updates Sprites
  void DrawArrows();
};
#endif  // ARROW_H