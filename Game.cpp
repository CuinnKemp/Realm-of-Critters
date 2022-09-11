#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

static double xpos, ypos;

class Player{
    public:
    double gravity = 5;
    double fallTime = 0;
    double movSpeed = 10;
    double jumpSpeed = 50;

    //collision detections
    int floorTouch = 0;
    int roofTouch = 0;
    int leftTouch = 0;
    int rightTouch = 0;

    sf::RectangleShape sprite;
    
    Player(){
        xpos = 0;
        ypos = 0;
        sprite.setSize(sf::Vector2f(50,50));
        sprite.setFillColor(sf::Color(255,255,255));
    }

    Player(double Pxpos, double Pypos, double width, double height){
        xpos = Pxpos;
        ypos = Pypos;
        sprite.setPosition(sf::Vector2f(xpos-25,ypos-25));
        sprite.setSize(sf::Vector2f(50,50));
        sprite.setFillColor(sf::Color(255,255,255));
    }


    void moveRight(){
        xpos = xpos + movSpeed;
        
    }
    void moveLeft(){
        xpos = xpos - movSpeed;
        
    }

    void moveUp(){
        ypos = ypos - movSpeed;
    }
    
    void moveDown(){
        ypos = ypos + movSpeed;
    }
    
    void getPosition(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->moveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            this->moveDown();
        }

    }

    void DrawPlayer(sf::RenderWindow* window){
        this->getPosition();
        sprite.setPosition(sf::Vector2f(xpos-25,ypos-25));
        window->draw(sprite);
    }

    };
    
    int main(){
        int direction = 0;

    double width = sf::VideoMode::getDesktopMode().width;
    double height = sf::VideoMode::getDesktopMode().height;
    Player P1(width/2,height/2, width, height);
    sf::RenderWindow window(sf::VideoMode(width, height), "GAME");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color(0,0,0));
        window.draw(rectangle);
        


        P1.DrawPlayer(&window);
        
        std::cout << xpos << "  " << ypos << std::endl;
        
        window.display();
    }

    return 0;
}
