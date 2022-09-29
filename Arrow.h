#ifndef ARROW_H
#define ARROW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"

extern Player P1;
extern double xpos, ypos;
extern sf::RenderWindow window;

class Arrow{
    public:
    double* arrowCoordinates = new double[2];
    int damage;
    double* targetCoordinates = new double[2];
    double* speedVector = new double[2];
    sf::RectangleShape ArrowShape;
    int counter;
    
    Arrow();
    Arrow(double xspawn, double yspawn);
    bool EnemycollisionDetection();
    bool outOfBounds();
    bool UpdatePosition();
    void DrawArrows();
};
#endif //ARROW_H