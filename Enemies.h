#ifndef ENEMIES_H
#define ENEMIES_H

#include "Enemy.h"
#include "Archer.h"

class Enemies{
    public:
    int enemyCounter;
    Enemy** enemies;
    int spawnRate;
    int timer;

    Enemies();
    
    ~Enemies();
    
    void spawnNewEnemy();

    void checkAlives();
    
    void updateEnemies();
};
#endif //ENEMIES_H