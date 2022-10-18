// g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp
// Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp
// SpinningBlade.cpp SpinningBladeSpawner.cpp ExpBall.cpp ExpContainer.cpp
// ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp -lsfml-graphics
// -lsfml-window -lsfml-system

#include "GameLoader.h"

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
#include "SpinningBladeSpawner.h"
#include "UIManager.h"
using namespace std;

// coordinates for the player
extern double xpos, ypos;
extern std ::string gameState;

// Window and Desktop Settings for the Viewport
extern double width;
extern double height;
extern sf::RenderWindow window;

// Initialising Objects
extern ObstacleGenerator og;
extern ExpSpawner E1;
extern ResourceManager resourceManager;
extern Player P1;
extern Enemies enemies;

// Abilities
extern PlayerArrowSpawner pArrows;
extern SpinningBladeSpawner sBlades;

extern const sf::Time TimePerFrame;
extern bool showQuitGameDialouge;
extern bool showSettingsPage;
extern bool isGameChanging;
extern bool waiting;
extern bool shouldLoadGame, isButtonClicked, playSFX;
extern float musicVolume, sfxVolume;
extern sf::Music menuMusic, mainMusic, deathMusic;
extern sf::SoundBuffer buttonHovering, bigButtonHovering, buttonClicked,
    yesButtonSB, noButtonSB, arrowSB, gameOverSB;
extern sf::Sound buttonSound, arrowSound, gameOverSound;
extern sf::Sprite musicLevel, sfxLevel;

// Saves game stats to a file
int GameLoader::saveGame(int health, int level, int currentExp, float time,
                         int pArrowLvl, int sBladeLvl) {
  ofstream saveFile("saveGame.save");
  if (saveFile.is_open()) {
    saveFile << health << " " << level << " " << currentExp << " " << time
             << " " << pArrowLvl << " " << sBladeLvl;
    saveFile.close();
  } else {
    return 0;
  }
  return 1;
}

// Loads game stats from a file
int GameLoader::loadGame() {
  P1.resetPlayer();
  float number;
  string line;
  ifstream saveFile("saveGame.save");
  if (saveFile.is_open()) {
    for (int i = 0; i < 6; i++) {
      saveFile >> number;
      if (i == 0) {
        if (number > 0 && number <= 100) {
          P1.health = number;
        } else {
          return 0;
        }
      } else if (i == 1) {
        P1.level = number;
      } else if (i == 2) {
        P1.currentExp = number;
      } else if (i == 3) {
        P1.savedTime = number;
      } else if (i == 4) {
        P1.pArrowLvl = number;
      } else if (i == 5) {
        P1.sBladeLvl = number;
      }
    }
    saveFile.close();
  } else {
    return 0;
  }
  return 1;
}

// Encrypts save game file to avoid cheating
void GameLoader::encryptSaveGame() {
  char fileName[30], ch;
  std::fstream fps, fpt;

  std::ofstream myfile;
  fps.open("saveGame.save", std::fstream::in);
  fpt.open("tmpSave.save", std::fstream::out);
  while (fps >> std::noskipws >> ch) {
    ch = ch + 100;
    fpt << ch;
  }
  remove("saveGame.save");
  rename("tmpSave.save", "saveGame.save");
  fps.close();
  fpt.close();
}

// Decrypts save game file to allow contents to be read
void GameLoader::decryptSaveGame() {
  char fileName[30], ch;
  std::fstream fps, fpt;

  std::ofstream myfile;
  fps.open("saveGame.save", std::fstream::in);
  fpt.open("tmpSave.save", std::fstream::out);
  while (fps >> std::noskipws >> ch) {
    fpt << ch;
  }
  fps.close();
  fpt.close();
  fps.open("saveGame.save", std::fstream::out);
  fpt.open("tmpSave.save", std::fstream::in);
  while (fpt >> std::noskipws >> ch) {
    ch = ch - 100;
    fps << ch;
  }
  remove("tmpSave.save");
  fps.close();
  fpt.close();
}

// Shows the quit game dialouge
void GameLoader::quitGameDialouge() {
  sf::Sprite dialougeBox, yesButton, noButton;
  dialougeBox.setTexture(resourceManager.dialougeBoxTex);
  dialougeBox.setScale(1, 1);

  yesButton.setTexture(resourceManager.yesButtonTex);
  yesButton.setScale(2, 2);

  noButton.setTexture(resourceManager.noButtonTex);
  noButton.setScale(2, 2);

  // If gameLoop is running, adjuts positions to remain in the centre of the
  // screen
  if (gameState == "gameLoop") {
    dialougeBox.setPosition(-285 + P1.camera.getCenter().x,
                            -75 + P1.camera.getCenter().y);
    yesButton.setPosition(-150 + P1.camera.getCenter().x,
                          -10 + P1.camera.getCenter().y);
    noButton.setPosition(0 + P1.camera.getCenter().x,
                         -10 + P1.camera.getCenter().y);
  } else {
    dialougeBox.setPosition(-285, -75);
    yesButton.setPosition(-150, -10);
    noButton.setPosition(0, -10);
  }

  // Checks if mouse is hovering over the yes button
  if (yesButton.getGlobalBounds().contains(sf::Vector2f(
          window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
    // Sets selected texture for the yes button
    yesButton.setPosition(-150 + P1.camera.getCenter().x,
                          -9 + P1.camera.getCenter().y);
    yesButton.setTexture(resourceManager.yesButtonSelectedTex, true);
    buttonSound.setBuffer(bigButtonHovering);
    // Checks if hovering button sound has not played
    if (playSFX) {
      buttonSound.play();
      playSFX = false;
    }
    // Checks if the yes button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (gameState == "gameLoop") {
        saveGame(P1.health, P1.level, P1.currentExp,
                 P1.clock.getElapsedTime().asSeconds() + P1.savedTime,
                 P1.pArrowLvl, P1.sBladeLvl);
        encryptSaveGame();
        mainMusic.stop();
      } else {
        menuMusic.stop();
      }
      buttonSound.setBuffer(yesButtonSB);
      buttonSound.play();
      sleep(1);
      window.close();
    }
  }
  // Checks if mouse is hovering over the yes button
  else if (noButton.getGlobalBounds().contains(sf::Vector2f(
               window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
    // Sets selected texture for the yes button
    noButton.setPosition(0 + P1.camera.getCenter().x,
                         -9 + P1.camera.getCenter().y);
    noButton.setTexture(resourceManager.noButtonSelectedTex, true);
    buttonSound.setBuffer(bigButtonHovering);
    // Checks if hovering button sound has not played
    if (playSFX) {
      buttonSound.play();
      playSFX = false;
    }
    // Checks if the no button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      buttonSound.setBuffer(noButtonSB);
      buttonSound.play();
      showQuitGameDialouge = false;
    }
  } else {
    playSFX = true;
  }
  // Draws quit game dialouge UI elements
  window.draw(dialougeBox);
  window.draw(yesButton);
  window.draw(noButton);
}

void GameLoader::gameLoop() {
  // Initialising Objects for Main Game
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

  // While the Window is open
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) showQuitGameDialouge = true;
  }
  // Sets Background Map, Spawns Obstacles and EXP
  backgroundMap.setOrigin(-512, -512);
  for (int i = 0; i <= 237; i++) {
    og.spawnNewObstacle();
  }
  for (int i = 0; i < 25; i++) {
    E1.spawnNewExp();
  }
  while (P1.isAlive() && window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) showQuitGameDialouge = true;
    }

    // Checks if decryptSaveGame() and loadGame() should be called
    if (shouldLoadGame) {
      decryptSaveGame();
      loadGame();
      shouldLoadGame = false;
    }

    // Draws Background Map
    window.draw(backgroundMap);
    og.updateObstacles();
    // Adding Collision to Objects
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
    // Drawing Foliage on the Map
    window.draw(mapExtras);
    // update command for enemies
    enemies.updateEnemies();
    // Spawning Player Arrows, firing them at enemies
    pArrows.fireCounter++;
    // Temp test to see how fire rate affects gameplay
    if (pArrows.fireCounter >= 100) {
      pArrows.attack();
      pArrows.fireCounter = 0;
    }
    pArrows.drawArrows();

    sBlades.updateAbility();
    // Drawing Player on the map
    P1.DrawPlayer(&window);

    // Updating Exp, UI and Map
    E1.updateExps();
    UI.DrawUIManager(&window);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      showQuitGameDialouge = true;
    }

    // Checks if the quit button has been clicked
    if (showQuitGameDialouge == true) {
      quitGameDialouge();
    }
    window.display();
    window.clear(sf::Color::White);
  }
  // Death Screen if Player runs out of health
  P1.resetPlayer();
  UI.resetUI();
  pArrows.resetSpawner();
  sBlades.resetSpawner();
  E1.deleteExpBalls();
  enemies.deleteEnemies();

  window.clear(sf::Color::Green);
  sf::Sprite background;
  background.setTexture(resourceManager.backgroundTex);
  background.setScale(6, 6);
  background.setPosition(-480, -270);
  sf::Text deathText1;
  sf::Text deathText2;
  deathText1.setString(sf::String("YOU DIED"));
  deathText2.setString(sf::String("PRESS ENTER"));

  deathText1.setFont(resourceManager.defaultFont);
  deathText2.setFont(resourceManager.defaultFont);
  deathText1.setCharacterSize(150);
  deathText2.setCharacterSize(75);
  deathText1.setPosition(-702 / 2, -1080 / 6);
  deathText2.setPosition(-533 / 2, 0);

  deathText1.setFillColor(sf::Color::Green);
  deathText2.setFillColor(sf::Color::Green);

  window.draw(background);
  window.draw(deathText1);
  window.draw(deathText2);
  window.display();
  gameOverSound.play();
  sleep(3);
  mainMusic.stop();
  deathMusic.play();
  // Waiting for Player Response on Death Screen
  waiting = true;
  while (waiting == true && window.isOpen()) {
    sf::Event eventInner;
    while (window.pollEvent(eventInner)) {
      if (eventInner.type == sf::Event::Closed) showQuitGameDialouge = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      waiting = false;
      deathMusic.stop();
      menuMusic.play();
      return;
    }
  }
}

void GameLoader::mainMenu() {
  // Setings for Main Menu UI
  sf::Sprite playButton, loadButton, settingsButton, quitButton, background,
      menuTitle, settingsPage, exitButton, musicLeftButton, musicRightButton,
      sfxLeftButton, sfxRightButton;
  sf::Clock clock;
  menuTitle.setTexture(resourceManager.menuTitleTex);
  background.setTexture(resourceManager.backgroundTex);
  playButton.setTexture(resourceManager.playButtonTex, true);
  loadButton.setTexture(resourceManager.loadButtonTex);
  settingsButton.setTexture(resourceManager.settingsButtonTex);
  quitButton.setTexture(resourceManager.quitButtonTex);

  musicLeftButton.setTexture(resourceManager.leftArrowTex);
  musicRightButton.setTexture(resourceManager.rightArrowTex);
  sfxLeftButton.setTexture(resourceManager.leftArrowTex);
  sfxRightButton.setTexture(resourceManager.rightArrowTex);

  musicLevel.setTexture(resourceManager.audioLevelTex);
  sfxLevel.setTexture(resourceManager.audioLevelTex);

  settingsPage.setTexture(resourceManager.settingsPageTex);
  settingsPage.setScale(3, 3);
  settingsPage.setPosition(-325, -215);
  exitButton.setScale(2, 2);
  exitButton.setPosition(-330, -220);
  exitButton.setTexture(resourceManager.quitButtonTex);
  musicLeftButton.setScale(3, 3);
  musicLeftButton.setPosition(60, -50);
  musicRightButton.setScale(3, 3);
  musicRightButton.setPosition(210, -50);
  sfxLeftButton.setScale(3, 3);
  sfxLeftButton.setPosition(60, 75);
  sfxRightButton.setScale(3, 3);
  sfxRightButton.setPosition(210, 75);
  musicLevel.setPosition(107, -44);
  sfxLevel.setPosition(107, 85);

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

  sf::Event menuEvent;

  if (!showSettingsPage && !showQuitGameDialouge) {
    // Checks if mouse is hovering over the play button
    if (playButton.getGlobalBounds().contains(sf::Vector2f(
            window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the play button
      playButton.setPosition(-196, 14);
      playButton.setTexture(resourceManager.playButtonSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }

      // Checks if the play button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        gameState = "gameLoop";
        isGameChanging = true;
      }
    }
    // Checks if mouse is hovering over the quit button
    else if (quitButton.getGlobalBounds().contains(sf::Vector2f(
                 window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the quit button
      quitButton.setPosition(104, 14);
      quitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the quit button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        showQuitGameDialouge = true;
      }
    }
    // Checks if mouse is hovering over the settings button
    else if (settingsButton.getGlobalBounds().contains(sf::Vector2f(
                 window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the settings button
      settingsButton.setPosition(4, 14);
      settingsButton.setTexture(resourceManager.settingsButtonSelectedTex,
                                true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the settings button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        showSettingsPage = true;
      }

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      showQuitGameDialouge = true;
    }
    // Checks if mouse is hovering over the load button
    else if (loadButton.getGlobalBounds().contains(sf::Vector2f(
                 window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the load button
      loadButton.setPosition(-96, 14);
      loadButton.setTexture(resourceManager.loadButtonSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the load button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        shouldLoadGame = true;
        gameState = "gameLoop";
        isGameChanging = true;
      }

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      showQuitGameDialouge = true;
    } else if (!showQuitGameDialouge) {
      playSFX = true;
    }
  }

  // Draws UI elements
  window.draw(background);
  window.draw(menuTitle);
  window.draw(playButton);
  window.draw(loadButton);
  window.draw(settingsButton);
  window.draw(quitButton);

  // Checks if the settings button has been clicked
  if (showSettingsPage) {
    // Checks if mouse is hovering over the exit button
    if (exitButton.getGlobalBounds().contains(sf::Vector2f(
            window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the exit button
      exitButton.setPosition(-332, -222);
      exitButton.setTexture(resourceManager.quitButtonSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the exit button is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        showSettingsPage = false;
      }
    } else if (musicLeftButton.getGlobalBounds().contains(sf::Vector2f(
                   window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the musicLeftButton
      musicLeftButton.setTexture(resourceManager.leftArrowSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the musicLeftButton is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        if (musicVolume >= 1) {
          musicVolume = musicVolume - 1;
          musicLevel.setScale(musicVolume * 3 / 100, musicLevel.getScale().y);
        }
      }
    } else if (musicRightButton.getGlobalBounds().contains(sf::Vector2f(
                   window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the musicRightButton
      musicRightButton.setTexture(resourceManager.rightArrowSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the musicRightButton is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        if (musicVolume <= 99) {
          musicVolume = musicVolume + 1;
          musicLevel.setScale(musicVolume * 3 / 100, musicLevel.getScale().y);
        }
      }
    } else if (sfxLeftButton.getGlobalBounds().contains(sf::Vector2f(
                   window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the sfxLeftButton
      sfxLeftButton.setTexture(resourceManager.leftArrowSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the sfxLeftButton is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        if (sfxVolume >= 1) {
          sfxVolume = sfxVolume - 1;
          sfxLevel.setScale(sfxVolume * 3 / 100, sfxLevel.getScale().y);
        }
      }
    } else if (sfxRightButton.getGlobalBounds().contains(sf::Vector2f(
                   window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
      // Sets selected texture for the sfxRightButton
      sfxRightButton.setTexture(resourceManager.rightArrowSelectedTex, true);
      buttonSound.setBuffer(buttonHovering);
      // Checks if hovering button sound has not played
      if (playSFX) {
        buttonSound.play();
        playSFX = false;
      }
      // Checks if the sfxRightButton is clicked
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        buttonSound.setBuffer(buttonClicked);
        buttonSound.play();
        if (sfxVolume <= 99) {
          sfxVolume = sfxVolume + 1;
          sfxLevel.setScale(sfxVolume * 3 / 100, sfxLevel.getScale().y);
        }
      }
    } else {
      playSFX = true;
    }

    // Draws settings page UI elements
    window.draw(settingsPage);
    window.draw(musicLeftButton);
    window.draw(musicRightButton);
    window.draw(sfxLeftButton);
    window.draw(sfxRightButton);
    window.draw(musicLevel);
    window.draw(sfxLevel);
    window.draw(exitButton);
  }
  // Checks if the quit button has been clicked
  if (showQuitGameDialouge == true) {
    quitGameDialouge();
  }

  window.setFramerateLimit(60);
  window.display();
}
