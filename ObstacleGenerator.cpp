#include "ObstacleGenerator.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Obstacle.h"

ObstacleGenerator::ObstacleGenerator() {
  obstacleCounter = 0;
  obstacles = new Obstacle*[0];
}

void ObstacleGenerator::spawnNewObstacle() {
  Obstacle** holdObstacleGenerator = this->obstacles;
  obstacles = new Obstacle*[obstacleCounter + 1];
  for (int i = 0; i < obstacleCounter; i++) {
    obstacles[i] = holdObstacleGenerator[i];
  }
  delete[] holdObstacleGenerator;
  obstacleCounter++;
}

ObstacleGenerator::~ObstacleGenerator() {
  for (int i = 0; i < obstacleCounter; i++) {
    delete obstacles[i];
  }
  delete[] obstacles;
}
