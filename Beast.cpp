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

extern double xpos, ypos;
extern sf::RenderWindow window;
extern ExpSpawner E1;
extern ResourceManager resourceManager;

Beast::Beast() {
  this->arrowCounter = 0;
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

  this->lastCoordinates[0] = coordinates[0];
  this->lastCoordinates[1] = coordinates[1];

  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.setSize(sf::Vector2f(16, 16));
  this->sprite.setTextureRect(rectSourceSprite);
  this->sprite.setSize(sf::Vector2f(32, 32));
  this->sprite.setTexture(&resourceManager.walkDown1);
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->sprite.setOrigin(0, 0);

  this->Arrows = new Arrow[0];

  this->fireCounter = 0;
  this->health = 50;
}

Beast::~Beast() { delete[] this->coordinates; }

void Beast::attack() {
  Arrow* holdArrows = this->Arrows;
  Arrows = new Arrow[arrowCounter + 1];
  for (int i = 0; i < arrowCounter; i++) {
    Arrows[i] = holdArrows[i];
  }
  delete[] holdArrows;

  Arrow A(coordinates[0], this->coordinates[1]);

  Arrows[arrowCounter] = A;
  arrowCounter++;
  return;
}

void Beast::drawArrows() {
  for (int i = 0; i < arrowCounter; i++) {
    if (!(this->Arrows[i].UpdatePosition())) {
      for (int j = i + 1; j < arrowCounter; j++) {
        Arrows[j - 1] = Arrows[j];
      }
      arrowCounter--;
    }
    window.draw(this->Arrows[i].ArrowShape);
  }
  return;
}

void Beast::movement() {
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
    sprite.setPosition(
        sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    isMoving = true;
  } else {
    isMoving = false;
  }
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

  lastCoordinates[0] = coordinates[0];
  lastCoordinates[1] = coordinates[1];
}

bool Beast::updateEnemy() {
  if (this->health == 0) {
    int shouldSpawnExp = rand() % 2;
    if (shouldSpawnExp == 0) {
      E1.spawnNewExp(10, coordinates[0], coordinates[1]);
    }
    return 0;
  }

  this->drawArrows();
  this->movement();

  this->fireCounter = this->fireCounter + 2;
  if (this->fireCounter == 100) {
    this->attack();
    this->fireCounter = 0;
  }

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

  window.draw(this->sprite);

  return 1;
}