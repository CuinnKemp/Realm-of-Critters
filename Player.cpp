#include "Player.h"

// external variable of current player position
extern double xpos, ypos;

// Constructor for Player
Player::Player(double Pxpos, double Pypos, double width, double height,
               sf::RenderWindow* window) {

  // Sets Position Variables for the player
  xpos = Pxpos;
  ypos = Pypos;

  // Initialises Player Stats
  this->health = 100;
  this->movSpeed = 5;

  // Sequence to Intialise Sprites and Animations
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
  camera.setSize(width, height);
  window->setView(camera);

  // Sets Default Direction and movement
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;

  //Initialising Exp and levelling system
  this->currentExp = 0;
  this->expCap = 100;
  this->level = 1;

  //Initialising Health Bar UI, (WILL BE UPDATED FOR UI_OVERHAUL)
  this->healthBarBack.setFillColor(sf::Color::Black);
  this->healthBarBack.setPosition(camera.getCenter().x - width / 2,
                                  camera.getCenter().y - height / 2);

  this->healthBarFront.setFillColor(sf::Color::Red);
  this->healthBarFront.setPosition(camera.getCenter().x - width / 2,
                                   camera.getCenter().y - height / 2);
  this->healthBarBack.setSize(sf::Vector2f(200 * camera.getSize().x / 1000,
                                           20 * camera.getSize().x / 1000));
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

// Resets the Player after Death Screen
void Player::resetPlayer() {

  // Sets deafault Position and camera to 0,0
  xpos = 0;
  ypos = 0;
  oldXpos = 0;
  oldYpos = 0;
  camera.setCenter(0, 0);
  this->sprite.setSize(sf::Vector2f(40, 40));

  //resets variables
  this->animationCount = 0;
  this->health = 100;

  //Resets Health Bar
  this->healthBarBack.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarBack.setSize(sf::Vector2f(200 * camera.getSize().x / 1000,
                                           20 * camera.getSize().x / 1000));
}

//Directional movement by adding current Position and movement speed vector in chosen direction
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

//Returns Player Position depending on Key Pressed, for arrow-keys
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

  // Sets Animation cycle
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

// Checks if Player is Alive
bool Player::isAlive() {
  if (health >= 0) {
    return 1;
  }
  
  // Resets camera if player isnt alive
  camera.setCenter(0, 0);
  window->setView(camera);
  return 0;
}

//Draws the Player, Repeeated in while loop to update consistently with keyboard presses
void Player::DrawPlayer(sf::RenderWindow* window) {
  
  // Gets current POsition
  this->getPosition();

  // Sets the Position of the PLayer Sprite
  sprite.setPosition(sf::Vector2f(xpos - 20, ypos - 20));
  window->draw(sprite);

  // Centres the Camera On the player's new position
  camera.setCenter(sprite.getPosition());
  window->setView(camera);

  // Sets the Health bar to be consistent in the corner of the screen (WILL BE UPDATED IN UI OVERHAUL)
  this->healthBarBack.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setPosition(
      camera.getCenter().x - camera.getSize().x / 2,
      camera.getCenter().y - camera.getSize().y / 2);
  this->healthBarFront.setSize(sf::Vector2f(
      health * 2 * camera.getSize().x / 1000, 20 * camera.getSize().x / 1000));

  window->draw(healthBarBack);
  window->draw(healthBarFront);
}