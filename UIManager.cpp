#include "UIManager.h"

#include <stdint.h>

#include <sstream>

#include "Player.h"
#include "ResourceManager.h"

extern ResourceManager resourceManager;
extern Player P1;

UIManager::UIManager(double Pxpos, double Pypos, double width, double height,
                     sf::RenderWindow* window) {
  UIwidth = 1920;
  UIheight = 1080;
  timer = 0;

  emptyInfo.setTexture(resourceManager.emptyInfoTex);
  healthBarBottom.setTexture(&resourceManager.healthBarBottomTex);
  healthBarTop.setTexture(&resourceManager.healthBarTopTex);
  levelBarBottom.setTexture(&resourceManager.levelBarBottomTex);
  levelBarTop.setTexture(&resourceManager.levelBarTopTex);
  timerText.setFont(resourceManager.defaultFont);
  timerText.setCharacterSize(20);
}

void UIManager::DrawUIManager(sf::RenderWindow* window) {
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

  if (P1.health > 1) {
    healthBarBottom.setSize(sf::Vector2f(P1.health * 1.01 * UIwidth / 1000 + 2,
                                         6 * UIwidth / 1000));
    healthBarTop.setSize(
        sf::Vector2f(healthBarBottom.getSize().x - 10, 6 * UIwidth / 1000));
  } else {
    healthBarBottom.setSize(sf::Vector2f(0, 0));
    healthBarTop.setSize(sf::Vector2f(0, 0));
  }
  if (P1.currentExp > 0) {
    levelBarBottom.setSize(sf::Vector2f(
        P1.currentExp * 0.865 * UIwidth / 1000 + 2, 6 * UIwidth / 1000));
    levelBarTop.setSize(
        sf::Vector2f(levelBarBottom.getSize().x - 10, 6 * UIwidth / 1000));
  } else {
    levelBarBottom.setSize(sf::Vector2f(0, 0));
    levelBarTop.setSize(sf::Vector2f(0, 0));
  }
  timer = round(P1.clock.getElapsedTime().asSeconds() * 1000.0) / 1000.0;
  if (timer < 10) {
    timerText.setString("00:0" + std::to_string(timer));
  } else if (timer < 60) {
    timerText.setString("00:" + std::to_string(timer));
  } else if (timer < 600) {
    std::string tmp = std::string(1, std::to_string(timer).at(0));
    std::string tmp2 = std::string(2, std::to_string(timer).at(1));
    timerText.setString("0" + tmp + ":" + tmp);
  } else {
    std::string tmp = std::string(2, std::to_string(timer).at(0));
    std::string tmp2 = std::string(2, std::to_string(timer).at(2));
    timerText.setString(tmp + ":" + tmp);
  }

  timerText.setPosition(
      sf::Vector2f(P1.sprite.getPosition().x - UIwidth / 5.875,
                   P1.sprite.getPosition().y - UIheight / 5.250));

  window->draw(emptyInfo);
  window->draw(healthBarBottom);
  window->draw(healthBarTop);
  window->draw(levelBarBottom);
  window->draw(levelBarTop);
  window->draw(timerText);
}

void UIManager::resetUI() {
  P1.clock.restart();
  timer = 0;
}