#include "Player.h"

#include "ResourceManager.h"

extern double xpos, ypos;

extern ResourceManager resourceManager;
Player::Player(double Pxpos, double Pypos, double width, double height,
               sf::RenderWindow* window) {
  xpos = Pxpos;
  ypos = Pypos;
  this->health = 100;
  this->movSpeed = 5;
  this->window = window;
  this->sprite.setPosition(sf::Vector2f(0, 0));
  this->sprite.setSize(sf::Vector2f(40, 40));
  sprite.setTexture(&resourceManager.idleDown);
  camera.setCenter(0, 0);
  camera.setSize(1920 / 2, 1080 / 2);
  window->setView(camera);
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->currentExp = 0;
  this->expCap = 100;
  this->level = 1;
}

// This should be called whenever an enemy dies to check whether player has
// levelled up
void Player::levelPlayer() {
  if (currentExp >= expCap) {
    this->level++;
    /*
      INSERT LEVEL UP SEQUENCE HERE
    */

    this->expCap =
        this->expCap * 2;  // increase experience required after every level
    this->currentExp = 0;  // resets exp
  }
}

void Player::resetPlayer() {
  xpos = 0;
  ypos = 0;
  oldXpos = 0;
  oldYpos = 0;
  currentExp = 0;
  expCap = 100;
  camera.setCenter(0, 0);
  this->sprite.setSize(sf::Vector2f(40, 40));
  this->animationCount = 0;
  this->health = 100;
}

void Player::moveRight() {
  oldXpos = xpos;
  xpos = xpos + movSpeed;
}
void Player::moveLeft() {
  oldXpos = xpos;
  xpos = xpos - movSpeed;
}

void Player::moveUp() {
  oldYpos = ypos;
  ypos = ypos - movSpeed;
}

void Player::moveDown() {
  oldYpos = ypos;
  ypos = ypos + movSpeed;
}

void Player::getPosition() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    direction = 1;
    isMoving = true;
    this->moveLeft();
    animationCount++;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    direction = 2;
    isMoving = true;
    this->moveRight();
    animationCount++;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    direction = 3;
    isMoving = true;
    this->moveUp();
    animationCount++;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    direction = 4;
    isMoving = true;
    this->moveDown();
    animationCount++;
  }

  if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
    isMoving = false;
  }

  if (isMoving == false) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.idleLeft);
        break;
      case 2:
        sprite.setTexture(&resourceManager.idleRight);
        break;
      case 3:
        sprite.setTexture(&resourceManager.idleUp);
        break;
      case 4:
        sprite.setTexture(&resourceManager.idleDown);
        break;
      default:
        sprite.setTexture(&resourceManager.idleDown);
    }
  } else if (remainder(animationCount / 8, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.pwalkLeft4);
        break;
      case 2:
        sprite.setTexture(&resourceManager.pwalkRight4);
        break;
      case 3:
        sprite.setTexture(&resourceManager.pwalkUp4);
        break;
      case 4:
        sprite.setTexture(&resourceManager.pwalkDown4);
        break;
      default:
        sprite.setTexture(&resourceManager.pwalkDown4);
    }
  } else if (remainder(animationCount / 6, 3) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.pwalkLeft3);
        break;
      case 2:
        sprite.setTexture(&resourceManager.pwalkRight3);
        break;
      case 3:
        sprite.setTexture(&resourceManager.pwalkUp3);
        break;
      case 4:
        sprite.setTexture(&resourceManager.pwalkDown3);
        break;
      default:
        sprite.setTexture(&resourceManager.pwalkDown3);
    }
  } else if (remainder(animationCount / 4, 2) == 0) {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.pwalkLeft2);
        break;
      case 2:
        sprite.setTexture(&resourceManager.pwalkRight2);
        break;
      case 3:
        sprite.setTexture(&resourceManager.pwalkUp2);
        break;
      case 4:
        sprite.setTexture(&resourceManager.pwalkDown2);
        break;
      default:
        sprite.setTexture(&resourceManager.pwalkDown2);
    }
  } else {
    switch (direction) {
      case 1:
        sprite.setTexture(&resourceManager.pwalkLeft1);
        break;
      case 2:
        sprite.setTexture(&resourceManager.pwalkRight1);
        break;
      case 3:
        sprite.setTexture(&resourceManager.pwalkUp1);
        break;
      case 4:
        sprite.setTexture(&resourceManager.pwalkDown1);
        break;
      default:
        sprite.setTexture(&resourceManager.pwalkDown1);
    }
  }
}

bool Player::isAlive() {
  if (health >= 0) {
    return 1;
  }
  camera.setCenter(0, 0);
  window->setView(camera);
  return 0;
}

void Player::DrawPlayer(sf::RenderWindow* window) {
  this->getPosition();
  sprite.setPosition(sf::Vector2f(xpos - 20, ypos - 20));
  window->draw(sprite);
  camera.setCenter(sprite.getPosition());
  window->setView(camera);
}