// g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Beast.cpp
// Arrow.cpp Enemies.cpp PowerUp.cpp SpinningBlade.cpp ObstacleGenerator.cpp
// Obstacle.cpp ExpBall.cpp ExpSpawner.cpp-lsfml-graphics -lsfml-window
// -lsfml-system

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
#include "ResourceManager.h"
#include "SpinningBlade.h"
#include "UIManager.h"

double xpos, ypos;
std ::string gameState;

double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");

ObstacleGenerator og;
ExpSpawner E1;
ResourceManager resourceManager;
Player P1(0, 0, width / 2, height / 2, &window);
const sf::Time TimePerFrame = sf::seconds(1.f / 90.f);
bool showQuitGameDialouge;
bool showSettingsPage;
bool isGameChanging;

void gameLoop() {
  SpinningBlade b1(0);
  UIManager UI(0, 0, width / 2, height / 2, &window);
  sf::Clock clk;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Sprite backgroundMap, mapExtras;
  backgroundMap.scale(2, 2);
  backgroundMap.setTexture(resourceManager.mapImage);
  backgroundMap.setPosition(-3586, -3616);
  mapExtras.scale(2, 2);
  mapExtras.setTexture(resourceManager.extrasImage);
  mapExtras.setPosition(-2048, -2048);
  window.setFramerateLimit(120);
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
    deathText.setFont(resourceManager.defaultFont);
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
  sf::Sprite playButton, loadButton, settingsButton, quitButton, background,
      menuTitle, dialougeBox, yesButton, noButton, settingsPage, exitButton;
  menuTitle.setTexture(resourceManager.menuTitleTex);
  background.setTexture(resourceManager.backgroundTex);
  playButton.setTexture(resourceManager.playButtonTex, true);
  loadButton.setTexture(resourceManager.loadButtonTex);
  settingsButton.setTexture(resourceManager.settingsButtonTex);
  quitButton.setTexture(resourceManager.quitButtonTex);

  dialougeBox.setTexture(resourceManager.dialougeBoxTex);
  dialougeBox.setScale(1, 1);
  dialougeBox.setPosition(-285, -75);
  yesButton.setTexture(resourceManager.yesButtonTex);
  yesButton.setScale(2, 2);
  yesButton.setPosition(-150, -10);
  noButton.setTexture(resourceManager.noButtonTex);
  noButton.setScale(2, 2);
  noButton.setPosition(0, -10);

  settingsPage.setTexture(resourceManager.settingsPageTex);
  settingsPage.setScale(3, 3);
  settingsPage.setPosition(-325, -215);
  exitButton.setScale(2, 2);
  exitButton.setPosition(-330, -220);
  exitButton.setTexture(resourceManager.quitButtonTex);

  background.setScale(6, 6);
  background.setPosition(-480, -270);
  menuTitle.setScale(6, 6);
  menuTitle.setPosition(-240, -190);
  playButton.setScale(6, 6);
  playButton.setPosition(-190, 20);
  loadButton.setScale(6, 6);
  loadButton.setPosition(-90, 20);
  settingsButton.setScale(6, 6);
  settingsButton.setPosition(10, 20);
  quitButton.setScale(6, 6);
  quitButton.setPosition(110, 20);

  if (abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) > 1100 &&
      abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) < 1330 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) >
          870 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) <
          1100) {
    playButton.setPosition(-196, 14);
    playButton.setTexture(resourceManager.playButtonSelectedTex, true);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      gameState = "gameLoop";
      isGameChanging = true;
    }
  } else if (abs(sf::Mouse::getPosition(window).x -
                 quitButton.getGlobalBounds().left) > 1750 &&
             abs(sf::Mouse::getPosition(window).x -
                 quitButton.getGlobalBounds().left) < 2000 &&
             abs(sf::Mouse::getPosition(window).y -
                 quitButton.getGlobalBounds().top) > 870 &&
             abs(sf::Mouse::getPosition(window).y -
                 quitButton.getGlobalBounds().top) < 1100) {
    quitButton.setPosition(104, 14);
    quitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      showQuitGameDialouge = true;
    }
  } else if (abs(sf::Mouse::getPosition(window).x -
                 playButton.getGlobalBounds().left) > 1725 &&
             abs(sf::Mouse::getPosition(window).x -
                 playButton.getGlobalBounds().left) < 1995 &&
             abs(sf::Mouse::getPosition(window).y -
                 playButton.getGlobalBounds().top) > 870 &&
             abs(sf::Mouse::getPosition(window).y -
                 playButton.getGlobalBounds().top) < 1100) {
    settingsButton.setPosition(4, 14);
    settingsButton.setTexture(resourceManager.settingsButtonSelectedTex, true);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      showSettingsPage = true;
    }

  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    showQuitGameDialouge = true;
  }

  window.draw(background);
  window.draw(menuTitle);
  window.draw(playButton);
  window.draw(loadButton);
  window.draw(settingsButton);
  window.draw(quitButton);

  if (showSettingsPage == true) {
    if (abs(sf::Mouse::getPosition(window).x -
            exitButton.getGlobalBounds().left) > 800 &&
        abs(sf::Mouse::getPosition(window).x -
            exitButton.getGlobalBounds().left) < 900 &&
        abs(sf::Mouse::getPosition(window).y -
            exitButton.getGlobalBounds().top) > 350 &&
        abs(sf::Mouse::getPosition(window).y -
            exitButton.getGlobalBounds().top) < 450) {
      exitButton.setPosition(-332, -222);
      exitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        showSettingsPage = false;
      }
    }
    window.draw(settingsPage);
    window.draw(exitButton);
  }

  if (showQuitGameDialouge == true) {
    if (abs(sf::Mouse::getPosition(window).x -
            yesButton.getGlobalBounds().left) > 1175 &&
        abs(sf::Mouse::getPosition(window).x -
            yesButton.getGlobalBounds().left) < 1580 &&
        abs(sf::Mouse::getPosition(window).y -
            yesButton.getGlobalBounds().top) > 780 &&
        abs(sf::Mouse::getPosition(window).y -
            yesButton.getGlobalBounds().top) < 980) {
      yesButton.setPosition(-150, -9);
      yesButton.setTexture(resourceManager.yesButtonSelectedTex, true);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        window.close();
      }
    }
    if (abs(sf::Mouse::getPosition(window).x -
            noButton.getGlobalBounds().left) > 1500 &&
        abs(sf::Mouse::getPosition(window).x -
            noButton.getGlobalBounds().left) < 1895 &&
        abs(sf::Mouse::getPosition(window).y - noButton.getGlobalBounds().top) >
            780 &&
        abs(sf::Mouse::getPosition(window).y - noButton.getGlobalBounds().top) <
            980) {
      noButton.setPosition(0, -9);
      noButton.setTexture(resourceManager.noButtonSelectedTex, true);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        showQuitGameDialouge = false;
      }
    }
    window.draw(dialougeBox);
    window.draw(yesButton);
    window.draw(noButton);
  }

  window.setFramerateLimit(120);
  window.display();
}

int main() {
  showQuitGameDialouge = false;
  showSettingsPage = false;
  isGameChanging = true;

  while (window.isOpen()) {
    sf::Event event;
    gameState = "mainMenu";
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    if (gameState == "mainMenu") {
      if (isGameChanging) {
        resourceManager.loadMainMenu();
        isGameChanging = false;
      }
      mainMenu();
    }
    if (gameState == "gameLoop") {
      if (isGameChanging) {
        resourceManager.loadGame();
        isGameChanging = false;
      }
      gameLoop();
    }
  }

  return 0;
}