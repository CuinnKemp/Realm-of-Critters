#include "PlayerArrowSpawner.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "PlayerArrow.h"

PlayerArrowSpawner::PlayerArrowSpawner(Enemies* a1) {
  // Copies Enemey Array into PlayerArrowSpawner
  this->a1 = a1;

  // Initialisies Counter and Array; loads Sprite
  playerArrowCounter = 0;
  texturearrow.loadFromFile("playerAnimation/Arrow.png");
  playerArrows = new PlayerArrow[0];
}

void PlayerArrowSpawner::attack() {
  // If there is at least one enemy alive
  if (this->a1->enemyCounter >= 1) {
    std::cout << "newArrow" << std::endl;
    // Temporary Array
    PlayerArrow* holdPlayerArrowSpawner = this->playerArrows;

    // Replacing old Array with incramental Larger Array
    playerArrows = new PlayerArrow[playerArrowCounter + 1];

    // Filling New array
    for (int i = 0; i < playerArrowCounter; i++) {
      playerArrows[i] = holdPlayerArrowSpawner[i];
    }

    // Deleting Temp Array
    delete[] holdPlayerArrowSpawner;

    // Spawning new Arrow
    PlayerArrow A(a1);

    // Filling Array and incrementing counter
    playerArrows[playerArrowCounter] = A;
    playerArrowCounter++;
    return;
  }
}

void PlayerArrowSpawner::drawArrows() {
  // For all active arrows
  for (int i = 0; i < playerArrowCounter; i++) {
    // Draws Sprite
    playerArrows[i].sprite.setTexture(&texturearrow);

    // collision Detection
    if (!(this->playerArrows[i].UpdatePosition(this->a1))) {
      // std::cout << "UpdatePosition() done" << std::endl;

      // If collided, delete from array
      for (int j = i + 1; j < playerArrowCounter; j++) {
        playerArrows[j - 1] = playerArrows[j];
      }

      // decrements
      playerArrowCounter--;
    }
    // window.draw(playerArrows[i].sprite);
  }
  return;
}

PlayerArrowSpawner::~PlayerArrowSpawner() {
  // Deletes PlayerArrows as destructor
  for (int i = 0; i < playerArrowCounter; i++) {
    delete &playerArrows[i];
  }
  delete[] playerArrows;
}
