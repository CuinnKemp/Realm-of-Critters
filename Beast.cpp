#include "Beast.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "Enemy.h"
#include "ExpSpawner.h"
#include "ResourceManager.h"

extern double xpos, ypos;        // Player Position
extern sf::RenderWindow window;  // Render Window
extern ExpSpawner E1;            // Exp Spawner
extern ResourceManager resourceManager;

Beast::Beast() {
  // initialises the arrow counter
  this->arrowCounter = 0;

  // Sets the Spawn Point of the beast based upon the current position of the
  // player
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

  // sets the spawn position to be in 'lastCoorinates'
  this->lastCoordinates[0] = coordinates[0];
  this->lastCoordinates[1] = coordinates[1];

  // Sets the Sprite position
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.setSize(sf::Vector2f(16, 16));

  // Initialises the movement, direction, sprite size & texture of the enemy

  this->sprite.setTextureRect(rectSourceSprite);
  this->sprite.setSize(sf::Vector2f(32, 32));
  this->sprite.setTexture(&resourceManager.walkDown1);
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->sprite.setOrigin(0, 0);

  // Initialises an array of Projectiles, and health of the enemy
  this->Arrows = new Arrow[0];
  this->fireCounter = 0;
  this->health = 50;
}

// destructor deletes the coordinates of the current enemy
Beast::~Beast() { delete[] this->coordinates; }

// Called when Firecounter reaches a threshold value,
// used to shoot a projectile at the player
void Beast::attack() {
  // Sets a temporary arrray to hold the current spawned Projectiles
  Arrow* holdArrows = this->Arrows;

  // Replaces Arrows with a new array that is incrementally bigger
  Arrows = new Arrow[arrowCounter + 1];

  // Fills 'Arrows' with the projectiles in 'holdArrows'
  for (int i = 0; i < arrowCounter; i++) {
    Arrows[i] = holdArrows[i];
  }

  // Deletes Temporary Array
  delete[] holdArrows;

  // Creates a new projectile, Adds it to array, increments arrow counter
  Arrow A(coordinates[0], this->coordinates[1]);
  Arrows[arrowCounter] = A;
  arrowCounter++;
  return;
}

// Updates the position and sprite of the projectiles
void Beast::drawArrows() {
  // for every arrow currently spawned
  for (int i = 0; i < arrowCounter; i++) {
    // checks the position of each arrow
    if (!(this->Arrows[i].UpdatePosition())) {
      // if collided with the player, removed
      for (int j = i + 1; j < arrowCounter; j++) {
        Arrows[j - 1] = Arrows[j];
      }

      // decrements total arrows
      arrowCounter--;
    }

    // draws arrow sprites for new positions
    window.draw(this->Arrows[i].ArrowShape);
  }
  return;
}

// movement for beast
void Beast::movement() {
  // Moves the beast if further away than a 200 pixel radius from the current
  // position of the player
  if (sqrt(pow(xpos - coordinates[0], 2) + pow(ypos - coordinates[1], 2)) >=
      200) {
    this->coordinates[0] =
        this->coordinates[0] + 2.5 * ((xpos - this->coordinates[0]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));
    this->coordinates[1] =
        this->coordinates[1] + 2.5 * ((ypos - this->coordinates[1]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));

    // sets new position of sprite
    sprite.setPosition(
        sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    isMoving = true;
  } else {
    isMoving = false;
  }

  // Checks in which direction the beast moved last by using its previous
  // position
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

  // resets previous position to current position as direction has been found
  lastCoordinates[0] = coordinates[0];
  lastCoordinates[1] = coordinates[1];
}

// main updating function for beast, controls all processes
bool Beast::updateEnemy() {
  // checks whether or not beast is alive
  if (this->health == 0) {
    // random exp spawn on death
    int shouldSpawnExp = rand() % 2;
    if (shouldSpawnExp == 0) {
      E1.spawnNewExp(10, coordinates[0], coordinates[1]);
    }
    return 0;
  }

  // calls to update projectiles and movement
  this->drawArrows();
  this->movement();

  // updates firecounter, checks whether threshold value has been reached
  this->fireCounter = this->fireCounter + 2;
  if (this->fireCounter == 100) {
    this->attack();
    this->fireCounter = 0;
  }

  //  updates animation cycle based on 'isMoving' and current direction found in
  //  'movement()'
  if (isMoving == false) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.walkLeft1);
        break;
      case 2:
        sprite.setTexture(&resourceManager.walkRight1);
        break;
      case 3:
        sprite.setTexture(&resourceManager.walkUp1);
        break;
      case 4:
        sprite.setTexture(&resourceManager.walkDown1);
        break;
      default:
        sprite.setTexture(&resourceManager.walkDown1);
    }
  } else if (remainder(animationCount / 8, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.walkLeft4);
        break;
      case 2:
        sprite.setTexture(&resourceManager.walkRight4);
        break;
      case 3:
        sprite.setTexture(&resourceManager.walkUp4);
        break;
      case 4:
        sprite.setTexture(&resourceManager.walkDown4);
        break;
      default:
        sprite.setTexture(&resourceManager.walkDown4);
    }
  } else if (remainder(animationCount / 6, 3) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.walkLeft3);
        break;
      case 2:
        sprite.setTexture(&resourceManager.walkRight3);
        break;
      case 3:
        sprite.setTexture(&resourceManager.walkUp3);
        break;
      case 4:
        sprite.setTexture(&resourceManager.walkDown3);
        break;
      default:
        sprite.setTexture(&resourceManager.walkDown3);
    }
  } else if (remainder(animationCount / 4, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.walkLeft2);
        break;
      case 2:
        sprite.setTexture(&resourceManager.walkRight2);
        break;
      case 3:
        sprite.setTexture(&resourceManager.walkUp2);
        break;
      case 4:
        sprite.setTexture(&resourceManager.walkDown2);
        break;
      default:
        sprite.setTexture(&resourceManager.walkDown2);
    }
  } else {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.walkLeft1);
        break;
      case 2:
        sprite.setTexture(&resourceManager.walkRight1);
        break;
      case 3:
        sprite.setTexture(&resourceManager.walkUp1);
        break;
      case 4:
        sprite.setTexture(&resourceManager.walkDown1);
        break;
      default:
        sprite.setTexture(&resourceManager.walkDown1);
    }
  }
  animationCount++;

  // Updates sprite
  window.draw(this->sprite);

  return 1;
}