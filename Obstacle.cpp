// include Obstacle header
#include "Obstacle.h"

//include required libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

//External:
extern double xpos, ypos; //Player Position
extern sf::RenderWindow window; //RenderWindow

// default constructor
Obstacle::Obstacle() {
//Sets Scale and Origin point of Sprites
  this->sprite.setScale(sf::Vector2f(2, 2));
  this->sprite.setOrigin(960, 960);
}

//update obstacle
bool Obstacle::updateObstacle() {
  
  // Draw Sprite
  window.draw(this->sprite);
  return 1;
}

//deconstructor
Obstacle::~Obstacle() {

  // Delete Obstacles
  delete[] this->coordinates;
  return;
}
