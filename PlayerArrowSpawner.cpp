#include "PlayerArrowSpawner.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "PlayerArrow.h"

extern Enemies a1;

PlayerArrowSpawner::PlayerArrowSpawner() {
  playerArrowCounter = 0;
  playerArrows = new PlayerArrow*[0];
}

void PlayerArrowSpawner::spawnNewArrow() {
  PlayerArrow** holdPlayerArrowSpawner = this->playerArrows;
  playerArrows = new PlayerArrow*[playerArrowCounter + 1];
  for (int i = 0; i < playerArrowCounter; i++) {
    playerArrows[i] = holdPlayerArrowSpawner[i];
  }
  delete[] holdPlayerArrowSpawner;
  playerArrows[playerArrowCounter] = new PlayerArrow;
  // std::cout << obstacleCounter << std::endl;

  playerArrows[playerArrowCounter]->sprite.setPosition(
      playerArrows[playerArrowCounter]->coordinates[0],
      playerArrows[playerArrowCounter]->coordinates[1]);
  playerArrowCounter++;
}

void PlayerArrowSpawner::updateArrows() {
  for (int i = 0; i < playerArrowCounter; i++) {
    playerArrows[i]->updateAbility(&a1, playerArrows[i]);
  }
}
PlayerArrowSpawner::~PlayerArrowSpawner() {
  for (int i = 0; i < playerArrowCounter; i++) {
    delete playerArrows[i];
  }
  delete[] playerArrows;
}
