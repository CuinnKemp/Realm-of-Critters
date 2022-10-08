#include "UIManager.h"

#include "Player.h"

extern Player P1;

UIManager::UIManager(double Pxpos, double Pypos, double width, double height,
                     sf::RenderWindow* window) {
  UIwidth = 1920;
  UIheight = 1080;
  emptyInfoTex.loadFromFile("UI/EmptyInfo.png");
  emptyInfo.setTexture(emptyInfoTex);
  this->emptyInfo.setScale(sf::Vector2f(1, 1));
}

void UIManager::DrawUIManager(sf::RenderWindow* window) {
  emptyInfo.setPosition(P1.sprite.getPosition().x - UIwidth / 4.1,
                        P1.sprite.getPosition().y - UIheight / 4.1);
  window->draw(emptyInfo);
}