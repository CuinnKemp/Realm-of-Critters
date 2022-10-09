#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

class UIManager {
 public:
  sf::Texture emptyInfoTex, healthBarBottomTex, healthBarTopTex,
      levelBarBottomTex, levelBarTopTex;
  sf::Sprite emptyInfo;
  sf::RectangleShape healthBarBottom, healthBarTop, levelBarBottom, levelBarTop;
  double UIwidth, UIheight;

  UIManager(double Pxpos, double Pypos, double width, double height,
            sf::RenderWindow* window);

  void DrawUIManager(sf::RenderWindow* window);
  void resetUI();
  ~UIManager() {}
};

#endif  // UIMANAGER_H