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

#include "ExpBall.h"
#include "ExpContainer.h"
#include "ExpSpawner.h"
#include "Player.h"
double xpos, ypos;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
Player P1(0, 0, width, height, &window);
ExpSpawner E1;

int main() {
  window.setFramerateLimit(120);
  sf::Texture mapImage;
  sf::Texture extrasImage;
  sf::Sprite backgroundMap;
  sf::Sprite mapExtras;

  if (!mapImage.loadFromFile("backgroundMap.png")) {
    std::cout << "Could not load \"backgroundMap.png\"!" << std::endl;
  }
  if (!extrasImage.loadFromFile("mapExtras.png")) {
    std::cout << "Could not load \"mapExtras.png\"!" << std::endl;
  }
  backgroundMap.scale(2, 2);
  backgroundMap.setTexture(mapImage);
  backgroundMap.setPosition(-3586, -3616);
  mapExtras.scale(2, 2);
  mapExtras.setTexture(extrasImage);
  mapExtras.setPosition(-2048, -2048);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    backgroundMap.setOrigin(-512, -512);

    for (int i = 0; i < 25; i++) {
      E1.spawnNewExp();
    }
    while (P1.isAlive() && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }
      window.draw(backgroundMap);
      P1.DrawPlayer(&window);
      window.draw(mapExtras);
      E1.updateExps();
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