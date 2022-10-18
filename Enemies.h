#ifndef ENEMIES_H
#define ENEMIES_H

// include beast enemy and slime headers
#include "Beast.h"
#include "GoldenSlime.h"
#include "Slime.h"
#include "Enemy.h"

// Enemies is an aggregator of all Enemy subclasses such as Beast and Slime
class Enemies {
 public:
  // Current Position
  double* coordinates;

  // Counter of all Enemies alive
  int enemyCounter;

  // Array of all enemies on screen
  Enemy** enemies;

  // Spawn Functionality, Spawn rate and timer
  int spawnRate;
  int timer;

  // default Constructor & destructor
  Enemies();
  ~Enemies();

  // Spawns new enemy onscreen
  void spawnNewEnemy();

  void goldenSlime();

  // Check how many Enemies are alive
  void checkAlives();

  // Updates the Array of Enemies
  void updateEnemies();

  void deleteEnemies();
};
#endif  // ENEMIES_H