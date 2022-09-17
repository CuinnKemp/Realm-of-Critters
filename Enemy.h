#ifndef ENEMY_H
#define ENEMY_H
class Enemy{
    public:
    double* coordinates = new double[2];
    int health;
    sf::RectangleShape sprite;
    virtual bool updateEnemy();
};
#endif //ENEMY_H