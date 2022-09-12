#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "Enemy.h"
#include "Arrow.h"
#include "Archer.h"

extern double xpos, ypos;
extern sf::RenderWindow window;

Archer::Archer(){
    this->arrowCounter = 0;
    this->coordinates[0] = xpos + rand()%800 - 400;
    this->coordinates[1] = ypos + rand()%800 - 400;

    this->sprite.setPosition(sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    this->sprite.setSize(sf::Vector2f(30,30));
    this->texture1.loadFromFile("ARCHER1.png");
    this->texture2.loadFromFile("ARCHER2.png");
    this->sprite.setTexture(&texture1);

    this->Arrows = new Arrow[0];

    this->fireCounter = 0;
    this->health = 50;
}

void Archer::attack(){
    Arrow* holdArrows = this->Arrows;
    Arrows = new Arrow[arrowCounter+1];
    for (int i = 0; i < arrowCounter; i++){
        Arrows[i] = holdArrows[i];
    }
    delete[] holdArrows;

    Arrow A(this->coordinates[0], this->coordinates[1]);

    Arrows[arrowCounter] = A;
    arrowCounter++;
    return;
}

void Archer::drawArrows(){
    for (int i = 0; i < arrowCounter; i++){
        if (!(this->Arrows[i].UpdatePosition())){
            for (int j = i+1; j < arrowCounter; j++){
                Arrows[j-1] = Arrows[j];
            }
            arrowCounter--;
        }
        window.draw(this->Arrows[i].ArrowShape);
    }
    return;
}

void Archer::movement(){
    if (sqrt(pow(xpos-coordinates[0],2)+pow(ypos-coordinates[1],2)) >= 200){
        this->coordinates[0] = this->coordinates[0] + 2.5*((xpos - this->coordinates[0])/sqrt(pow(xpos-coordinates[0],2)+pow(ypos-coordinates[1],2)));
        this->coordinates[1] = this->coordinates[1] + 2.5*((ypos - this->coordinates[1])/sqrt(pow(xpos-coordinates[0],2)+pow(ypos-coordinates[1],2)));
        sprite.setPosition(sf::Vector2f(this->coordinates[0], this->coordinates[1]));
    }
}

bool Archer::updateEnemy(){
    if (this->health == 0){
        return 0;
    }

    this->drawArrows();
    this->movement();

    this->fireCounter = this->fireCounter + 2;
    if (this->fireCounter == 100){
        this->attack();
        this->fireCounter = 0;
    }

    if (remainder(fireCounter/10, 2) == 0){
        sprite.setTexture(&texture1);
    }
    else{
        sprite.setTexture(&texture2);
    }


    window.draw(this->sprite);
    
    return 1;
}