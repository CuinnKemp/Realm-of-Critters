#include "Beast.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "Enemy.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

Beast::Beast() {
  this->arrowCounter = 0;
  this->coordinates[0] = xpos + rand() % 800 - 400;
  this->coordinates[1] = ypos + rand() % 800 - 400;

  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.setSize(sf::Vector2f(30, 30));
  walkDown1.loadFromFile("beastAnimation/Walk/walkDown1.png");
  walkDown2.loadFromFile("beastAnimation/Walk/walkDown2.png");
  walkDown3.loadFromFile("beastAnimation/Walk/walkDown3.png");
  walkDown4.loadFromFile("playerAnimation/Walk/walkDown4.png");
  walkUp1.loadFromFile("playerAnimation/Walk/walkUp1.png");
  walkUp2.loadFromFile("playerAnimation/Walk/walkUp2.png");
  walkUp3.loadFromFile("playerAnimation/Walk/walkUp3.png");
  walkUp4.loadFromFile("playerAnimation/Walk/walkUp4.png");
  walkLeft1.loadFromFile("playerAnimation/Walk/walkLeft1.png");
  walkLeft2.loadFromFile("playerAnimation/Walk/walkLeft2.png");
  walkLeft3.loadFromFile("playerAnimation/Walk/walkLeft3.png");
  walkLeft4.loadFromFile("playerAnimation/Walk/walkLeft4.png");
  walkRight1.loadFromFile("playerAnimation/Walk/walkRight1.png");
  walkRight2.loadFromFile("playerAnimation/Walk/walkRight2.png");
  walkRight3.loadFromFile("playerAnimation/Walk/walkRight3.png");
  walkRight4.loadFromFile("playerAnimation/Walk/walkRight4.png");
  this->sprite.setTexture(&texture1);

  this->Arrows = new Arrow[0];

  this->fireCounter = 0;
  this->health = 50;
}

Beast::~Beast() { delete[] this->coordinates; }

void Beast::attack() {
  Arrow* holdArrows = this->Arrows;
  Arrows = new Arrow[arrowCounter + 1];
  for (int i = 0; i < arrowCounter; i++) {
    Arrows[i] = holdArrows[i];
  }
  delete[] holdArrows;

  Arrow A(coordinates[0], this->coordinates[1]);

  Arrows[arrowCounter] = A;
  arrowCounter++;
  return;
}

void Beast::drawArrows() {
  for (int i = 0; i < arrowCounter; i++) {
    if (!(this->Arrows[i].UpdatePosition())) {
      for (int j = i + 1; j < arrowCounter; j++) {
        Arrows[j - 1] = Arrows[j];
      }
      arrowCounter--;
    }
    window.draw(this->Arrows[i].ArrowShape);
  }
  return;
}

void Beast::movement() {
  if (sqrt(pow(xpos - coordinates[0], 2) + pow(ypos - coordinates[1], 2)) >=
      200) {
    this->coordinates[0] =
        this->coordinates[0] + 2.5 * ((xpos - this->coordinates[0]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));
    this->coordinates[1] =
        this->coordinates[1] + 2.5 * ((ypos - this->coordinates[1]) /
                                      sqrt(pow(xpos - coordinates[0], 2) +
                                           pow(ypos - coordinates[1], 2)));
    sprite.setPosition(
        sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  }
}

bool Beast::updateEnemy() {
  if (this->health == 0) {
    return 0;
  }

  this->drawArrows();
  this->movement();

  this->fireCounter = this->fireCounter + 2;
  if (this->fireCounter == 100) {
    this->attack();
    this->fireCounter = 0;
  }

  if (remainder(fireCounter / 10, 2) == 0) {
    sprite.setTexture(&texture1);
  } else {
    sprite.setTexture(&texture2);
  }

  window.draw(this->sprite);

  return 1;
}