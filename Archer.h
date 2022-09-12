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
    double* coordinates = new double[2];
    int arrowCounter;
    int fireCounter;
    Arrow* Arrows;
    int health;
    sf::RectangleShape sprite;
    sf::Texture texture1;
    sf::Texture texture2;

    Archer();

    void attack();

    void drawArrows();

    void movement();
    
    void updatePosition();

    bool updateEnemy();


};
#endif //ARCHER_H