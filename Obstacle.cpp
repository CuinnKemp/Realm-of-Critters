#include "Obstacle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

#include "Obstacle.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

Obstacle::Obstacle() {
  this->grass.loadFromFile("barrier/grass.png");
  this->desert.loadFromFile("barrier/desert.png");
  this->snow.loadFromFile("barrier/snow.png");
  this->dirt.loadFromFile("barrier/dirt.png");
  sf::Texture textureArray[] = {grass, desert, snow, dirt};
  // this->sprite.setTexture(textureArray[0]);
  this->sprite.setScale(sf::Vector2f(2, 2));
  this->sprite.setOrigin(960, 960);
  return;
}

bool Obstacle::updateObstacle() {
  window.draw(this->sprite);

  return 1;
}

Obstacle::~Obstacle() {
  delete[] this->coordinates;
  return;
}
