// g++ Game.cpp Player.cpp Enemy.cpp Enemies.cpp Beast.cpp Obstacle.cpp
// ObstacleGenerator.cpp Arrow.cpp PowerUp.cpp SpinningBlade.cpp ExpBall.cpp
// ExpContainer.cpp ExpSpawner.cpp  -lsfml-graphics -lsfml-window -lsfml-system

#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "Beast.h"
#include "Enemies.h"
#include "Enemy.h"
#include "ExpBall.h"
#include "ExpContainer.h"
#include "ExpSpawner.h"
#include "Obstacle.h"
#include "ObstacleGenerator.h"
#include "Player.h"
#include "SpinningBlade.h"
#include "UIManager.h"

double xpos, ypos;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
Player P1(0, 0, width / 2, height / 2, &window);
UIManager UI(0, 0, width / 2, height / 2, &window);

SpinningBlade b1(0);
ObstacleGenerator og;
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

    for (int i = 0; i <= 237; i++) {
      og.spawnNewObstacle();
    }
    for (int i = 0; i < 25; i++) {
      E1.spawnNewExp();
    }
    Enemies a1;
    // pArrow pA(&a1);
    while (P1.isAlive() && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }
      window.draw(backgroundMap);

      og.updateObstacles();

      for (int i = 0; i < og.obstacleCounter; i++) {
        float playerX = P1.sprite.getPosition().x + 20;
        float playerY = P1.sprite.getPosition().y + 20;
        float obstacleX = og.obstacles[i]->sprite.getPosition().x - 1888;
        float obstacleY = og.obstacles[i]->sprite.getPosition().y - 1888;
        if (abs(playerX - obstacleX) <= 50 && abs(playerY - obstacleY) <= 50) {
          xpos = P1.oldXpos;
          ypos = P1.oldYpos;
        }
      }

      window.draw(mapExtras);
      a1.updateEnemies();
      // pA.updateAbility(&a1, &pA);
      P1.DrawPlayer(&window);
      b1.updateAbility();
      b1.hitEnemy(&a1);
      E1.updateExps();
      UI.DrawUIManager(&window);
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
        UI.resetUI();
        E1.deleteExpBalls();
      }
    }
  }
  return 0;
}