#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "Enemy.h"
#include "Archer.h"
#include "Enemies.h"

Enemies::Enemies(){
    enemyCounter = 0;
    enemies = new Enemy*[0];
    spawnRate = 5;
    timer = 0;
}
    
void Enemies::spawnNewEnemy(){
    Enemy** holdEnemies = this->enemies;
    enemies = new Enemy*[enemyCounter+1];
    for (int i = 0; i < enemyCounter; i++){
        enemies[i] = holdEnemies[i];
    }
    delete[] holdEnemies;

    enemies[enemyCounter] = new Archer;
    enemyCounter++;
}

void Enemies::checkAlives(){
    for (int i = 0; i < enemyCounter; i++){
        if (!((*(enemies[i])).updateEnemy())){
            for (int j = i+1; j < enemyCounter; j++){
                enemies[j-1] = enemies[j];
            }
            enemyCounter--;
        }
    }
}

void Enemies::updateEnemies(){
    this->checkAlives();
    
    timer++;
    if (timer == 100){
        this->spawnNewEnemy();
        timer = 0;
    }
}

Enemies::~Enemies(){
    for (int i = 0; i < enemyCounter; i++){
        delete[] enemies[i];
    }
}

