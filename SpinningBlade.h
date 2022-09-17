#ifndef SPINNINGBLADE_H
#define SPINNINGBLADE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "PowerUp.h"
#include "Enemies.h"

class SpinningBlade : public PowerUp{
    public:
    sf::Texture texture1;
    sf::Texture texture2;
    int count;

    SpinningBlade(int num);

    ~SpinningBlade();

    void hitEnemy(Enemies* enemies);

    void movement();
    
    void updatePosition();

    bool updateAbility();


};
#endif //SPINNINGBLADE_H