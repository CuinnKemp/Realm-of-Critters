// include expspawner header
#include "ExpSpawner.h"

//include required libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//include expball class definition
#include "ExpBall.h"

// External : 
extern double xpos, ypos;       // Player Coordinates
extern sf::RenderWindow window; // Render Window

// default constructor
ExpSpawner::ExpSpawner() {

  // Intialisation of counter, array, spawn rate, timer, value of exp
  expBallsCounter = 0;
  expBalls = new ExpBall*[0];
  spawnRate = 5;
  timer = 0;
  baseExpPoints = 5;
}

// Exp spawner for random map occurences
void ExpSpawner::spawnNewExp() {
  
  // Temporary Array to hold all the expBalls
  ExpBall** holdExpSpawner = this->expBalls;

  // Replacing old array with one incrementally bigger
  expBalls = new ExpBall*[expBallsCounter + 1];

  // Filling new Array
  for (int i = 0; i < expBallsCounter; i++) {
    expBalls[i] = holdExpSpawner[i];
  }

  // Delete Temp array
  delete[] holdExpSpawner;

  // Creating new Exp Ball
  expBalls[expBallsCounter] = new ExpBall;
  expBalls[expBallsCounter]->expPoints = baseExpPoints;

  // Setting Position to be random across the map
  expBalls[expBallsCounter]->sprite.setPosition(rand() % 2900 - 1450,
                                                rand() % 2900 - 1450);
  expBalls[expBallsCounter]->sprite.setScale(1, 1);
  expBallsCounter++;
}

// Exp Spawner for monster death
void ExpSpawner::spawnNewExp(int expPoint, double xpos, double ypos) {

  // Creates temporary Array
  ExpBall** holdExpSpawner = this->expBalls;

  // Replaces old array with increamentally bigger one
  expBalls = new ExpBall*[expBallsCounter + 1];

  // fills new array
  for (int i = 0; i < expBallsCounter; i++) {
    expBalls[i] = holdExpSpawner[i];
  }

  // deletes temp array
  delete[] holdExpSpawner;

  // creates new EXP ball
  expBalls[expBallsCounter] = new ExpBall;
  expBalls[expBallsCounter]->expPoints = expPoint;

  // Sets position to be the position of the ExpBall sprite, increments total exp balls
  expBalls[expBallsCounter]->sprite.setPosition(xpos, ypos);
  expBallsCounter++;
}

// check alives function to check whether exps have been collected
void ExpSpawner::checkAlives() {

  // for every exp ball live
  for (int i = 0; i < expBallsCounter; i++) {

    // check collision detection
    if (!((*(expBalls[i])).updateExp())) {

      // if collided, remove from array
      for (int j = i + 1; j < expBallsCounter; j++) {
        expBalls[j - 1] = expBalls[j];
      }
      
      // decrement total exp balls
      expBallsCounter--;
    }
  }
}

// checks for "dead" exps and spawns new exps randomly
void ExpSpawner::updateExps() {
  // Collision Detection
  this->checkAlives();

  // Increments Timer to spawn new exp ball randomly on map
  timer++;
  if (timer == 2000) {
    this->spawnNewExp();
    timer = 0;
  }
}

ExpSpawner::~ExpSpawner() {
  // Destructor for all current expBalls on map
  for (int i = 0; i < expBallsCounter; i++) {
    delete expBalls[i];
  }
  delete[] expBalls;
}

// soft deconstructor for expballs
void ExpSpawner::deleteExpBalls() {
  // Deletes all exp balls upon command;
  for (int i = 0; i < expBallsCounter; i++) {
    delete expBalls[i];
  }
  expBallsCounter = 0;
}