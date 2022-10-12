#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Enemy {
 public:
  double* coordinates = new double[2];
  double* lastCoordinates = new double[2];
  int health;
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;
  virtual bool updateEnemy();
};
#endif  // ENEMY_H