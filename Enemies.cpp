#include "Enemies.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Beast.h"
#include "Enemy.h"
#include "Player.h"
#include "Slime.h"

extern Player P1;
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
  if (rand() % 2 == 0) {
    enemies[enemyCounter] = new Beast;
  } else {
    enemies[enemyCounter] = new Slime;
  }

  // increases the total enemies on the screen
  enemyCounter++;
}

void Enemies::checkAlives() {
  // runs through every enemy in the enemies array
  for (int i = 0; i < enemyCounter; i++) {
    // Runs each individual updateEnemy function for each of the beasts to check
    // if they are alive
    if (!((*(enemies[i])).updateEnemy())) {
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
       (100 - (P1.clock.getElapsedTime().asSeconds() + P1.savedTime)))) {
    this->spawnNewEnemy();
    timer = 0;
  }
}

void Enemies::deleteEnemies() {
  for (int i = 0; i < enemyCounter; i++) {
    delete enemies[i];
  }
  enemyCounter = 0;
}

Enemies::~Enemies() {
  // Deletes all instances of enemies alive
  for (int i = 0; i < enemyCounter; i++) {
    delete enemies[i];
  }
  delete[] enemies;
}
