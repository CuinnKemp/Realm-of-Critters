#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

ResourceManager::ResourceManager() {
  // Loads textures for player and player arrow
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
  arrowTex.loadFromFile("playerAnimation/Arrow.png");
  shuriken.loadFromFile("Shuriken.png");
}

void ResourceManager::loadMainMenu() {
  // Loads textures for main menu
  backgroundTex.loadFromFile("UI/MainMenuBackground.png");
  menuTitleTex.loadFromFile("UI/MenuTitle.png");
  playButtonTex.loadFromFile("UI/PlayButton.png");
  loadButtonTex.loadFromFile("UI/LoadButton.png");
  settingsButtonTex.loadFromFile("UI/SettingsButton.png");
  settingsButtonSelectedTex.loadFromFile("UI/SettingsButtonSelected.png");
  quitButtonTex.loadFromFile("UI/QuitButton.png");
  playButtonSelectedTex.loadFromFile("UI/PlayButtonSelected.png");
  loadButtonSelectedTex.loadFromFile("UI/LoadButtonSelected.png");
  quitButtonSelectedTex.loadFromFile("UI/QuitButtonSelected.png");
  dialougeBoxTex.loadFromFile("UI/DialougeBox.png");
  yesButtonTex.loadFromFile("UI/YesButton.png");
  noButtonTex.loadFromFile("UI/NoButton.png");
  yesButtonSelectedTex.loadFromFile("UI/YesButtonSelected.png");
  noButtonSelectedTex.loadFromFile("UI/NoButtonSelected.png");
  settingsPageTex.loadFromFile("UI/SettingsPage.png");

  // Loads textures for settings page
  leftArrowTex.loadFromFile("UI/ArrowButtonLeft.png");
  rightArrowTex.loadFromFile("UI/ArrowButtonRight.png");
  leftArrowSelectedTex.loadFromFile("UI/ArrowButtonSelectedLeft.png");
  rightArrowSelectedTex.loadFromFile("UI/ArrowButtonSelectedRight.png");
  audioLevelTex.loadFromFile("UI/AudioBar.png");
}

void ResourceManager::loadGame() {
  // Loads map textures
  mapImage.loadFromFile("backgroundMap.png");
  extrasImage.loadFromFile("mapExtras.png");
  grass.loadFromFile("barrier/grass.png");
  desert.loadFromFile("barrier/desert.png");
  snow.loadFromFile("barrier/snow.png");
  dirt.loadFromFile("barrier/dirt.png");

  // Loads exp ball textures
  exp1.loadFromFile("expAnimation/exp1.png");
  exp2.loadFromFile("expAnimation/exp2.png");
  exp3.loadFromFile("expAnimation/exp3.png");
  exp4.loadFromFile("expAnimation/exp4.png");
  exp5.loadFromFile("expAnimation/exp5.png");
  exp6.loadFromFile("expAnimation/exp6.png");
  exp7.loadFromFile("expAnimation/exp7.png");
  exp8.loadFromFile("expAnimation/exp8.png");

  // Loads Beasts textures
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

  // Loads Slime textures
  slimeWalkDown1.loadFromFile("slimeAnimation/walkDown1.png");
  slimeWalkDown2.loadFromFile("slimeAnimation/walkDown2.png");
  slimeWalkDown3.loadFromFile("slimeAnimation/walkDown3.png");
  slimeWalkDown4.loadFromFile("slimeAnimation/walkDown4.png");
  slimeWalkUp1.loadFromFile("slimeAnimation/walkUp1.png");
  slimeWalkUp2.loadFromFile("slimeAnimation/walkUp2.png");
  slimeWalkUp3.loadFromFile("slimeAnimation/walkUp3.png");
  slimeWalkUp4.loadFromFile("slimeAnimation/walkUp4.png");
  slimeWalkLeft1.loadFromFile("slimeAnimation/walkLeft1.png");
  slimeWalkLeft2.loadFromFile("slimeAnimation/walkLeft2.png");
  slimeWalkLeft3.loadFromFile("slimeAnimation/walkLeft3.png");
  slimeWalkLeft4.loadFromFile("slimeAnimation/walkLeft4.png");
  slimeWalkRight1.loadFromFile("slimeAnimation/walkRight1.png");
  slimeWalkRight2.loadFromFile("slimeAnimation/walkRight2.png");
  slimeWalkRight3.loadFromFile("slimeAnimation/walkRight3.png");
  slimeWalkRight4.loadFromFile("slimeAnimation/walkRight4.png");

  // Loads UI Textures
  emptyInfoTex.loadFromFile("UI/EmptyInfo.png");
  healthBarBottomTex.loadFromFile("UI/HealthBarBottom.png");
  healthBarTopTex.loadFromFile("UI/HealthBarTop.png");
  levelBarBottomTex.loadFromFile("UI/LevelBarBottom.png");
  levelBarTopTex.loadFromFile("UI/LevelBarTop.png");

  // Loads text font
  defaultFont.loadFromFile("OfMiceAndCats.ttf");
}

ResourceManager::~ResourceManager() {}
