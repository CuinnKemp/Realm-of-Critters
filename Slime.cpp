#include "Slime.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"
#include "Player.h"

extern double xpos, ypos;
extern sf::RenderWindow window;
extern Player P1;

Slime::Slime() {
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
  walkDown1.loadFromFile("slimeAnimation/walkDown1.png");
  walkDown2.loadFromFile("slimeAnimation/walkDown2.png");
  walkDown3.loadFromFile("slimeAnimation/walkDown3.png");
  walkDown4.loadFromFile("slimeAnimation/walkDown4.png");
  walkUp1.loadFromFile("slimeAnimation/walkUp1.png");
  walkUp2.loadFromFile("slimeAnimation/walkUp2.png");
  walkUp3.loadFromFile("slimeAnimation/walkUp3.png");
  walkUp4.loadFromFile("slimeAnimation/walkUp4.png");
  walkLeft1.loadFromFile("slimeAnimation/walkLeft1.png");
  walkLeft2.loadFromFile("slimeAnimation/walkLeft2.png");
  walkLeft3.loadFromFile("slimeAnimation/walkLeft3.png");
  walkLeft4.loadFromFile("slimeAnimation/walkLeft4.png");
  walkRight1.loadFromFile("slimeAnimation/walkRight1.png");
  walkRight2.loadFromFile("slimeAnimation/walkRight2.png");
  walkRight3.loadFromFile("slimeAnimation/walkRight3.png");
  walkRight4.loadFromFile("slimeAnimation/walkRight4.png");
  this->sprite.setTextureRect(rectSourceSprite);
  this->sprite.setSize(sf::Vector2f(32, 32));
  this->sprite.setTexture(&walkDown1);
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->sprite.setOrigin(0, 0);

  this->count = 0;
  this->health = 50;
}

Slime::~Slime() { delete[] this->coordinates; }

void Slime::attack() {
  if (sqrt(pow(xpos - coordinates[0], 2) + pow(ypos - coordinates[1], 2)) <=
      50) {
        P1.health = P1.health - 10;
      }
}

void Slime::movement() {
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

bool Slime::updateEnemy() {
  if (this->health == 0) {
    return 0;
  }
  this->movement();

  this->count++;
  if (this->count == 60) {
    this->attack();
    this->count = 0;
  }

  if (isMoving == false) {
    switch (direction) {
      case 1:
        sprite.setTexture(&walkLeft1);
        break;
      case 2:
        sprite.setTexture(&walkRight1);
        break;
      case 3:
        sprite.setTexture(&walkUp1);
        break;
      case 4:
        sprite.setTexture(&walkDown1);
        break;
      default:
        sprite.setTexture(&walkDown1);
    }
  } else if (remainder(animationCount / 8, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&walkLeft4);
        break;
      case 2:
        sprite.setTexture(&walkRight4);
        break;
      case 3:
        sprite.setTexture(&walkUp4);
        break;
      case 4:
        sprite.setTexture(&walkDown4);
        break;
      default:
        sprite.setTexture(&walkDown4);
    }
  } else if (remainder(animationCount / 6, 3) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&walkLeft3);
        break;
      case 2:
        sprite.setTexture(&walkRight3);
        break;
      case 3:
        sprite.setTexture(&walkUp3);
        break;
      case 4:
        sprite.setTexture(&walkDown3);
        break;
      default:
        sprite.setTexture(&walkDown3);
    }
  } else if (remainder(animationCount / 4, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&walkLeft2);
        break;
      case 2:
        sprite.setTexture(&walkRight2);
        break;
      case 3:
        sprite.setTexture(&walkUp2);
        break;
      case 4:
        sprite.setTexture(&walkDown2);
        break;
      default:
        sprite.setTexture(&walkDown2);
    }
  } else {
    switch (direction) {
      case 1:
        sprite.setTexture(&walkLeft1);
        break;
      case 2:
        sprite.setTexture(&walkRight1);
        break;
      case 3:
        sprite.setTexture(&walkUp1);
        break;
      case 4:
        sprite.setTexture(&walkDown1);
        break;
      default:
        sprite.setTexture(&walkDown1);
    }
  }
  animationCount++;

  window.draw(this->sprite);

  return 1;
}