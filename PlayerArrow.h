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
  int count;
  double TWOPI = 6.2831853071795865;
  double RAD2DEG = 57.2957795130823209;

  int closestenemy;

  double* arrowCoordinates = new double[2];
  int damage;
  double* targetCoordinates = new double[2];
  double* speedVector = new double[2];
  int counter;

  PlayerArrow(Enemies* enemies);
  PlayerArrow();

  bool outOfBounds();

  bool UpdatePosition(Enemies* enemies);

  void DrawArrows();

  bool EnemycollisionDetection(Enemies* enemies);

  bool movement(Enemies* enemies, PlayerArrow* arrow1);

  bool updateAbility(Enemies* enemies, PlayerArrow* arrow1);
};
#endif  // PlayerArrow_H