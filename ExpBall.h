#ifndef EXPBALL_H
#define EXPBALL_H

#include <SFML/Graphics.hpp>
class ExpBall {
 public:
  int expPoints;
  int timer;
  double* coordinates = new double[2];
  sf::Sprite sprite;
  sf::Texture exp1, exp2, exp3, exp4;
  ExpBall();
  ~ExpBall();
  void collected();
  void drawExp();
  bool updateExp();
};
#endif