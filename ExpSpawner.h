#ifndef EXPSPAWNER_H
#define EXPSPAWNER_H

#include "ExpBall.h"

// Aggregate of all Current Exp Balls
class ExpSpawner {
 public:

  // Total live Exp Balls
  int expBallsCounter;

  // Array of ExpBalls 
  ExpBall** expBalls;

  // Spawn rate and timer for expiration
  int spawnRate;
  int timer;

  // amount of exp given
  int baseExpPoints;


  // Default Constructor & Destructor
  ExpSpawner();
  ~ExpSpawner();

  // Deletes Exp Balls from Array
  void deleteExpBalls();

  // Spawns new Exp Ball
  void spawnNewExp();

  // Spawns new Exp Ball with parameters for specific coordinates
  void spawnNewExp(int expPoint, double xpos, double ypos);

  // Check which balls have been collided with 
  void checkAlives();

  // main function which calls other when necessary
  void updateExps();
};
#endif  // EXPSPAWNER_H