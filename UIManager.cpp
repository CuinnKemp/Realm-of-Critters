#include "UIManager.h"

#include <stdint.h>

#include <sstream>

#include "Player.h"
#include "ResourceManager.h"

// External:
extern ResourceManager resourceManager;  // ResourceManager
extern Player P1;                        // Player

UIManager::UIManager(double Pxpos, double Pypos, double width, double height,
                     sf::RenderWindow* window) {
  // Sets UI window size and resets timer
  UIwidth = 1920;
  UIheight = 1080;
  timerCount = 0;
  P1.resetPlayer();

  // Sets player UI textures
  emptyInfo.setTexture(resourceManager.emptyInfoTex);
  healthBarBottom.setTexture(&resourceManager.healthBarBottomTex);
  healthBarTop.setTexture(&resourceManager.healthBarTopTex);
  levelBarBottom.setTexture(&resourceManager.levelBarBottomTex);
  levelBarTop.setTexture(&resourceManager.levelBarTopTex);

  // Sets time text font and size
  timerText.setFont(resourceManager.defaultFont);
  timerText.setCharacterSize(20);
}

void UIManager::DrawUIManager(sf::RenderWindow* window) {
  // Sets position of player UI elements
  emptyInfo.setPosition(P1.sprite.getPosition().x - UIwidth / 4.1,
                        P1.sprite.getPosition().y - UIheight / 4.1);
  healthBarBottom.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                              P1.sprite.getPosition().y - UIheight / 4.225);
  healthBarTop.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                           P1.sprite.getPosition().y - UIheight / 4.225);
  levelBarBottom.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                             P1.sprite.getPosition().y - UIheight / 4.670);
  levelBarTop.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                          P1.sprite.getPosition().y - UIheight / 4.670);
  timerText.setPosition(
      sf::Vector2f(P1.sprite.getPosition().x - UIwidth / 5.875,
                   P1.sprite.getPosition().y - UIheight / 5.250));
  // Changes health bar width depending on player health
  if (P1.health > 1) {
    healthBarBottom.setSize(sf::Vector2f(P1.health * 1.01 * UIwidth / 1000 + 2,
                                         6 * UIwidth / 1000));
    healthBarTop.setSize(
        sf::Vector2f(healthBarBottom.getSize().x - 10, 6 * UIwidth / 1000));
  } else {
    healthBarBottom.setSize(sf::Vector2f(0, 0));
    healthBarTop.setSize(sf::Vector2f(0, 0));
  }

  // Changes exp bar width depending on exp health
  if (P1.currentExp > 0) {
    levelBarBottom.setSize(
        sf::Vector2f((P1.currentExp * 0.865 * UIwidth / 1000 + 2) / P1.level,
                     6 * UIwidth / 1000));
    levelBarTop.setSize(
        sf::Vector2f(levelBarBottom.getSize().x - 10, 6 * UIwidth / 1000));
  } else {
    levelBarBottom.setSize(sf::Vector2f(0, 0));
    levelBarTop.setSize(sf::Vector2f(0, 0));
  }

  timerText.setString(std::to_string(
      int(P1.clock.getElapsedTime().asSeconds() + P1.savedTime)));

  // Draws player UI elements
  window->draw(emptyInfo);
  window->draw(healthBarBottom);
  window->draw(healthBarTop);
  window->draw(levelBarBottom);
  window->draw(levelBarTop);
  window->draw(timerText);
}

// Reset timer
void UIManager::resetUI() {
  P1.clock.restart();
  timerCount = 0;
}