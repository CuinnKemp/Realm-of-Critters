#ifndef EXPCONTAINER_H
#define EXPCONTAINER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class ExpContainer {
 public:
  double* coordinates = new double[2];
  int expPoints;
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;
  virtual bool updateExp();
};
#endif  // EXPCONTAINER_H