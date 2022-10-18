#include "GoldenSlime.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"
#include "ExpSpawner.h"
#include "Player.h"
#include "ResourceManager.h"


// External:
extern double xpos, ypos;        // Player Position
extern sf::RenderWindow window;  // Render Window
extern ExpSpawner E1;            // Exp Spawner
extern Player P1;                // Player Class
extern ResourceManager resourceManager;

GoldenSlime::GoldenSlime(){
    // Spawn Coordinates, anywhere between 400 pixels of the current position of
  // the player
  this->coordinates[0] = xpos + rand() % 800 - 400;
  this->coordinates[1] = ypos + rand() % 800 - 400;
  if (coordinates[0] < -1600) {
    coordinates[0] = coordinates[0] + 400;
  } else if (coordinates[0] > 1600) {
    coordinates[0] = coordinates[0] - 400;
  }
  if (coordinates[1] < -1600) {
    coordinates[1] = coordinates[1] + 400;
  } else if (coordinates[1] > 1600) {
    coordinates[1] = coordinates[1] - 400;
  }

  // Sets spawn as its last coordinates
  this->lastCoordinates[0] = coordinates[0];
  this->lastCoordinates[1] = coordinates[1];

  // Sets Sprite Position and size
  this->sprite.setPosition(
      sf::Vector2f(this->coordinates[0], this->coordinates[1]));
  this->sprite.setSize(sf::Vector2f(16, 16));

  // Loads Animation Files

  // Initialises sprite texture, size and shape
  this->sprite.setTextureRect(rectSourceSprite);
  this->sprite.setSize(sf::Vector2f(32, 32));
  this->sprite.setTexture(&resourceManager.slimeWalkDown1);

  // initialises movement direction, current status and animation
  // countP1.savedTime)
  this->direction = 4;
  this->isMoving = false;
  this->animationCount = 0;
  this->sprite.setOrigin(0, 0);

  // initialises total and health
  this->count = 0;
  this->health = 25;
}