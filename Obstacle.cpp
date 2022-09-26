#include "Obstacle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

#include "Obstacle.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

Obstacle::Obstacle(int type, float posX, float posY) {
  this->grass.loadFromFile("barrier/grass.png");
  this->desert.loadFromFile("barrier/desert.png");
  this->snow.loadFromFile("barrier/snow.png");
  this->dirt.loadFromFile("barrier/dirt.png");
  sf::Texture textureArray[] = {grass, desert, snow, dirt};
  this->sprite.setTexture(textureArray[type - 1]);
  this->coordinates[0] = posX;
  this->coordinates[1] = posY;
  this->sprite.setScale(sf::Vector2f(14, 32));

  return;
}

Obstacle::~Obstacle() {
  delete[] this->coordinates;
  return;
}
