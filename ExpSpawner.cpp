#include "ExpSpawner.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "ExpBall.h"
#include "ExpContainer.h"

extern sf::RenderWindow window;
extern double xpos, ypos;

ExpSpawner::ExpSpawner() {
  expBallsCounter = 0;
  expBalls = new ExpContainer*[0];
  baseExpPoints = 10;
  spawnRate = 5;
  timer = 0;

  for (int i = 0; i < 100; i++) {
    spawnExp();
  }
}

void ExpSpawner::spawnExp(int expPoints, double xpos1, double ypos1) {
  ExpContainer** holdExpBalls = this->expBalls;
  expBalls = new ExpContainer*[expBallsCounter + 1];
  for (int i = 0; i < expBallsCounter; i++) {
    expBalls[i] = expBalls[i];
  }
  delete[] holdExpBalls;

  expBalls[expBallsCounter] = new ExpBall;
  expBalls[expBallsCounter]->expPoints = expPoints;

  expBalls[expBallsCounter]->sprite.setPosition(xpos1, ypos1);
  expBallsCounter++;
}

void ExpSpawner::spawnExp() {
  ExpContainer** holdExpBalls = this->expBalls;
  expBalls = new ExpContainer*[expBallsCounter + 1];
  for (int i = 0; i < expBallsCounter; i++) {
    expBalls[i] = expBalls[i];
  }
  delete[] holdExpBalls;

  expBalls[expBallsCounter] = new ExpBall;
  expBalls[expBallsCounter]->expPoints = baseExpPoints;

  expBalls[expBallsCounter]->sprite.setPosition(xpos + rand() % 800 - 400,
                                                ypos + rand() % 800 - 400);
  expBallsCounter++;
}

void ExpSpawner::checkExp() {
  std::cout << "checkExp()" << std::endl;
  std::cout << expBallsCounter << std::endl;
  for (int i = 0; i < expBallsCounter; i++) {
    std::cout << "loop" << std::endl;
    if (!((*(expBalls[i])).updateExp())) {
      std::cout << "true" << std::endl;
      for (int j = i + 1; j < expBallsCounter; j++) {
        expBalls[j - 1] = expBalls[j];
      }
      expBallsCounter--;
    }
    std::cout << "false" << std::endl;
  }
}

void ExpSpawner::updateExps() {
  this->checkExp();
  timer++;
  if (timer == 100 / spawnRate) {
    spawnExp();
    timer = 0;
  }
}

ExpSpawner::~ExpSpawner() {
  for (int i = 0; i < expBallsCounter; i++) {
    delete expBalls[i];
  }
  delete[] expBalls;
}
