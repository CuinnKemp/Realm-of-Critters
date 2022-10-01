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
  obstacles[obstacleCounter] = new Obstacle;
  // std::cout << obstacleCounter << std::endl;
  if (obstacleCounter <= 59) {
    obstacles[obstacleCounter]->coordinates[0] = obstacleCounter * 64;
    obstacles[obstacleCounter]->coordinates[1] = 0;
  } else if (obstacleCounter <= 118) {
    obstacles[obstacleCounter]->coordinates[0] = 0;
    obstacles[obstacleCounter]->coordinates[1] = (obstacleCounter - 59) * 64;
  } else if (obstacleCounter <= 178) {
    obstacles[obstacleCounter]->coordinates[0] = (obstacleCounter - 119) * 64;
    obstacles[obstacleCounter]->coordinates[1] = 3776;
  } else if (obstacleCounter <= 237) {
    obstacles[obstacleCounter]->coordinates[0] = 3776;
    obstacles[obstacleCounter]->coordinates[1] = (obstacleCounter - 179) * 64;
  }
  if (obstacles[obstacleCounter]->coordinates[0] <= 1888 &&
      obstacles[obstacleCounter]->coordinates[1] <= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(
        obstacles[obstacleCounter]->grass);
  } else if (obstacles[obstacleCounter]->coordinates[0] >= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] <= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(
        obstacles[obstacleCounter]->desert);
  } else if (obstacles[obstacleCounter]->coordinates[0] <= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] >= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(
        obstacles[obstacleCounter]->snow);
  } else if (obstacles[obstacleCounter]->coordinates[0] >= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] >= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(
        obstacles[obstacleCounter]->dirt);
  }

  obstacles[obstacleCounter]->sprite.setPosition(
      obstacles[obstacleCounter]->coordinates[0],
      obstacles[obstacleCounter]->coordinates[1]);
  obstacleCounter++;
}

void ObstacleGenerator::updateObstacles() {
  for (int i = 0; i < obstacleCounter; i++) {
    obstacles[i]->updateObstacle();
  }
}
ObstacleGenerator::~ObstacleGenerator() {
  for (int i = 0; i < obstacleCounter; i++) {
    delete obstacles[i];
  }
  delete[] obstacles;
}
