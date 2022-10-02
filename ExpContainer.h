#ifndef EXPCONTAINER_H
#define EXPCONTAINER_H

#include <SFML/Window.hpp>
class ExpContainer {
 public:
  int expPoints;
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;
  virtual bool updateExp() = 0;
  virtual ~ExpContainer(){};
};
#endif  // EXPCONTAINER_H