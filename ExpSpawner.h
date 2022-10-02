#ifndef EXPSPAWNER_H
#define EXPSPAWNER_H

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
  ~ExpSpawner();
  void checkExp();
  void updateExps();
  void spawnExp(int expPoints, double xpos, double ypos);
  void spawnExp();
};
#endif  // EXPSPAWNER_H