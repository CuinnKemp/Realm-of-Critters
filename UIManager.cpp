#include "UIManager.h"

#include "Player.h"

extern Player P1;

UIManager::UIManager(double Pxpos, double Pypos, double width, double height,
                     sf::RenderWindow* window) {
  UIwidth = 1920;
  UIheight = 1080;
  emptyInfoTex.loadFromFile("UI/EmptyInfo.png");
  emptyInfo.setTexture(emptyInfoTex);
  emptyInfo.setScale(sf::Vector2f(1, 1));
  healthBar.setFillColor(sf::Color::Red);
  healthBar.setPosition(0 - width / 2, 0 - height / 2);
}

void UIManager::DrawUIManager(sf::RenderWindow* window) {
  emptyInfo.setPosition(P1.sprite.getPosition().x - UIwidth / 4.1,
                        P1.sprite.getPosition().y - UIheight / 4.1);
  healthBar.setPosition(P1.sprite.getPosition().x - UIwidth / 5.25,
                        P1.sprite.getPosition().y - UIheight / 4.15);
  healthBar.setSize(
      sf::Vector2f(P1.health * UIwidth / 1000, 9 * UIwidth / 1000));
  window->draw(emptyInfo);
  window->draw(healthBar);
}

void UIManager::resetUI() {
  healthBar.setPosition(0 - UIwidth / 2, 0 - UIheight / 2);
}