#include "PlayerArrowSpawner.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "PlayerArrow.h"


PlayerArrowSpawner::PlayerArrowSpawner(Enemies* a1) {
  this->a1 = a1;
  playerArrowCounter = 0;
  texturearrow.loadFromFile("playerAnimation/Arrow.png");
  playerArrows = new PlayerArrow[0];
}

void PlayerArrowSpawner::attack() {
  if (this->a1->enemyCounter >= 1) {
    PlayerArrow* holdPlayerArrowSpawner = this->playerArrows;
    playerArrows = new PlayerArrow[playerArrowCounter + 1];
    for (int i = 0; i < playerArrowCounter; i++) {
      playerArrows[i] = holdPlayerArrowSpawner[i];
    }
    delete[] holdPlayerArrowSpawner;

    PlayerArrow A(a1);

    playerArrows[playerArrowCounter] = A;
    playerArrowCounter++;
    return;
  }
}

void PlayerArrowSpawner::drawArrows() {
  for (int i = 0; i < playerArrowCounter; i++) {
    playerArrows[i].sprite.setTexture(&texturearrow);
    if (!(this->playerArrows[i].UpdatePosition(this->a1))) {
      //std::cout << "UpdatePosition() done" << std::endl;
      for (int j = i + 1; j < playerArrowCounter; j++) {
        playerArrows[j - 1] = playerArrows[j];
      }
      playerArrowCounter--;
    }
    //window.draw(playerArrows[i].sprite);
  }
  return;
}
PlayerArrowSpawner::~PlayerArrowSpawner() {
  for (int i = 0; i < playerArrowCounter; i++) {
    delete &playerArrows[i];
  }
  delete[] playerArrows;
}
