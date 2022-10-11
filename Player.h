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
  // Speed and Prior Position
  double movSpeed, oldXpos, oldYpos;

  //Sprites, Animations and Walk cycle
  sf::RectangleShape sprite;
  sf::RenderWindow* window;
  sf::View camera;
  sf::Texture idleLeft, idleRight, idleUp, idleDown, walkDown1, walkDown2,
      walkDown3, walkDown4, walkUp1, walkUp2, walkUp3, walkUp4, walkLeft1,
      walkLeft2, walkLeft3, walkLeft4, walkRight1, walkRight2, walkRight3,
      walkRight4;
  sf::RectangleShape healthBarBack;
  sf::RectangleShape healthBarFront;

  // Properties of Player, health, exp, direction, boolean movement, level
  double health;
  int direction;  // 1 = left, 2 = right, 3 = up, 4 = down
  bool isMoving;
  int currentExp;
  int expCap;
  int level;
  int animationCount;


  // Constructor with parameters, position and Screen Width and Height to set position
  Player(double Pxpos, double Pypos, double width, double height,
         sf::RenderWindow* window);

  // Resetting all player variables after death
  void resetPlayer();

  //  Levelling Sequence for Player
  void levelPlayer();

  // Movement for each Player Direction
  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();

  // Returns Player Position
  void getPosition();

  // Checks whether or not Player is alive
  bool isAlive();
  
  // Draws Player
  void DrawPlayer(sf::RenderWindow* window);
};

#endif  // PLAYER_H