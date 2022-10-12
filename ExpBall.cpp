#include "ExpBall.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "ExpContainer.h"
#include "Player.h"
#include "ResourceManager.h"

// Extern :
extern double xpos, ypos;        // player coordinates
extern sf::RenderWindow window;  // Render Window

extern Player P1;
extern ResourceManager resourceManager;
ExpBall::ExpBall() {
  // Sets Animation Texture
  sprite.setTextureRect(rectSourceSprite);
  sprite.setTexture(resourceManager.exp1);
  sprite.setScale(sf::Vector2f(2, 2));

  // Initialises Timer
  timer = 0;
}

bool ExpBall::updateExp() {
  // Draws Exp Ball
  window.draw(this->sprite);
  float expX = sprite.getPosition().x;
  float expY = sprite.getPosition().y;

  // Finds Player Position
  float playerX = P1.sprite.getPosition().x;
  float playerY = P1.sprite.getPosition().y;

  // Collision detection for Player and Exp ball
  if (abs(expX - playerX) <= 30 && abs(expY - playerY) <= 30) {
    collected();
    return 0;
  }

  // Animation loop using timer
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
  // Adds Exp to the player after collision
  P1.currentExp = P1.currentExp + expPoints;

  // Runs player Levelling sequence
  P1.levelPlayer();
}

ExpBall::~ExpBall() {}