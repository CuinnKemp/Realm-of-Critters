#ifndef EXPBALL_H
#define EXPBALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ExpContainer.h"
extern sf::RenderWindow window;

class ExpBall : public ExpContainer {
 public:
  int expPoints;
  int timer;
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;
  sf::Texture exp1, exp2, exp3, exp4;
  ExpBall();
  ~ExpBall() {}
  bool updateExp();
  void collected();
};
#endif  // EXPBALL_H