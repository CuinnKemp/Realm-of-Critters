#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Player.h"


// External:
extern Player P1;                // Player
extern double xpos, ypos;        // Player Position
extern sf::RenderWindow window;  // Render Window

// Projectile fired by Beast
class Arrow {
 public:
 
  // Coordinates for Projectile and Target as well as velocity vector
  double* arrowCoordinates = new double[2];
  double* targetCoordinates = new double[2];
  double* speedVector = new double[2];

  //sprite
  sf::RectangleShape ArrowShape;

  int damage;
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