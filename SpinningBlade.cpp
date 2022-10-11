#include "SpinningBlade.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

SpinningBlade::SpinningBlade(int num) {
  this->coordinates[0] = xpos;
  this->coordinates[1] = ypos;

  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0] + 20, this->coordinates[1] + 20));
  this->sprite.setOrigin(7, 7);
  this->sprite.setSize(sf::Vector2f(25, 25));
  this->texture1.loadFromFile("Shuriken.png");
  this->sprite.setTexture(&texture1);

  count = 0;

  return;
}

SpinningBlade::~SpinningBlade() {
  delete[] this->coordinates;
  return;
}

void SpinningBlade::hitEnemy(Enemies* enemies) {
  for (int i = 0; i < enemies->enemyCounter; i++) {
    float weaponX = sprite.getPosition().x;
    float weaponY = sprite.getPosition().y;
    float enemyX = enemies->enemies[i]->coordinates[0];
    float enemyY = enemies->enemies[i]->coordinates[1];
    if (abs(weaponX - enemyX) <= 25 && abs(weaponY - enemyY) <= 25) {
      enemies->enemies[i]->health = enemies->enemies[i]->health - 50;
    }
  }
  return;
}

void SpinningBlade::movement() {
  this->coordinates[0] = xpos - (200 * sin((3.14 / 100) * count));
  this->coordinates[1] = ypos - (200 * cos((3.14 / 100) * count));
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.rotate((3.14 / 100) * 500);
  count++;
  if (count == 200) {
    count = 0;
  }
  return;
}

bool SpinningBlade::updateAbility() {
  this->movement();

  window.draw(this->sprite);

  return 1;
}