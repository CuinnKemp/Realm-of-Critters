//g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp SpinningBlade.cpp SpinningBladeSpawner.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include <stdlib.h>
#include <unistd.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

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
#include "SpinningBladeSpawner.h"
#include "GameLoader.h"
using namespace std;

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
Enemies enemies;

//Abilities
PlayerArrowSpawner pArrows(&enemies);
SpinningBladeSpawner sBlades(&enemies);

const sf::Time TimePerFrame = sf::seconds(1.f / 90.f);
bool showQuitGameDialouge;
bool showSettingsPage;
bool isGameChanging;
bool waiting;
bool shouldLoadGame, isButtonClicked;
float musicVolume, sfxVolume;
sf::Music menuMusic, mainMusic, deathMusic;
sf::SoundBuffer buttonHovering, bigButtonHovering, buttonClicked, yesButtonSB,
    noButtonSB, arrowSB, gameOverSB;
sf::Sound buttonSound, arrowSound, gameOverSound;
sf::Sprite musicLevel, sfxLevel;

GameLoader G1;

int main() {
  // Sets inital game states
  showQuitGameDialouge = false;
  showSettingsPage = false;
  isGameChanging = true;
  waiting = false;
  shouldLoadGame = false;
  gameState = "mainMenu";
  musicVolume = 100;
  sfxVolume = 100;

  menuMusic.openFromFile("Music/1.ogg");
  mainMusic.openFromFile("Music/17.ogg");
  deathMusic.openFromFile("Music/15.ogg");
  menuMusic.setLoop(true);
  mainMusic.setLoop(true);
  deathMusic.setLoop(true);

  buttonHovering.loadFromFile("Sounds/Menu1.wav");
  bigButtonHovering.loadFromFile("Sounds/Menu1.wav");
  buttonClicked.loadFromFile("Sounds/Menu9.wav");
  yesButtonSB.loadFromFile("Sounds/Accept2.wav");
  noButtonSB.loadFromFile("Sounds/Accept.wav");

  arrowSB.loadFromFile("Sounds/Hit5.wav");
  arrowSound.setBuffer(arrowSB);
  arrowSound.setVolume(50.f);

  gameOverSB.loadFromFile("Sounds/GameOver.wav");
  gameOverSound.setBuffer(gameOverSB);

  musicLevel.setScale(3, 3);
  sfxLevel.setScale(3, 3);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) showQuitGameDialouge = true;
    }
    mainMusic.setVolume(musicVolume);
    deathMusic.setVolume(musicVolume);
    menuMusic.setVolume(musicVolume);
    buttonSound.setVolume(sfxVolume);
    arrowSound.setVolume(sfxVolume);
    gameOverSound.setVolume(sfxVolume);

    // Checks if on Main Menu Screen
    if (gameState == "mainMenu") {
      // Checks if the game state changed
      if (isGameChanging) {
        // Load assets for main menu
        resourceManager.loadMainMenu();
        isGameChanging = false;
        mainMusic.stop();
        deathMusic.stop();
        menuMusic.play();
      }
      G1.mainMenu();
    }
    // Checks if on Main Game Screen
    if (gameState == "gameLoop") {
      // Checks if the game state changed
      if (isGameChanging) {
        // Load assets for main game
        resourceManager.loadGame();
        isGameChanging = false;
        menuMusic.stop();
        deathMusic.stop();
        mainMusic.play();
      }
      G1.gameLoop();
      gameState = "mainMenu";
    }
  }

  return 0;
}