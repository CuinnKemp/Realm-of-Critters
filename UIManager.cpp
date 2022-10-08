#include "UIManager.h"

#include "Player.h"

extern Player P1;

UIManager::UIManager(double Pxpos, double Pypos, double width, double height,
                     sf::RenderWindow* window) {
  UIwidth = 1920;
  UIheight = 1080;
  emptyInfoTex.loadFromFile("UI/EmptyInfo.png");
  healthBarBottomTex.loadFromFile("UI/HealthBarBottom.png");
  healthBarTopTex.loadFromFile("UI/HealthBarTop.png");
  emptyInfo.setTexture(emptyInfoTex);
  healthBarBottom.setTexture(&healthBarBottomTex);
  healthBarTop.setTexture(&healthBarTopTex);
  emptyInfo.setScale(sf::Vector2f(1, 1));
  healthBarBottom.setSize(sf::Vector2f(1, 1));
  healthBarTop.setSize(sf::Vector2f(1, 1));
  healthBarBottom.setPosition(0 - width / 2, 0 - height / 2);
  healthBarTop.setPosition(0 - width / 2, 0 - height / 2);
}

void UIManager::DrawUIManager(sf::RenderWindow* window) {
  emptyInfo.setPosition(P1.sprite.getPosition().x - UIwidth / 4.1,
                        P1.sprite.getPosition().y - UIheight / 4.1);
  healthBarBottom.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                              P1.sprite.getPosition().y - UIheight / 4.225);
  healthBarTop.setPosition(P1.sprite.getPosition().x - UIwidth / 5.275,
                           P1.sprite.getPosition().y - UIheight / 4.225);

  if (P1.health > 5) {
    healthBarBottom.setSize(
        sf::Vector2f(P1.health * 1.01 * UIwidth / 1000, 8 * UIwidth / 1000));
    healthBarTop.setSize(
        sf::Vector2f(healthBarBottom.getSize().x - 10, 8 * UIwidth / 1000));
  }
  window->draw(emptyInfo);
  window->draw(healthBarBottom);
  window->draw(healthBarTop);
}

void UIManager::resetUI() {
  healthBarBottom.setPosition(0 - UIwidth / 2, 0 - UIheight / 2);
  healthBarTop.setPosition(0 - UIwidth / 2, 0 - UIheight / 2);
}