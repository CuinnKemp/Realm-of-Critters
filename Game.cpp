//g++ Game.cpp Player.cpp Enemy.cpp Archer.cpp Arrow.cpp Enemies.cpp PowerUp.cpp SpinningBlade.cpp -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

#include "Player.h"
#include "Enemy.h"
#include "Archer.h"
#include "Arrow.h"
#include "Enemies.h"

#include "SpinningBlade.h"

double xpos, ypos;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");

Player P1(width/2,height/2, width, height, &window);

SpinningBlade b1(0);

int main(){
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Enemies a1;
        while (P1.isAlive() && window.isOpen()){
            sf::Event eventInner;
            while (window.pollEvent(eventInner))
            {
                if (eventInner.type == sf::Event::Closed)
                    window.close();
            }
            P1.DrawPlayer(&window);

            a1.updateEnemies();

            b1.updateAbility();
            b1.hitEnemy(&a1);
            
            window.display();
            window.clear(sf::Color::Green);
            }
        
        window.clear(sf::Color::Black);
        sf::Text deathText;
        sf::Font deathFont;
        deathFont.loadFromFile("Yagora.ttf");
        deathText.setFont(deathFont);
        deathText.setCharacterSize(80);
        deathText.setString("   YOU DIED!\n\nPRESS ENTER");
        deathText.setPosition(sf::Vector2f(-width/5,-height/4));
        window.draw(deathText);
        window.display();
        bool waiting = 1;
        while (waiting == 1 && window.isOpen()){
            sf::Event eventInner;
            while (window.pollEvent(eventInner))
            {
                if (eventInner.type == sf::Event::Closed)
                    window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                waiting = 0;
                P1.resetPlayer();
            }
        }
    }
    return 0;
}