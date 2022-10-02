#ifndef EXPSPAWNER_H
#define EXPSPAWNER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ExpBall.h"
#include "ExpContainer.h"

extern sf::RenderWindow window;

class ExpSpawner {
 public:
  int spawnRate;
  int baseExpPoints;
  int expBallsCounter;
  ExpContainer** expBalls;
  int timer;
  ExpSpawner();
  void checkExp();
  void updateExps();
  void spawnExp();
  void spawnExp(int expPoints, double xpos, double ypos);
  ~ExpSpawner();
};
#endif  // EXPSPAWNER_H