#include "Player.h"

extern double xpos, ypos;

Player::Player(double Pxpos, double Pypos, double width, double height,
               sf::RenderWindow* window) {
  xpos = Pxpos;
  ypos = Pypos;
  this->health = 500;
  this->movSpeed = 5;
  this->window = window;
  this->sprite.setPosition(sf::Vector2f(0, 0));
  this->sprite.setSize(sf::Vector2f(40, 40));
  idleDown.loadFromFile("playerAnimation/Idle/idleDown.png");
  idleUp.loadFromFile("playerAnimation/Idle/idleUp.png");
  idleLeft.loadFromFile("playerAnimation/Idle/idleLeft.png");
  idleRight.loadFromFile("playerAnimation/Idle/idleRight.png");
  idleRight.loadFromFile("playerAnimation/Idle/idleRight.png");
  walkDown1.loadFromFile("playerAnimation/Walk/walkDown1.png");
  walkDown2.loadFromFile("playerAnimation/Walk/walkDown2.png");
  walkDown3.loadFromFile("playerAnimation/Walk/walkDown3.png");
  walkDown4.loadFromFile("playerAnimation/Walk/walkDown4.png");
  walkUp1.loadFromFile("playerAnimation/Walk/walkUp1.png");
  walkUp2.loadFromFile("playerAnimation/Walk/walkUp2.png");
  walkUp3.loadFromFile("playerAnimation/Walk/walkUp3.png");
  walkUp4.loadFromFile("playerAnimation/Walk/walkUp4.png");
  walkLeft1.loadFromFile("playerAnimation/Walk/walkLeft1.png");
  walkLeft2.loadFromFile("playerAnimation/Walk/walkLeft2.png");
  walkLeft3.loadFromFile("playerAnimation/Walk/walkLeft3.png");
  walkLeft4.loadFromFile("playerAnimation/Walk/walkLeft4.png");
  walkRight1.loadFromFile("playerAnimation/Walk/walkRight1.png");
  walkRight2.loadFromFile("playerAnimation/Walk/walkRight2.png");
  walkRight3.loadFromFile("playerAnimation/Walk/walkRight3.png");
  walkRight4.loadFromFile("playerAnimation/Walk/walkRight4.png");
  sprite.setTexture(&idleDown);
  camera.setCenter(0, 0);
  camera.setSize(width / 3, height / 3);
  window->setView(camera);
  this->direction = 4;
  this->isMoving - false;
  this->animationCount = 0;
  this->currentExp = 0;
  this->expCap = 100;
  this->level = 1;
  this->healthBarBack.setFillColor(sf::Color::Black);
  this->healthBarBack.setPosition(camera.getCenter().x - width / 2,
                                  camera.getCenter().y - height / 2);
  this->healthBarBack.setSize(sf::Vector2f(200, 20));

  this->healthBarFront.setFillColor(sf::Color::Red);
  this->healthBarFront.setPosition(camera.getCenter().x - width / 2,
                                   camera.getCenter().y - height / 2);
  this->healthBarFront.setSize(sf::Vector2f(200, 20));
}

void Player::resetPlayer() {
  xpos = 0;
  ypos = 0;
  camera.setCenter(0, 0);
  this->sprite.setSize(sf::Vector2f(40, 40));
  this->animationCount = 0;
  this->health = 100;

  this->healthBarBack.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setSize(sf::Vector2f(200, 20));
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

void Player::moveRight() { xpos = xpos + movSpeed; }
void Player::moveLeft() { xpos = xpos - movSpeed; }

void Player::moveUp() { ypos = ypos - movSpeed; }

void Player::moveDown() { ypos = ypos + movSpeed; }

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
        sprite.setTexture(&idleLeft);
        break;
      case 2:
        sprite.setTexture(&idleRight);
        break;
      case 3:
        sprite.setTexture(&idleUp);
        break;
      case 4:
        sprite.setTexture(&idleDown);
        break;
      default:
        sprite.setTexture(&idleDown);
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

  this->healthBarBack.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setSize(sf::Vector2f(health * 2, 20));

  window->draw(healthBarBack);
  window->draw(healthBarFront);
}