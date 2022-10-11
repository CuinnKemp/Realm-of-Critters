#include "ExpBall.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "ExpContainer.h"
#include "Player.h"
#include "ResourceManager.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

extern Player P1;
extern ResourceManager resourceManager;
ExpBall::ExpBall() {
  sprite.setTextureRect(rectSourceSprite);
  sprite.setTexture(resourceManager.exp1);
  sprite.setScale(sf::Vector2f(2, 2));
  timer = 0;
}

bool ExpBall::updateExp() {
  window.draw(this->sprite);
  float expX = sprite.getPosition().x;
  float expY = sprite.getPosition().y;
  float playerX = P1.sprite.getPosition().x;
  float playerY = P1.sprite.getPosition().y;
  if (abs(expX - playerX) <= 30 && abs(expY - playerY) <= 30) {
    collected();
    return 0;
  }

  if (timer >= 90) {
    timer = 0;
  }
  if (timer == 0) {
    this->sprite.setTexture(resourceManager.exp1);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 2);
  } else if (timer == 10) {
    this->sprite.setTexture(resourceManager.exp2);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 2);
  } else if (timer == 20) {
    this->sprite.setTexture(resourceManager.exp3);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 2);
  } else if (timer == 30) {
    this->sprite.setTexture(resourceManager.exp4);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 2);
  } else if (timer == 40) {
    this->sprite.setTexture(resourceManager.exp5);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 2);
  } else if (timer == 50) {
    this->sprite.setTexture(resourceManager.exp6);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 2);
  } else if (timer == 60) {
    this->sprite.setTexture(resourceManager.exp7);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 2);
  } else if (timer == 80) {
    this->sprite.setTexture(resourceManager.exp8);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 2);
  }
  timer++;
  return 1;
}
void ExpBall::collected() {
  P1.currentExp = P1.currentExp + expPoints;
  P1.levelPlayer();
}

ExpBall::~ExpBall() {}