// include Player header
#include "Player.h"

//include required libraries
#include <SFML/Audio.hpp>

// include resourceManager class definition
#include "ResourceManager.h"

// external variable of current player position and resource manager
extern double xpos, ypos;
extern ResourceManager resourceManager;

// Constructor for Player
Player::Player(double Pxpos, double Pypos, double width, double height,
               sf::RenderWindow* window) {
  // Sets Position Variables for the player
  xpos = Pxpos;
  ypos = Pypos;

  // Initialises Player Stats
  this->health = 1;
  this->movSpeed = 5;

  // Sequence to Intialise Sprites and Animations
  this->window = window;
  this->sprite.setPosition(sf::Vector2f(0, 0));
  this->sprite.setSize(sf::Vector2f(40, 40));
  sprite.setTexture(&resourceManager.idleDown);
  camera.setCenter(0, 0);
  camera.setSize(1920 / 2, 1080 / 2);
  window->setView(camera);

  // Sets Default Direction and movement
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;

  // Initialising Exp and levelling system
  this->currentExp = 0;
  this->expCap = 50;
  this->level = 1;
  this->pArrowLvl = 1;
  this-> sBladeLvl = 1;
}

// This should be called whenever an enemy dies to check whether player has
// levelled up
void Player::levelPlayer() {
  // if current exp is equal too or greater than the exp cap
  if (currentExp >= expCap) {
    // create rectangle shapes sBlade and pArrow
    sf::RectangleShape sBlade, pArrow;

    // create text
    sf::Text upgradeText;
    
    //apply the spinning blade texture and arrow texture
    sBlade.setTexture(&resourceManager.shuriken);
    pArrow.setTexture(&resourceManager.arrowTex);

    // set the size of the spinning blade and arrow
    sBlade.setSize(sf::Vector2f(100,120));
    pArrow.setSize(sf::Vector2f(80,120));

    // set txt to say Select Upgrade and font and character size
    upgradeText.setString(sf::String("Select Upgrade"));
    upgradeText.setFont(resourceManager.defaultFont);
    upgradeText.setCharacterSize(75);

    // set the position and colour of the text
    upgradeText.setPosition(sf::Vector2f(this->camera.getCenter().x - (583/2.0), this->camera.getCenter().y - 100));
    upgradeText.setFillColor(sf::Color::Black);

    //set the postion of the spinning blade and arrow
    sBlade.setPosition(sf::Vector2f(this->camera.getCenter().x - 200, this->camera.getCenter().y + 50));
    pArrow.setPosition(sf::Vector2f(this->camera.getCenter().x + 100, this->camera.getCenter().y + 50));

    // while waiting is true
    bool waiting = true;
    while (waiting == true){
      //draw and display the buttons and text
      this->window->draw(sBlade);
      this->window->draw(pArrow);
      this->window->draw(upgradeText);
      window->display();

      // if the player clicks on spinning blade increase its level
      if (sBlade.getGlobalBounds().contains(sf::Vector2f(
          this->window->mapPixelToCoords(sf::Mouse::getPosition(*(this->window))))) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          this->sBladeLvl++;
          // exit loop
          waiting = false;
      }
      // if the player clicks on the arrow increase its level
      else if (pArrow.getGlobalBounds().contains(sf::Vector2f(
          this->window->mapPixelToCoords(sf::Mouse::getPosition(*(this->window))))) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          this->pArrowLvl++;
          // exit loop
          waiting = false;
      }
    }
    // increase level
    this->level++;
    
    // set new exp cap
    this->expCap =
        this->expCap * 1.10;  // increase experience required after every level
    // reset exp
    this->currentExp = 0;  // resets exp
  }
}


// Resets the Player after Death Screen
void Player::resetPlayer() {
  // reset all variables to original variables
  xpos = 0;
  ypos = 0;
  oldXpos = 0;
  oldYpos = 0;
  camera.setCenter(0, 0);
  clock.restart();
  this->sprite.setSize(sf::Vector2f(40, 40));
  //reset levels
  this->currentExp = 0;
  this->expCap = 50;
  this->level = 1;
  this->pArrowLvl = 1;
  this->sBladeLvl = 1;

  // resets variables
  this->animationCount = 0;
  this->health = 100;
}

// Directional movement by adding current Position and movement speed vector in
// chosen direction
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

// Returns Player Position depending on Key Pressed, for arrow-keys
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

// Checks if Player is Alive
bool Player::isAlive() {
  if (health > 0) {
    return 1;
  }

  // Resets camera if player isnt alive
  camera.setCenter(0, 0);
  window->setView(camera);
  return 0;
}

// Draws the Player, Repeeated in while loop to update consistently with
// keyboard presses
void Player::DrawPlayer(sf::RenderWindow* window) {
  // Gets current POsition
  this->getPosition();

  // Sets the Position of the PLayer Sprite
  sprite.setPosition(sf::Vector2f(xpos - 20, ypos - 20));
  window->draw(sprite);

  // Centres the Camera On the player's new position
  camera.setCenter(sprite.getPosition());
  window->setView(camera);
}