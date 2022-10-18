#ifndef EXPCONTAINER_H
#define EXPCONTAINER_H

//include required libraries
#include <SFML/Graphics.hpp>

// Virtual Class for Exp Ball
class ExpContainer {
 public:

  // Cordinates of ball
  double* coordinates = new double[2];

  // Amount of xp given
  int expPoints;

  // Sprite
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;

  // Virtual function to update the Exp ball
  virtual bool updateExp();
};
#endif  // EXPCONTAINER_H