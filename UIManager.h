#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Player.h"

class UIManager {
 public:
  sf::Sprite emptyInfo;
  sf::RectangleShape healthBarBottom, healthBarTop, levelBarBottom, levelBarTop;
  sf::Text timerText;
  double UIwidth, UIheight;
  int timer;

  UIManager(double Pxpos, double Pypos, double width, double height,
            sf::RenderWindow* window);

  void DrawUIManager(sf::RenderWindow* window);
  void resetUI();
  ~UIManager() {}
};

#endif  // UIMANAGER_H