#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

ResourceManager::ResourceManager() {
  idleDown.loadFromFile("playerAnimation/Idle/idleDown.png");
  idleUp.loadFromFile("playerAnimation/Idle/idleUp.png");
  idleLeft.loadFromFile("playerAnimation/Idle/idleLeft.png");
  idleRight.loadFromFile("playerAnimation/Idle/idleRight.png");
  idleRight.loadFromFile("playerAnimation/Idle/idleRight.png");
  pwalkDown1.loadFromFile("playerAnimation/Walk/walkDown1.png");
  pwalkDown2.loadFromFile("playerAnimation/Walk/walkDown2.png");
  pwalkDown3.loadFromFile("playerAnimation/Walk/walkDown3.png");
  pwalkDown4.loadFromFile("playerAnimation/Walk/walkDown4.png");
  pwalkUp1.loadFromFile("playerAnimation/Walk/walkUp1.png");
  pwalkUp2.loadFromFile("playerAnimation/Walk/walkUp2.png");
  pwalkUp3.loadFromFile("playerAnimation/Walk/walkUp3.png");
  pwalkUp4.loadFromFile("playerAnimation/Walk/walkUp4.png");
  pwalkLeft1.loadFromFile("playerAnimation/Walk/walkLeft1.png");
  pwalkLeft2.loadFromFile("playerAnimation/Walk/walkLeft2.png");
  pwalkLeft3.loadFromFile("playerAnimation/Walk/walkLeft3.png");
  pwalkLeft4.loadFromFile("playerAnimation/Walk/walkLeft4.png");
  pwalkRight1.loadFromFile("playerAnimation/Walk/walkRight1.png");
  pwalkRight2.loadFromFile("playerAnimation/Walk/walkRight2.png");
  pwalkRight3.loadFromFile("playerAnimation/Walk/walkRight3.png");
  pwalkRight4.loadFromFile("playerAnimation/Walk/walkRight4.png");
}

void ResourceManager::loadMainMenu() {
  backgroundTex.loadFromFile("UI/MainMenuBackground.png");
  menuTitleTex.loadFromFile("UI/MenuTitle.png");
  playButtonTex.loadFromFile("UI/PlayButton.png");
  loadButtonTex.loadFromFile("UI/LoadButton.png");
  settingsButtonTex.loadFromFile("UI/SettingsButton.png");
  quitButtonTex.loadFromFile("UI/QuitButton.png");
  playButtonSelectedTex.loadFromFile("UI/PlayButtonSelected.png");
  loadButtonSelectedTex.loadFromFile("UI/LoadButtonSelected.png");
  quitButtonSelectedTex.loadFromFile("UI/QuitButtonSelected.png");
}

void ResourceManager::loadGame() {
  mapImage.loadFromFile("backgroundMap.png");
  extrasImage.loadFromFile("mapExtras.png");
  grass.loadFromFile("barrier/grass.png");
  desert.loadFromFile("barrier/desert.png");
  snow.loadFromFile("barrier/snow.png");
  dirt.loadFromFile("barrier/dirt.png");

  exp1.loadFromFile("expAnimation/exp1.png");
  exp2.loadFromFile("expAnimation/exp2.png");
  exp3.loadFromFile("expAnimation/exp3.png");
  exp4.loadFromFile("expAnimation/exp4.png");
  exp5.loadFromFile("expAnimation/exp5.png");
  exp6.loadFromFile("expAnimation/exp6.png");
  exp7.loadFromFile("expAnimation/exp7.png");
  exp8.loadFromFile("expAnimation/exp8.png");

  walkDown1.loadFromFile("beastAnimation/walkDown1.png");
  walkDown2.loadFromFile("beastAnimation/walkDown2.png");
  walkDown3.loadFromFile("beastAnimation/walkDown3.png");
  walkDown4.loadFromFile("beastAnimation/walkDown4.png");
  walkUp1.loadFromFile("beastAnimation/walkUp1.png");
  walkUp2.loadFromFile("beastAnimation/walkUp2.png");
  walkUp3.loadFromFile("beastAnimation/walkUp3.png");
  walkUp4.loadFromFile("beastAnimation/walkUp4.png");
  walkLeft1.loadFromFile("beastAnimation/walkLeft1.png");
  walkLeft2.loadFromFile("beastAnimation/walkLeft2.png");
  walkLeft3.loadFromFile("beastAnimation/walkLeft3.png");
  walkLeft4.loadFromFile("beastAnimation/walkLeft4.png");
  walkRight1.loadFromFile("beastAnimation/walkRight1.png");
  walkRight2.loadFromFile("beastAnimation/walkRight2.png");
  walkRight3.loadFromFile("beastAnimation/walkRight3.png");
  walkRight4.loadFromFile("beastAnimation/walkRight4.png");

  emptyInfoTex.loadFromFile("UI/EmptyInfo.png");
  healthBarBottomTex.loadFromFile("UI/HealthBarBottom.png");
  healthBarTopTex.loadFromFile("UI/HealthBarTop.png");
  levelBarBottomTex.loadFromFile("UI/LevelBarBottom.png");
  levelBarTopTex.loadFromFile("UI/LevelBarTop.png");
  shuriken.loadFromFile("Shuriken.png");

  defaultFont.loadFromFile("OfMiceAndCats.ttf");
}

ResourceManager::~ResourceManager() {}
