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
std ::string gameState;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
Player P1(0, 0, width / 2, height / 2, &window);
UIManager UI(0, 0, width / 2, height / 2, &window);

SpinningBlade b1(0);
ObstacleGenerator og;
ExpSpawner E1;
const sf::Time TimePerFrame = sf::seconds(1.f / 90.f);

void gameLoop() {
  sf::Clock clk;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  window.setFramerateLimit(120);
  // window.setVerticalSyncEnabled(true);
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
      sf::Time dt = clk.restart();
      timeSinceLastUpdate += dt;
      while (timeSinceLastUpdate > TimePerFrame) {
        timeSinceLastUpdate -= TimePerFrame;

        window.draw(backgroundMap);

        og.updateObstacles();

        for (int i = 0; i < og.obstacleCounter; i++) {
          float playerX = P1.sprite.getPosition().x + 20;
          float playerY = P1.sprite.getPosition().y + 20;
          float obstacleX = og.obstacles[i]->sprite.getPosition().x - 1888;
          float obstacleY = og.obstacles[i]->sprite.getPosition().y - 1888;
          if (abs(playerX - obstacleX) <= 50 &&
              abs(playerY - obstacleY) <= 50) {
            xpos = P1.oldXpos;
            ypos = P1.oldYpos;
          }
        }

        window.draw(mapExtras);
        a1.updateEnemies();
        P1.DrawPlayer(&window);
        b1.updateAbility();
        b1.hitEnemy(&a1);
        E1.updateExps();
        UI.DrawUIManager(&window);
        window.display();
      }
    }

    window.clear(sf::Color::Black);
    sf::Text deathText;
    sf::Font deathFont;
    deathFont.loadFromFile("OfMiceAndCats.ttf");
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
}

void mainMenu() {
  sf::Sprite background, menuTitle, playButton, loadButton, settingsButton,
      quitButton;
  sf::Texture backgroundTex, menuTitleTex, playButtonTex, loadButtonTex,
      settingsButtonTex, quitButtonTex, playButtonSelectedTex,
      loadButtonSelectedTex;

  backgroundTex.loadFromFile("UI/MainMenuBackground.png");
  menuTitleTex.loadFromFile("UI/MenuTitle.png");
  playButtonTex.loadFromFile("UI/PlayButton.png");
  loadButtonTex.loadFromFile("UI/LoadButton.png");
  settingsButtonTex.loadFromFile("UI/SettingsButton.png");
  quitButtonTex.loadFromFile("UI/QuitButton.png");
  playButtonSelectedTex.loadFromFile("UI/PlayButtonSelected.png");
  loadButtonSelectedTex.loadFromFile("UI/LoadButtonSelected.png");

  menuTitle.setTexture(menuTitleTex);
  background.setTexture(backgroundTex);
  playButton.setTexture(playButtonTex, true);
  loadButton.setTexture(loadButtonTex);
  settingsButton.setTexture(settingsButtonTex);
  quitButton.setTexture(quitButtonTex);

  background.setScale(6, 6);
  background.setPosition(-480, -270);
  menuTitle.setScale(6, 6);
  menuTitle.setPosition(-240, -190);
  playButton.setScale(6, 6);
  playButton.setPosition(-190, 20);
  loadButton.setScale(6, 6);
  loadButton.setPosition(-90, 20);
  settingsButton.setScale(6 * 13 / 15, 6 * 13 / 15);
  settingsButton.setPosition(10, 20);
  quitButton.setScale(6 * 13 / 15, 6 * 13 / 15);
  quitButton.setPosition(110, 20);

  sf::Event playButtonEvent;
  if (abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) > 1100 &&
      abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) < 1330 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) >
          870 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) <
          1100) {
    playButton.setPosition(-196, 14);
    playButton.setTexture(playButtonSelectedTex, true);
    std::cout << "Pressed" << std::endl;
  }

  /* if (sf::Mouse::getPosition(window).x >
          playButton.getGlobalBounds().left &&
      sf::Mouse::getPosition(window).x <
          playButton.getGlobalBounds().left +
              playButton.getGlobalBounds().width &&
      sf::Mouse::getPosition().y > playButton.getGlobalBounds().top &&
      sf::Mouse::getPosition(window).y <
          (playButton.getGlobalBounds().top +
           playButton.getGlobalBounds().height))
    ;
  { playButton.setTexture(playButtonSelectedTex); } */

  window.draw(background);
  window.draw(menuTitle);
  window.draw(playButton);
  window.draw(loadButton);
  window.draw(settingsButton);
  window.draw(quitButton);
  window.setFramerateLimit(120);
  window.display();
}

int main() {
  while (window.isOpen()) {
    sf::Event event;
    gameState = "mainMenu";
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    if (gameState == "mainMenu") {
      mainMenu();
    }
    if (gameState == "gameLoop") {
      gameLoop();
    }
  }

  return 0;
}