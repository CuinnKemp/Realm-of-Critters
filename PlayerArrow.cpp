#include "PlayerArrow.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "Player.h"

extern Player P1;
extern double xpos, ypos;
extern sf::RenderWindow window;

PlayerArrow::PlayerArrow() {}

PlayerArrow::PlayerArrow(Enemies* enemies, int num) {
  // std::cout << enemies->enemyCounter << std::endl;
  if (enemies->enemyCounter >= 1) {
    // std::cout << "Running" << std::endl;
    // set damage
    this->damage = 25;

    // Sets the initial position of the arrow to the player
    this->arrowCoordinates[0] = xpos;
    this->arrowCoordinates[1] = ypos;

    // creates an array of the distances of all enemies on the screen
    double distance[enemies->enemyCounter];

    // fills distance array
    for (int t = 0; t < enemies->enemyCounter; t++) {
      distance[t] = sqrt(
          pow((arrowCoordinates[0] - (enemies->enemies[t]->coordinates[0])),
              2) +
          pow((arrowCoordinates[0] - (enemies->enemies[t]->coordinates[0])),
              2));
    }

    // the finds the shortest distance between the player and an enemy


    // finds place in enemies array of the enemy with the shoretest distance to
    // the player
    
    int enemyPlaceInList = 0;

    // sorts distance array to find shortest distance
    for (int j = 0; j < num; j++){
      double current = 0;
      double shortest = distance[0];
      for (int i = 1; i < enemies->enemyCounter; i++) {
      if (distance[i] < shortest &&  i != enemyPlaceInList) {
        current = i;
        }
      }
      enemyPlaceInList = current;
    }

    // sets the target coordinates to the shortest distance
    this->targetCoordinates[0] =
        enemies->enemies[enemyPlaceInList]->coordinates[0];

    this->targetCoordinates[1] =
        enemies->enemies[enemyPlaceInList]->coordinates[1];
    // sets the target enemy for other functions use
    closestenemy = enemyPlaceInList;
    // std::cout << closestenemy << std::endl;

    // testing to see whether or not it finds the enemy with the shortest
    // distance
    for (int i = 0; i < 50; i++) {
      // std::cout << enemyPlaceInList << std::endl;
    }

    // same process as arrow, setting the speed vectors for the bullet
    double divisor = sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
                          pow(targetCoordinates[1] - arrowCoordinates[1], 2));

    this->speedVector[0] =
        10 * (this->targetCoordinates[0] - this->arrowCoordinates[0]) / divisor;
    this->speedVector[1] =
        10 * (this->targetCoordinates[1] - this->arrowCoordinates[1]) / divisor;
    // sets sprite (my pc for some reason doesnt like to load it)

    this->sprite.setPosition(this->arrowCoordinates[0],
                             this->arrowCoordinates[1]);
    this->sprite.setSize(sf::Vector2f(10, 30));

    // Calculates angle between player and enemy
    double theta = atan2(
        targetCoordinates[0] - arrowCoordinates[0],
        targetCoordinates[1] -
            arrowCoordinates[1]);  // std::cout << theta << " b" << std::endl;
    if (theta < 0.0) {
      theta += TWOPI;
    }
    theta = RAD2DEG * theta;

    // std::cout << theta << std::endl;

    // Rotates Sprite accordingly
    this->sprite.rotate(180 - theta);
  }
}

// detects if the sprite has collided with the closest enemy
bool PlayerArrow::EnemycollisionDetection(Enemies* a1) {
  // std::cout << "EnemycollisionDetection() 1" << std::endl;
  // std::cout << closestenemy << std::endl;
  for (int i = 0; i < a1->enemyCounter; i++) {
    float weaponX = sprite.getPosition().x;
    float weaponY = sprite.getPosition().y;
    float enemyX = a1->enemies[i]->coordinates[0];
    float enemyY = a1->enemies[i]->coordinates[1];
    // std::cout << "EnemycollisionDetection() qqwqweqweqwe" << std::endl;
    if (abs(weaponX - enemyX) <= 30 && abs(weaponY - enemyY) <= 30) {
      a1->enemies[i]->health = a1->enemies[i]->health - this->damage;
      // std::cout << "EnemycollisionDetection() ascjnaslj" << std::endl;
      return 1;
    }
  }

  // std::cout << "EnemycollisionDetection() 2" << std::endl;
  return 0;
}

// same as arrow, detects if projectile is out of bounds
bool PlayerArrow::outOfBounds() {
  if (sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
           pow(targetCoordinates[1] - arrowCoordinates[1], 2)) == 0) {
    return 1;
  }
  return 0;
}

bool PlayerArrow::UpdatePosition(Enemies* enemies) {
  // std::cout << "UpdatePosition() 1" << std::endl;
  if (this->EnemycollisionDetection(enemies) == 1 || this->outOfBounds() == 1) {
    // std::cout << "UpdatePosition() 2" << std::endl;
    return 0;
  }

  this->arrowCoordinates[0] = this->arrowCoordinates[0] + this->speedVector[0];
  this->arrowCoordinates[1] = this->arrowCoordinates[1] + this->speedVector[1];
  this->sprite.setPosition(
      sf::Vector2f(this->arrowCoordinates[0], this->arrowCoordinates[1]));
  // std::cout << "UpdatePosition() 3" << std::endl;
  window.draw(this->sprite);
  return 1;
}

// Movement function, for some reason this doesnt seem to work, its similair
// to how arrow works
bool PlayerArrow::movement(Enemies* enemies, PlayerArrow* arrow1) {
  if (enemies->enemyCounter >= 1) {
    if (this->EnemycollisionDetection(enemies) == 1 ||
        this->outOfBounds() == 1) {
      return 0;
    }
    arrow1->arrowCoordinates[0] =
        arrow1->arrowCoordinates[0] + arrow1->speedVector[0];
    arrow1->arrowCoordinates[1] =
        arrow1->arrowCoordinates[1] + arrow1->speedVector[1];
    arrow1->sprite.setPosition(
        sf::Vector2f(arrow1->arrowCoordinates[0], arrow1->arrowCoordinates[1]));
  }
  return 1;
}

// update ability is the same as SpinningBlade, also something wrong here i
// think
bool PlayerArrow::updateAbility(Enemies* enemies, PlayerArrow* arrow1) {
  if (this->movement(enemies, arrow1) == 0) {
    return 0;
  }

  // window.draw(this->sprite);

  return 1;
}