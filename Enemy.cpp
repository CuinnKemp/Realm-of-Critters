// include enemy header
#include "Enemy.h"

// include required libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

// default update enemy
// returns 0 so that broken enemy is deleted
bool Enemy::updateEnemy() { return 0; } 

// default deconstructor
void Enemy::deconstructor(){ return; }
