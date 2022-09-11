#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

static double xpos, ypos;

class Player{
    public:
    double movSpeed;
    sf::RectangleShape sprite;
    sf::RenderWindow* window;
    sf::View camera;
    sf::Texture texture;
    
    Player(double Pxpos, double Pypos, double width, double height, sf::RenderWindow* window){
        xpos = Pxpos;
        ypos = Pypos;
        this->movSpeed = 5;
        this->window = window;
        this->sprite.setPosition(sf::Vector2f(xpos-20,ypos-20));
        this->sprite.setSize(sf::Vector2f(40,40));
        // texture.loadFromFile("player.gif");
        // texture.setSmooth(true);
        // sprite.setTexture(&texture);
        camera.setCenter(0,0);
        camera.setSize(width, height);
        window->setView(camera);
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
        sprite.setPosition(sf::Vector2f(xpos-20,ypos-20));
        window->draw(sprite);
        camera.setCenter(sprite.getPosition());
        window->setView(camera);
    }

    };
    
    int main(){
        int direction = 0;

    double width = sf::VideoMode::getDesktopMode().width;
    double height = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(width, height), "GAME");

    Player P1(width/2,height/2, width, height, &window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        


        P1.DrawPlayer(&window);
        
        window.display();
        window.clear(sf::Color::Green);
    }

    return 0;
}
