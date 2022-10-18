#ifndef GAMELOADER_H
#define GAMELOADER_H

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
using namespace std;

class GameLoader {
 public:
  int saveGame(int health, int level, int currentExp, float time, int pArrowLvl, int sBladeLvl);
  int loadGame();
  void encryptSaveGame();
  void decryptSaveGame();
  void quitGameDialouge();
  void gameLoop();
  void mainMenu();
  

};

#endif  // GAMELOADER