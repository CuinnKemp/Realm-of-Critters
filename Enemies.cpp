// include enemies header
#include "Enemies.h"

//include required libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

// include beast slime enemy and player class definitions
#include "Beast.h"
#include "Slime.h"
#include "Enemy.h"
#include "Player.h"

#include "GoldenSlime.h"

//external variable:
extern Player P1; //player

Enemies::Enemies() {
  // Initialises all variables, sets the enemy counter to 0,
  // creates an array of enemies, and sets the spawn rate to 5
  enemyCounter = 0;
  enemies = new Enemy*[0];
  spawnRate = 5;
  timer = 0;
}

void Enemies::spawnNewEnemy() {
  // Creates a temporary copy of enemies in HoldEnemies
  Enemy** holdEnemies = this->enemies;

  // replaces old enemy array with an incramentally larger one
  enemies = new Enemy*[enemyCounter + 1];

  // Places all enemies from HoldEnemies back into enemies
  for (int i = 0; i < enemyCounter; i++) {
    enemies[i] = holdEnemies[i];
  }

  // Deletes the temporary array
  delete[] holdEnemies;

  // Randomly chooses between a beast and a slime to spawn
  enemies[enemyCounter] = new GoldenSlime;
  // if (rand() % 2 == 0) {
  //   enemies[enemyCounter] = new Beast;
  // } else {
  //   enemies[enemyCounter] = new Slime;
  // }

  // increases the total enemies on the screen
  enemyCounter++;
}


void Enemies::checkAlives() {
  // runs through every enemy in the enemies array
  for (int i = 0; i < enemyCounter; i++) {
    // Runs each individual updateEnemy function for each of the beasts to check
    // if they are alive
    if (!((*(enemies[i])).updateEnemy())) {
      // calls the virtual deconstructor
      enemies[i]->deconstructor();
      // if the enemy isnt alive, removes them from the array
      for (int j = i + 1; j < enemyCounter; j++) {
        enemies[j - 1] = enemies[j];
      }

      // decrement the total enemy counter
      enemyCounter--;
    }
  }
}

void Enemies::updateEnemies() {
  // Checks whether or not any enemies have died
  this->checkAlives();

  // increments the timer, if it reachers threshold it spawns a new enemy on
  // screen
  timer++;
  if (timer >=
      (1 / (P1.clock.getElapsedTime().asSeconds() + P1.savedTime) +
       (200 - (P1.clock.getElapsedTime().asSeconds() + P1.savedTime)))) {
    this->spawnNewEnemy();
    timer = 0;
  }
}

//soft deconstructor to clear unused memory
void Enemies::deleteEnemies() {
  // calls the deconstructor and deletes all the enemies in the array
  for (int i = 0; i < enemyCounter; i++) {
    enemies[i]->deconstructor();
    delete enemies[i];
  }
  // sets enemy counter to 0;
  enemyCounter = 0;
}

Enemies::~Enemies() {
  // Deletes all instances of enemies alive
  for (int i = 0; i < enemyCounter; i++) {
    enemies[i]->deconstructor();
    delete enemies[i];
  }
  // deletes the enemies array
  delete[] enemies;
}
