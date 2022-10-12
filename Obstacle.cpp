#include "Obstacle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

//External:
extern double xpos, ypos; //Player Position
extern sf::RenderWindow window; //RenderWindow


Obstacle::Obstacle() {
//Sets Scale and Origin point of Sprites
  this->sprite.setScale(sf::Vector2f(2, 2));
  this->sprite.setOrigin(960, 960);
}

bool Obstacle::updateObstacle() {
  
  // Draw Sprite
  window.draw(this->sprite);
  return 1;
}

Obstacle::~Obstacle() {

  // Delete Obstacles
  delete[] this->coordinates;
  return;
}
