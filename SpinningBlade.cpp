#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "SpinningBlade.h"
#include "Enemies.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

SpinningBlade::SpinningBlade(int num){  
    this->coordinates[0] = xpos + 200;
    this->coordinates[1] = ypos;

    this->sprite.setPosition(sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    this->sprite.setSize(sf::Vector2f(20,20));
    // this->texture1.loadFromFile("ARCHER1.png");
    // this->texture2.loadFromFile("ARCHER2.png");
    // this->sprite.setTexture(&texture1);
    this->sprite.setFillColor(sf::Color::Blue);

    count = 0;
    
    return;
}

    SpinningBlade::~SpinningBlade(){
        delete[] this->coordinates;
        return;
    }

    void SpinningBlade::hitEnemy(Enemies* enemies){
        for (int i = 0; i < enemies->enemyCounter; i++){
            if (this->sprite.getGlobalBounds().intersects(enemies->enemies[i]->sprite.getGlobalBounds())){
                enemies->enemies[i]->health = enemies->enemies[i]->health - 50;
            }
        }
        return;
    }

    void SpinningBlade::movement(){
        this->coordinates[0] = xpos - (200 * sin((3.14 / 100) * count));
        this->coordinates[1] = ypos - (200 * cos((3.14 / 100) * count));
        this->sprite.setPosition(sf::Vector2f(this->coordinates[0], this->coordinates[1]));
        count++;
        if (count == 200){
            count = 0;
        }
        return;
    }

    bool SpinningBlade::updateAbility(){
        this->movement();

        window.draw(this->sprite);

        return 1;
    }