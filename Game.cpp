// g++ Game.cpp Player.cpp Enemy.cpp Archer.cpp Arrow.cpp Enemies.cpp
// PowerUp.cpp SpinningBlade.cpp -lsfml-graphics -lsfml-window -lsfml-system

#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

#include "Archer.h"
#include "Arrow.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Player.h"
#include "SpinningBlade.h"

double xpos, ypos;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
Player P1(width / 2, height / 2, width, height, &window);

int main() {
  window.setFramerateLimit(120);
  sf::Texture mapImage;
  sf::Sprite backgroundMap;
  if (!mapImage.loadFromFile("backgroundMap.png")) {
    std::cout << "Could not load \"backgroundMap.png\"!" << std::endl;
  }
  backgroundMap.scale(1, 1);
  backgroundMap.setTexture(mapImage);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    backgroundMap.setOrigin(-512, -512);
    Enemies a1;
    SpinningBlade b1(0);
    while (P1.isAlive() && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }
      window.draw(backgroundMap);
      P1.DrawPlayer(&window);
      a1.updateEnemies();

      b1.updateAbility();
      b1.hitEnemy(&a1);
      window.display();
      window.clear(sf::Color::White);
    }

    window.clear(sf::Color::Black);
    sf::Text deathText;
    sf::Font deathFont;
    deathFont.loadFromFile("Yagora.ttf");
    deathText.setFont(deathFont);
    deathText.setCharacterSize(80);
    deathText.setString("   YOU DIED!\n\nPRESS ENTER");
    deathText.setPosition(sf::Vector2f(-width / 10, -height / 10));
    window.draw(deathText);
    window.display();
    bool waiting = 1;
    while (waiting == 1 && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        waiting = 0;
        P1.resetPlayer();
      }
    }
  }
  return 0;
}