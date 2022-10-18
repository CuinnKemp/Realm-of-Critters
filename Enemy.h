#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Virtual Class 
class Enemy {
 public:

 // Coordinates of Enemy
  double* coordinates = new double[2];
  double* lastCoordinates = new double[2];

  // Health
  int health;

  // Sprite
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;

  // virtual soft deconstructor 
  virtual void deconstructor();

  // Virtual Function which is repeated every loop to update position and actions
  virtual bool updateEnemy();
};
#endif  // ENEMY_H