#ifndef BARRIER_H
#define BARRIER_H

//include required libraries
#include <SFML/Graphics.hpp>

//This class is for unmoving objects that have collision bounds
class Obstacle {
 public:
  //coordinates for object
  double* coordinates = new double[2];

  // Sprites
  sf::Sprite sprite;

  //Default Constructor and Destructor
  Obstacle();  // 1 - grass, 2 - desert, 3 - snow, 4 - dirt
  ~Obstacle();

  // Draw Obstacles
  bool updateObstacle();
};
#endif