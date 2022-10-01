#ifndef OBSTACLEGENERATOR_H
#define OBSTACLEGENERATOR_H

#include "Obstacle.h"

class ObstacleGenerator {
 public:
  double* coordinates;
  int obstacleCounter;
  Obstacle** obstacles;

  ObstacleGenerator();

  void spawnNewObstacle();

  void updateObstacles();

  ~ObstacleGenerator();
};
#endif  // OBSTACLEGENERATOR_H