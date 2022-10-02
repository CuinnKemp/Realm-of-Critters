#include "PlayerArrow.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "Player.h"

extern Player P1;
extern Enemies* a1;
extern double xpos, ypos;
extern sf::RenderWindow window;

pArrow::pArrow(Enemies* enemies) {
  if (enemies->enemyCounter >= 3) {
    // set damage
    this->damage = 10;

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
    double shortest = distance[0];

    // finds place in enemies array of the enemy with the shoretest distance to
    // the player
    int enemyPlaceInList = 0;

    // sorts distance array to find shortest distance
    for (int i = 1; i < enemies->enemyCounter; i++) {
      if (distance[i] < shortest) {
        enemyPlaceInList = i;
      }
    }

    // sets the target coordinates to the shortest distance
    this->targetCoordinates[0] =
        enemies->enemies[enemyPlaceInList]->coordinates[0];
    this->targetCoordinates[1] =
        enemies->enemies[enemyPlaceInList]->coordinates[1];

    // sets the target enemy for other functions use
    closestenemy = enemyPlaceInList;

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
    this->sprite.setSize(sf::Vector2f(10, 10));
    this->texture1.loadFromFile("fork.png");
    this->sprite.setTexture(&texture1);
  }
}

// detects if the sprite has collided with the closest enemy
bool pArrow::EnemycollisionDetection(Enemies* enemies) {
  if (enemies->enemies[closestenemy]->sprite.getGlobalBounds().intersects(
          this->sprite.getGlobalBounds())) {
    enemies->enemies[closestenemy]->health =
        enemies->enemies[closestenemy]->health - this->damage;
    return 1;
  }
  return 0;
}

// same as arrow, detects if projectile is out of bounds
bool pArrow::outOfBounds() {
  if (sqrt(pow(targetCoordinates[0] - arrowCoordinates[0], 2) +
           pow(targetCoordinates[1] - arrowCoordinates[1], 2)) == 0) {
    return 1;
  }
  return 0;
}

// Movement function, for some reason this doesnt seem to work, its similair to
// how arrow works
bool pArrow::movement(Enemies* enemies, pArrow* arrow1) {
  if (enemies->enemyCounter >= 3) {
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
bool pArrow::updateAbility(Enemies* enemies, pArrow* arrow1) {
  this->movement(enemies, arrow1);

  window.draw(this->sprite);

  return 1;
}
