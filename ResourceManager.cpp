#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

ResourceManager::ResourceManager() {}

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

  deathFont.loadFromFile("OfMiceAndCats.ttf");
}

ResourceManager::~ResourceManager() {}
