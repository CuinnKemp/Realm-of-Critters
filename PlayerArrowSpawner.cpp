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
  playerArrows = new PlayerArrow[0];
}

void PlayerArrowSpawner::attack() {
  if (a1.enemyCounter >= 3) {
    PlayerArrow* holdPlayerArrowSpawner = this->playerArrows;
    playerArrows = new PlayerArrow[playerArrowCounter + 1];
    for (int i = 0; i < playerArrowCounter; i++) {
      playerArrows[i] = holdPlayerArrowSpawner[i];
    }
    delete[] holdPlayerArrowSpawner;

    PlayerArrow A(&a1);

    playerArrows[playerArrowCounter] = A;
    playerArrowCounter++;
    return;
  }
}

void PlayerArrowSpawner::drawArrows() {
  for (int i = 0; i < playerArrowCounter; i++) {
    if (!(this->playerArrows[i].UpdatePosition())) {
      std::cout << "UpdatePosition() done" << std::endl;
      for (int j = i + 1; j < playerArrowCounter; j++) {
        playerArrows[j - 1] = playerArrows[j];
      }
      playerArrowCounter--;
    }
    this->playerArrows[i].movement(&a1, &playerArrows[i]);
    window.draw(playerArrows[i].sprite);
  }
  return;
}
PlayerArrowSpawner::~PlayerArrowSpawner() {
  for (int i = 0; i < playerArrowCounter; i++) {
    delete &playerArrows[i];
  }
  delete[] playerArrows;
}
