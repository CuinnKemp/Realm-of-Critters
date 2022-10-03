#include "ExpBall.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "ExpContainer.h"
#include "Player.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

extern Player P1;

ExpBall::ExpBall() {
  exp1.loadFromFile("expAnimation/exp1.png");
  exp2.loadFromFile("expAnimation/exp2.png");
  exp3.loadFromFile("expAnimation/exp3.png");
  exp4.loadFromFile("expAnimation/exp4.png");
  exp5.loadFromFile("expAnimation/exp5.png");
  exp6.loadFromFile("expAnimation/exp6.png");
  exp7.loadFromFile("expAnimation/exp7.png");
  exp8.loadFromFile("expAnimation/exp8.png");
  sprite.setTexture(exp1);
  sprite.setScale(sf::Vector2f(2, 2));
  this->coordinates[0] = rand() % 3700 - 1850;
  this->coordinates[1] = rand() % 3700 - 1850;
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
}

bool ExpBall::updateExp() {
  float expX = sprite.getPosition().x;
  float expY = sprite.getPosition().y;
  float playerX = P1.sprite.getPosition().x;
  float playerY = P1.sprite.getPosition().y;
  if (abs(expX - playerX) <= 30 && abs(expY - playerY) <= 30) {
    collected();
    return 0;
  }

  if (timer == 100) {
    timer = 0;
  }
  if (remainder(timer / 8, 2) == 0) {
    sprite.setTexture(exp1);
  } else if (remainder(timer / 6, 3) == 0) {
    sprite.setTexture(exp2);
  } else if (remainder(timer / 4, 2) == 0) {
    sprite.setTexture(exp3);
  } else if (remainder(timer / 6, 3) == 0) {
    sprite.setTexture(exp4);
  } else if (remainder(timer / 4, 2) == 0) {
    sprite.setTexture(exp5);
  } else if (remainder(timer / 6, 3) == 0) {
    sprite.setTexture(exp6);
  } else if (remainder(timer / 4, 2) == 0) {
    sprite.setTexture(exp7);
  } else {
    sprite.setTexture(exp8);
  }
  timer++;
  window.draw(this->sprite);
  return 1;
}
void ExpBall::collected() {
  P1.currentExp = P1.currentExp + expPoints;
  P1.levelPlayer();
}

ExpBall::~ExpBall() { delete[] this->coordinates; }