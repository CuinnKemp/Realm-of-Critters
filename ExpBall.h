#ifndef EXPBALL_H
#define EXPBALL_H

#include <SFML/Graphics.hpp>
class ExpBall {
 public:
  int expPoints;
  int timer;
  sf::Sprite sprite;
  sf::IntRect rectSourceSprite;
  ExpBall();
  ~ExpBall();
  void collected();
  void drawExp();
  bool updateExp();
};
#endif