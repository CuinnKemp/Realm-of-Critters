// include ObstacleGenerator header
#include "ObstacleGenerator.h"

//include required libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

// include Obstacle and resource manager class definitions
#include "Obstacle.h"
#include "ResourceManager.h"

//external variables
extern ResourceManager resourceManager;


//default constructor
ObstacleGenerator::ObstacleGenerator() {
  // Initialising counter and size of Obstacle Array
  obstacleCounter = 0;
  obstacles = new Obstacle*[0];
}

// spawn ne obstacles 
void ObstacleGenerator::spawnNewObstacle() {
  //Creates temporary Array of Obstacles
  Obstacle** holdObstacleGenerator = this->obstacles;

  // Creates new Array incramentally bigger than prior array
  obstacles = new Obstacle*[obstacleCounter + 1];

  // Fills new array with temp array
  for (int i = 0; i < obstacleCounter; i++) {
    obstacles[i] = holdObstacleGenerator[i];
  }

  // Deletes Temporary Array
  delete[] holdObstacleGenerator;
  
  // Creates new Obstacle
  obstacles[obstacleCounter] = new Obstacle;

  //std::cout << obstacleCounter << std::endl;

  //Changes Coordinates of each obstacles based upon position in map,
  // Wraps around a set size around the edge of the map
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
    obstacles[obstacleCounter]->sprite.setTexture(resourceManager.grass);
  } else if (obstacles[obstacleCounter]->coordinates[0] >= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] <= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(resourceManager.desert);
  } else if (obstacles[obstacleCounter]->coordinates[0] <= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] >= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(resourceManager.snow);
  } else if (obstacles[obstacleCounter]->coordinates[0] >= 1888 &&
             obstacles[obstacleCounter]->coordinates[1] >= 1888) {
    obstacles[obstacleCounter]->sprite.setTexture(resourceManager.dirt);
  }

  // Sets the Sprite position to the individual cooridnates of each Obstacle in the array, 
  obstacles[obstacleCounter]->sprite.setPosition(
      obstacles[obstacleCounter]->coordinates[0],
      obstacles[obstacleCounter]->coordinates[1]);

  // incraments amount of obstacles
  obstacleCounter++;
}

// update the obstacles
void ObstacleGenerator::updateObstacles() {
  // updates each obstacle to draw sprites on map
  for (int i = 0; i < obstacleCounter; i++) {
    obstacles[i]->updateObstacle();
  }
}

// default deconstructor 
ObstacleGenerator::~ObstacleGenerator() {
  //destructor for obstacle array
  for (int i = 0; i < obstacleCounter; i++) {
    delete obstacles[i];
  }
  delete[] obstacles;
}
