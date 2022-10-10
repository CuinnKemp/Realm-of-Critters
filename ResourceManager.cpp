#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

ResourceManager::ResourceManager() {
  backgroundTex.loadFromFile("UI/MainMenuBackground.png");
  menuTitleTex.loadFromFile("UI/MenuTitle.png");
  playButtonTex.loadFromFile("UI/PlayButton.png");
  loadButtonTex.loadFromFile("UI/LoadButton.png");
  settingsButtonTex.loadFromFile("UI/SettingsButton.png");
  quitButtonTex.loadFromFile("UI/QuitButton.png");
  playButtonSelectedTex.loadFromFile("UI/PlayButtonSelected.png");
  loadButtonSelectedTex.loadFromFile("UI/LoadButtonSelected.png");
  quitButtonSelectedTex.loadFromFile("UI/QuitButtonSelected.png");
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
  quitButton.setScale(6, 6);
  quitButton.setPosition(110, 20);

  mapImage.loadFromFile("backgroundMap.png");
  extrasImage.loadFromFile("mapExtras.png");
  backgroundMap.scale(2, 2);
  backgroundMap.setTexture(mapImage);
  backgroundMap.setPosition(-3586, -3616);
  mapExtras.scale(2, 2);
  mapExtras.setTexture(extrasImage);
  mapExtras.setPosition(-2048, -2048);
}

ResourceManager::~ResourceManager() {}
