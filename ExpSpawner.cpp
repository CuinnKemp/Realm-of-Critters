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
}

void ExpSpawner::spawnExp(int expPoints, double xpos, double ypos) {
  ExpContainer** holdExpBalls = expBalls;
  expBalls = new ExpContainer*[expBallsCounter + 1];
  for (int i = 0; i < expBallsCounter; i++) {
    expBalls[i] = expBalls[i];
  }
  delete[] holdExpBalls;

  expBalls[expBallsCounter] = new ExpBall;
  expBalls[expBallsCounter]->expPoints = expPoints;

  expBalls[expBallsCounter]->sprite.setPosition(xpos, ypos);
  expBallsCounter++;
}

void ExpSpawner::spawnExp() {
  std::cout << "spawnExp()" << std::endl;
  ExpContainer** holdExpBalls = expBalls;
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
  for (int i = 0; i < expBallsCounter; i++) {
    if (!((*(expBalls[i])).updateExp())) {
      for (int j = i + 1; j < expBallsCounter; j++) {
        expBalls[j - 1] = expBalls[j];
      }
      expBallsCounter--;
    }
  }
}

void ExpSpawner::updateExps() {
  checkExp();
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
