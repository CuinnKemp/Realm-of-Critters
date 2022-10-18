#ifndef GOLDENSLIME_H
#define GOLDENSLIME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Enemy.h"
#include "Slime.h"

// Similair to Beast.h, A simple Enemy collides with player to do damage
class GoldenSlime : public Slime {
    GoldenSlime();
};

#endif //GoldenSlime_H