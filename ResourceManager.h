#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <SFML/Graphics.hpp>

class ResourceManager {
 public:
  sf::Texture backgroundTex, menuTitleTex, playButtonTex, loadButtonTex,
      settingsButtonTex, settingsButtonSelectedTex, quitButtonTex,
      playButtonSelectedTex, loadButtonSelectedTex, quitButtonSelectedTex,
      quitGameDialougeBoxTex, mapImage, extrasImage, emptyInfoTex,
      healthBarBottomTex, healthBarTopTex, levelBarBottomTex, levelBarTopTex,
      shuriken, idleLeft, idleRight, idleUp, idleDown, pwalkDown1, pwalkDown2,
      pwalkDown3, pwalkDown4, pwalkUp1, pwalkUp2, pwalkUp3, pwalkUp4,
      pwalkLeft1, pwalkLeft2, pwalkLeft3, pwalkLeft4, pwalkRight1, pwalkRight2,
      pwalkRight3, pwalkRight4, grass, desert, snow, dirt, exp1, exp2, exp3,
      exp4, exp5, exp6, exp7, exp8, walkDown1, walkDown2, walkDown3, walkDown4,
      walkUp1, walkUp2, walkUp3, walkUp4, walkLeft1, walkLeft2, walkLeft3,
      walkLeft4, walkRight1, walkRight2, walkRight3, walkRight4, dialougeBoxTex,
      yesButtonTex, noButtonTex, yesButtonSelectedTex, noButtonSelectedTex,
      settingsPageTex, slimeWalkDown1, slimeWalkDown2, slimeWalkDown3,
      slimeWalkDown4, slimeWalkUp1, slimeWalkUp2, slimeWalkUp3, slimeWalkUp4,
      slimeWalkLeft1, slimeWalkLeft2, slimeWalkLeft3, slimeWalkLeft4,
      slimeWalkRight1, slimeWalkRight2, slimeWalkRight3, slimeWalkRight4,
      arrowTex;
  sf::Font defaultFont;
  ResourceManager();
  void loadMainMenu();
  void loadGame();
  ~ResourceManager();
};
#endif  // RESOURCEMANAGER_H
