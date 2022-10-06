#ifndef ENEMIES_H
#define ENEMIES_H

#include "Beast.h"
#include "Enemy.h"

class Enemies {
 public:
  double* coordinates;
  int enemyCounter;
  Enemy** enemies;
  int spawnRate;
  int timer;

  Enemies();

  ~Enemies();

  void spawnNewEnemy();

  void deleteEnemies();

  void checkAlives();

  void updateEnemies();
};
#endif  // ENEMIES_H