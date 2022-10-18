#ifndef OBSTACLEGENERATOR_H
#define OBSTACLEGENERATOR_H

// include obstacle class definition
#include "Obstacle.h"

//Aggregator class for Obstacles
class ObstacleGenerator {
 public:
 
  // Coordinates for obstacle
  double* coordinates;

  // Counter and array for Active Obstacles
  int obstacleCounter;
  Obstacle** obstacles;

  // Default Constructor & Destructor
  ObstacleGenerator();
  ~ObstacleGenerator();

  // Spawns new Obstacles
  void spawnNewObstacle();

  // Draws all Obstacles in Active Array
  void updateObstacles();

};
#endif  // OBSTACLEGENERATOR_H