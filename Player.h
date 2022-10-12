#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "PowerUp.h"

class Player {
 public:
  double movSpeed, oldXpos, oldYpos;
  sf::RectangleShape sprite;
  sf::RenderWindow* window;
  sf::View camera;
  double health;
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int currentExp;
  int expCap;
  int level;
  int animationCount;

  Player(double Pxpos, double Pypos, double width, double height,
         sf::RenderWindow* window);

  void resetPlayer();

  void levelPlayer();

  void moveRight();

  void moveLeft();

  void moveUp();

  void moveDown();

  void getPosition();

  bool isAlive();

  void DrawPlayer(sf::RenderWindow* window);
};

#endif  // PLAYER_H