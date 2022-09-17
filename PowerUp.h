#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

class PowerUp{
    public:
    double* coordinates = new double[2];
    sf::RectangleShape sprite;
    virtual bool updateAbility();
};
#endif //POWERUP_H