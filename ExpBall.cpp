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
  sprite.setTexture(exp1);
  sprite.setScale(sf::Vector2f(2, 2));
  sprite.setOrigin(960, 960);
  this->coordinates[0] = xpos + rand() % 800 - 400;
  this->coordinates[1] = ypos + rand() % 800 - 400;
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
}

bool ExpBall::updateExp() {
  float expX = sprite.getPosition().x;
  float expY = sprite.getPosition().y;
  float playerX = P1.sprite.getPosition().x;
  float playerY = P1.sprite.getPosition().y;
  if (abs(expX - playerX) <= 20 && abs(expY - playerY) <= 20) {
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
  } else {
    sprite.setTexture(exp4);
  }
  timer++;
  window.draw(this->sprite);
  return 1;
}
void ExpBall::collected() {
  std::cout << "collected()" << std::endl;
  P1.currentExp = P1.currentExp + expPoints;
  P1.levelPlayer();
}

ExpBall::~ExpBall() { delete[] this->coordinates; }