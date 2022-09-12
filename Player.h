#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

class Player{
    public:
    double movSpeed;
    sf::RectangleShape sprite;
    sf::RenderWindow* window;
    sf::View camera;
    sf::Texture standing;
    sf::Texture running1;
    sf::Texture running2;

    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;
    double health;
    int animationCount;
    
    Player(double Pxpos, double Pypos, double width, double height, sf::RenderWindow* window);
    
    void resetPlayer();

    void moveRight();

    void moveLeft();

    void moveUp();
    
    void moveDown();
    
    void getPosition();

    bool isAlive();

    void DrawPlayer(sf::RenderWindow* window);
};

#endif //PLAYER_H