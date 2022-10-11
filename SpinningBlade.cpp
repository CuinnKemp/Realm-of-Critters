#include "SpinningBlade.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"

// External:
extern double xpos, ypos;       //Player Position
extern sf::RenderWindow window; //Render Window

SpinningBlade::SpinningBlade(int num) {

  // Sets Coordinates of the player
  this->coordinates[0] = xpos;
  this->coordinates[1] = ypos;

  // Sets the Position of the blade sprite, 20 pixels out from the player
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0] + 20, this->coordinates[1] + 20));
  this->sprite.setSize(sf::Vector2f(14, 32));

  // loads texture and sets it
  this->texture1.loadFromFile("Fork.png");
  this->sprite.setTexture(&texture1);

  // initialises count
  count = 0;
  return;
}

SpinningBlade::~SpinningBlade() {
  // default destructor to delete spinning blade
  delete[] this->coordinates;
  return;
}

void SpinningBlade::hitEnemy(Enemies* enemies) {

  // for amount of enemies on screen
  for (int i = 0; i < enemies->enemyCounter; i++) {

    // gets position of the sprite
    float weaponX = sprite.getPosition().x;
    float weaponY = sprite.getPosition().y;

    // gets position of the current enemy in the loop
    float enemyX = enemies->enemies[i]->coordinates[0];
    float enemyY = enemies->enemies[i]->coordinates[1];

    //checks collision, if collided deals damage to the enemies
    if (abs(weaponX - enemyX) <= 30 && abs(weaponY - enemyY) <= 30) {
      enemies->enemies[i]->health = enemies->enemies[i]->health - 50;
    }
  }
  return;
}

void SpinningBlade::movement() {
  // Updates the spinning blade to move in a circular fashion around the player
  this->coordinates[0] = xpos - (200 * sin((3.14 / 100) * count));
  this->coordinates[1] = ypos - (200 * cos((3.14 / 100) * count));

  // Sets the sprite position to the new coordinates
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  // rotates the sprite accordingly
  this->sprite.rotate((3.14 / 100) * 250);

  // Iterates count which causes the spin, resets at 200 to make a perfect circle
  count++;
  if (count == 200) {
    count = 0;
  }
  return;
}

bool SpinningBlade::updateAbility() {
  
  // calls movement
  this->movement();

  // draws Sprite on render window
  window.draw(this->sprite);

  return 1;
}