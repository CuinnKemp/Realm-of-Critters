#ifndef GOLDENSLIME_H
#define GOLDENSLIME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Slime.h"

// Similair to Beast.h, A simple Enemy collides with player to do damage
class GoldenSlime : public Slime{
    public:
        GoldenSlime();
    
        void animation();
};

#endif //GoldenSlime_H