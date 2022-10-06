#ifndef PLAYERARROW_H
#define PLAYERARROW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemies.h"
#include "PowerUp.h"

class PlayerArrow : public PowerUp {
 public:
  sf::Texture texture1;
  int count;

  int closestenemy;

  double* arrowCoordinates = new double[2];
  int damage;
  double* targetCoordinates = new double[2];
  double* speedVector = new double[2];
  int counter;

  PlayerArrow(Enemies* enemies);
  PlayerArrow();

  bool outOfBounds();

  bool UpdatePosition();

  void DrawArrows();

  bool EnemycollisionDetection(Enemies* enemies);

  bool movement(Enemies* enemies, PlayerArrow* arrow1);

  bool updateAbility(Enemies* enemies, PlayerArrow* arrow1);
};
#endif  // PlayerArrow_H