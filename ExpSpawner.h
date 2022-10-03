#ifndef EXPSPAWNER_H
#define EXPSPAWNER_H

#include "ExpBall.h"
class ExpSpawner {
 public:
  int expBallsCounter;
  ExpBall** expBalls;
  int spawnRate;
  int timer;
  int baseExpPoints;

  ExpSpawner();

  ~ExpSpawner();

  void spawnNewExp();

  void checkAlives();

  void updateExps();
};
#endif  // EXPSPAWNER_H