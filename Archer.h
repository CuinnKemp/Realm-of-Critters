#ifndef ARCHER_H
#define ARCHER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "Enemy.h"
#include "Arrow.h"

class Archer : public Enemy{
    public:
    int arrowCounter;
    int fireCounter;
    Arrow* Arrows;
    sf::Texture texture1;
    sf::Texture texture2;

    Archer();

    ~Archer();

    void attack();

    void drawArrows();

    void movement();
    
    void updatePosition();

    bool updateEnemy();


};
#endif //ARCHER_H