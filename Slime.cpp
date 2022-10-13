#include "Slime.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"
#include "ExpSpawner.h"
#include "Player.h"
#include "ResourceManager.h"

// External:
extern double xpos, ypos;        // Player Position
extern sf::RenderWindow window;  // Render Window
extern ExpSpawner E1;            // Exp Spawner
extern Player P1;                // Player Class
extern ResourceManager resourceManager;

Slime::Slime() {
  // Spawn Coordinates, anywhere between 400 pixels of the current position of
  // the player
  this->coordinates[0] = xpos + rand() % 800 - 400;
  this->coordinates[1] = ypos + rand() % 800 - 400;
  if (coordinates[0] < -1600) {
    coordinates[0] = coordinates[0] + 400;
  } else if (coordinates[0] > 1600) {
    coordinates[0] = coordinates[0] - 400;
  }
  if (coordinates[1] < -1600) {
    coordinates[1] = coordinates[1] + 400;
  } else if (coordinates[1] > 1600) {
    coordinates[1] = coordinates[1] - 400;
  }

  // Sets spawn as its last coordinates
  this->lastCoordinates[0] = coordinates[0];
  this->lastCoordinates[1] = coordinates[1];

  // Sets Sprite Position and size
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.setSize(sf::Vector2f(16, 16));

  // Loads Animation Files

  // Initialises sprite texture, size and shape
  this->sprite.setTextureRect(rectSourceSprite);
  this->sprite.setSize(sf::Vector2f(32, 32));
  this->sprite.setTexture(&resourceManager.slimeWalkDown1);

  // initialises movement direction, current status and animation count
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->sprite.setOrigin(0, 0);

  // initialises total and health
  this->count = 0;
  this->health = 25;
}

// Destructor upon death to delete coordinates
Slime::~Slime() { delete[] this->coordinates; }

void Slime::attack() {
  // detects sprite collision with the player, damages the player upon collision
  if (sqrt(pow(xpos - coordinates[0], 2) + pow(ypos - coordinates[1], 2)) <=
      50) {
    P1.health = P1.health - 10;
  }
}

void Slime::movement() {
  // Movement for the slime, moves toward the player using parameterisation
  // stops within 2 pixels of the players current position, still enough for
  // collision
  if (sqrt(pow(xpos - coordinates[0], 2) + pow(ypos - coordinates[1], 2)) >=
      50) {
    this->coordinates[0] =
        this->coordinates[0] + 1.5 * ((xpos - this->coordinates[0]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));
    this->coordinates[1] =
        this->coordinates[1] + 1.5 * ((ypos - this->coordinates[1]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));

    // Sets position of sprite to last known coordinates
    sprite.setPosition(
        sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    isMoving = true;
  } else {
    isMoving = false;
  }

  // Sets direction to set which animation to play, using current known
  // coordinates and last known coordinates
  if (abs(lastCoordinates[0] - coordinates[0]) >
      abs(lastCoordinates[1] - coordinates[1])) {
    if (lastCoordinates[0] < coordinates[0]) {
      direction = 2;
    } else {
      direction = 1;
    }
  } else {
    if (lastCoordinates[1] < coordinates[1]) {
      direction = 4;
    } else if (lastCoordinates[1] > coordinates[1]) {
      direction = 3;
    }
  }

  // resets last known and current coordinates
  lastCoordinates[0] = coordinates[0];
  lastCoordinates[1] = coordinates[1];
}

bool Slime::updateEnemy() {
  // checks whether or not slime is alive
  if (this->health < 0) {
    // random exp spawn on death
    int shouldSpawnExp = rand() % 2;
    if (shouldSpawnExp == 0) {
      E1.spawnNewExp(10, coordinates[0], coordinates[1]);
    }
    return 0;
  }

  // calls movement function
  this->movement();
  this->count++;

  // checks for collision on count threshold
  if (this->count == 60) {
    this->attack();
    this->count = 0;
  }

  // Animation cycle based upon direction from movement function
  if (isMoving == false) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.slimeWalkLeft1);
        break;
      case 2:
        sprite.setTexture(&resourceManager.slimeWalkRight1);
        break;
      case 3:
        sprite.setTexture(&resourceManager.slimeWalkUp1);
        break;
      case 4:
        sprite.setTexture(&resourceManager.slimeWalkDown1);
        break;
      default:
        sprite.setTexture(&resourceManager.slimeWalkDown1);
    }
  } else if (remainder(animationCount / 8, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.slimeWalkLeft4);
        break;
      case 2:
        sprite.setTexture(&resourceManager.slimeWalkRight4);
        break;
      case 3:
        sprite.setTexture(&resourceManager.slimeWalkUp4);
        break;
      case 4:
        sprite.setTexture(&resourceManager.slimeWalkDown4);
        break;
      default:
        sprite.setTexture(&resourceManager.slimeWalkDown4);
    }
  } else if (remainder(animationCount / 6, 3) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.slimeWalkLeft3);
        break;
      case 2:
        sprite.setTexture(&resourceManager.slimeWalkRight3);
        break;
      case 3:
        sprite.setTexture(&resourceManager.slimeWalkUp3);
        break;
      case 4:
        sprite.setTexture(&resourceManager.slimeWalkDown3);
        break;
      default:
        sprite.setTexture(&resourceManager.slimeWalkDown3);
    }
  } else if (remainder(animationCount / 4, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.slimeWalkLeft2);
        break;
      case 2:
        sprite.setTexture(&resourceManager.slimeWalkRight2);
        break;
      case 3:
        sprite.setTexture(&resourceManager.slimeWalkUp2);
        break;
      case 4:
        sprite.setTexture(&resourceManager.slimeWalkDown2);
        break;
      default:
        sprite.setTexture(&resourceManager.slimeWalkDown2);
    }
  } else {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.slimeWalkLeft1);
        break;
      case 2:
        sprite.setTexture(&resourceManager.slimeWalkRight1);
        break;
      case 3:
        sprite.setTexture(&resourceManager.slimeWalkUp1);
        break;
      case 4:
        sprite.setTexture(&resourceManager.slimeWalkDown1);
        break;
      default:
        sprite.setTexture(&resourceManager.slimeWalkDown1);
    }
  }
  animationCount++;

  // Draws Sprite on Screen
  window.draw(this->sprite);

  return 1;
}