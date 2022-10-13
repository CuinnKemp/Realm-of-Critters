// g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp
// Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp
// PowerUp.cpp SpinningBlade.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp
// PlayerArrow.cpp PlayerArrowSpawner.cpp -lsfml-graphics -lsfml-window
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
#include "PlayerArrow.h"
#include "PlayerArrowSpawner.h"
#include "ResourceManager.h"
#include "Slime.h"
#include "SpinningBlade.h"
#include "UIManager.h"

// coordinates for the player
double xpos, ypos;
std ::string gameState;

// Window and Desktop Settings for the Viewport
double width = sf::VideoMode::getDesktopMode().width;
double height = sf::VideoMode::getDesktopMode().height;
sf::RenderWindow window(sf::VideoMode(width, height), "GAME");

// Initialising Objects
ObstacleGenerator og;
ExpSpawner E1;
ResourceManager resourceManager;
Player P1(0, 0, width / 2, height / 2, &window);
const sf::Time TimePerFrame = sf::seconds(1.f / 90.f);
bool showQuitGameDialouge;
bool showSettingsPage;
bool isGameChanging;
bool waiting;

void gameLoop() {
  // Initialising Objects for Main Game
  SpinningBlade b1(0);
  sf::Clock clk;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Sprite backgroundMap, mapExtras;
  UIManager UI(0, 0, width / 2, height / 2, &window);

  // Setings for Map and Extras
  backgroundMap.scale(2, 2);
  backgroundMap.setTexture(resourceManager.mapImage);
  backgroundMap.setPosition(-3586, -3616);

  mapExtras.scale(2, 2);
  mapExtras.setTexture(resourceManager.extrasImage);
  mapExtras.setPosition(-2048, -2048);

  if (isGameChanging) {
    P1.resetPlayer();
    isGameChanging = false;
  }

  // Main game Loop
  while (window.isOpen()) {
    // Initialising Enemies & Player Arrows
    Enemies a1;
    PlayerArrowSpawner pA(&a1);

    // While the Window is open
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    // Sets Background Map, Spawns Obstacles and EXP
    backgroundMap.setOrigin(-512, -512);

    for (int i = 0; i <= 237; i++) {
      og.spawnNewObstacle();
    }
    for (int i = 0; i < 25; i++) {
      E1.spawnNewExp();
    }

    // WHile the Player is Alive and the window is still open
    while (P1.isAlive() && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }

      sf::Time dt = clk.restart();
      timeSinceLastUpdate += dt;
      while (timeSinceLastUpdate > TimePerFrame) {
        timeSinceLastUpdate -= TimePerFrame;

        // Draws Background Map
        window.draw(backgroundMap);
        og.updateObstacles();

        // Adding Collision to Objects
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

        // Drawing Foliage on the Map
        window.draw(mapExtras);

        // update command for enemies
        a1.updateEnemies();

        // Spawning Player Arrows, firing them at enemies
        pA.fireCounter = pA.fireCounter + 2;
        // Temp test to see how fire rate affects gameplay
        if (pA.fireCounter >= (1 / P1.clock.getElapsedTime().asSeconds() +
                               (100 - P1.clock.getElapsedTime().asSeconds()))) {
          pA.attack();
          pA.fireCounter = 0;
        }
        pA.drawArrows();

        // Drawing Player on the map
        P1.DrawPlayer(&window);

        // update command for Abilities
        b1.updateAbility();
        b1.hitEnemy(&a1);

        // Updating Exp, UI and Map
        E1.updateExps();
        UI.DrawUIManager(&window);
        window.display();
        window.clear(sf::Color::White);
      }
    }

    // Death Screen if Player runs out of health
    window.clear(sf::Color::Black);
    sf::Text deathText;
    deathText.setFont(resourceManager.defaultFont);
    deathText.setCharacterSize(80);
    deathText.setString("   YOU DIED!\n\nPRESS ENTER");
    deathText.setPosition(sf::Vector2f(-width / 10, -height / 10));
    window.draw(deathText);
    window.display();

    // Waiting for Player Response on Death Screen
    waiting = true;
    while (waiting == true && window.isOpen()) {
      sf::Event eventInner;
      while (window.pollEvent(eventInner)) {
        if (eventInner.type == sf::Event::Closed) window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        waiting = 0;
        P1.resetPlayer();
        UI.resetUI();
        E1.deleteExpBalls();
        a1.deleteEnemies();
      }
    }
  }
}

void mainMenu() {
  // Setings for Main Menu UI
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

  // std::cout << window.getSize().x / 3024 << std::endl;

  // Checks if mouse is hovering over the play button
  if (abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) > 1100 &&
      abs(sf::Mouse::getPosition(window).x -
          playButton.getGlobalBounds().left) < 1330 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) >
          870 &&
      abs(sf::Mouse::getPosition(window).y - playButton.getGlobalBounds().top) <
          1100) {
    // Sets selected texture for the play button
    playButton.setPosition(-196, 14);
    playButton.setTexture(resourceManager.playButtonSelectedTex, true);

    // Checks if the play button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      gameState = "gameLoop";
      isGameChanging = true;
    }
  }
  // Checks if mouse is hovering over the quit button
  else if (abs(sf::Mouse::getPosition(window).x -
               quitButton.getGlobalBounds().left) > 1750 &&
           abs(sf::Mouse::getPosition(window).x -
               quitButton.getGlobalBounds().left) < 2000 &&
           abs(sf::Mouse::getPosition(window).y -
               quitButton.getGlobalBounds().top) > 870 &&
           abs(sf::Mouse::getPosition(window).y -
               quitButton.getGlobalBounds().top) < 1100) {
    // Sets selected texture for the quit button
    quitButton.setPosition(104, 14);
    quitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
    // Checks if the quit button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      showQuitGameDialouge = true;
    }
  }
  // Checks if mouse is hovering over the settings button
  else if (abs(sf::Mouse::getPosition(window).x -
               playButton.getGlobalBounds().left) > 1725 &&
           abs(sf::Mouse::getPosition(window).x -
               playButton.getGlobalBounds().left) < 1995 &&
           abs(sf::Mouse::getPosition(window).y -
               playButton.getGlobalBounds().top) > 870 &&
           abs(sf::Mouse::getPosition(window).y -
               playButton.getGlobalBounds().top) < 1100) {
    // Sets selected texture for the settings button
    settingsButton.setPosition(4, 14);
    settingsButton.setTexture(resourceManager.settingsButtonSelectedTex, true);
    // Checks if the settings button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      showSettingsPage = true;
    }

  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    showQuitGameDialouge = true;
  }

  // Draws UI elements
  window.draw(background);
  window.draw(menuTitle);
  window.draw(playButton);
  window.draw(loadButton);
  window.draw(settingsButton);
  window.draw(quitButton);

  // Checks if the settings button has been clicked
  if (showSettingsPage == true) {
    // Checks if mouse is hovering over the exit button
    if (abs(sf::Mouse::getPosition(window).x -
            exitButton.getGlobalBounds().left) > 800 &&
        abs(sf::Mouse::getPosition(window).x -
            exitButton.getGlobalBounds().left) < 900 &&
        abs(sf::Mouse::getPosition(window).y -
            exitButton.getGlobalBounds().top) > 350 &&
        abs(sf::Mouse::getPosition(window).y -
            exitButton.getGlobalBounds().top) < 450) {
      // Sets selected texture for the exit button
      exitButton.setPosition(-332, -222);
      exitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
      // Checks if the exit button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        showSettingsPage = false;
      }
    }
    // Draws settings page UI elements
    window.draw(settingsPage);
    window.draw(exitButton);
  }

  // Checks if the quit button has been clicked
  if (showQuitGameDialouge == true) {
    // Checks if mouse is hovering over the yes button
    if (abs(sf::Mouse::getPosition(window).x -
            yesButton.getGlobalBounds().left) > 1175 &&
        abs(sf::Mouse::getPosition(window).x -
            yesButton.getGlobalBounds().left) < 1580 &&
        abs(sf::Mouse::getPosition(window).y -
            yesButton.getGlobalBounds().top) > 780 &&
        abs(sf::Mouse::getPosition(window).y -
            yesButton.getGlobalBounds().top) < 980) {
      // Sets selected texture for the yes button
      yesButton.setPosition(-150, -9);
      yesButton.setTexture(resourceManager.yesButtonSelectedTex, true);
      // Checks if the yes button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        window.close();
      }
    }
    // Checks if mouse is hovering over the yes button
    if (abs(sf::Mouse::getPosition(window).x -
            noButton.getGlobalBounds().left) > 1500 &&
        abs(sf::Mouse::getPosition(window).x -
            noButton.getGlobalBounds().left) < 1895 &&
        abs(sf::Mouse::getPosition(window).y - noButton.getGlobalBounds().top) >
            780 &&
        abs(sf::Mouse::getPosition(window).y - noButton.getGlobalBounds().top) <
            980) {
      // Sets selected texture for the yes button
      noButton.setPosition(0, -9);
      noButton.setTexture(resourceManager.noButtonSelectedTex, true);
      // Checks if the no button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        showQuitGameDialouge = false;
      }
    }
    // Draws quit game dialouge UI elements
    window.draw(dialougeBox);
    window.draw(yesButton);
    window.draw(noButton);
  }

  window.setFramerateLimit(120);
  window.display();
}

int main() {
  // Sets inital game states
  showQuitGameDialouge = false;
  showSettingsPage = false;
  isGameChanging = true;
  waiting = false;
  gameState = "mainMenu";

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      /*       if (event.type == sf::Event::Resized) {
              sf::FloatRect view(1920, -1080, event.size.width,
         event.size.height); window.setView(sf::View(view));
            } */
    }
    // Checks if on Main Menu Screen
    if (gameState == "mainMenu") {
      // Checks if the game state changed
      if (isGameChanging) {
        // Load assets for main menu
        resourceManager.loadMainMenu();
        isGameChanging = false;
      }
      mainMenu();
    }
    // Checks if on Main Game Screen
    if (gameState == "gameLoop") {
      // Checks if the game state changed
      if (isGameChanging) {
        // Load assets for main game
        resourceManager.loadGame();
        isGameChanging = false;
      }
      gameLoop();
    }
  }

  return 0;
}