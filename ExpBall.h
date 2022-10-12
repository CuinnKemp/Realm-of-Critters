#ifndef EXPBALL_H
#define EXPBALL_H

#include <SFML/Graphics.hpp>

// Exp ball, manages the sprite and collision detection upon monster death
class ExpBall {
 public:
  // Exp given
  int expPoints;

  // Timer for animation
  int timer;

  // Sprite and Animation
  sf::Sprite sprite;
  sf::IntRect rectSourceSprite;

  // Default constructor & Destructor
  ExpBall();
  ~ExpBall();

  // Sequence after Collision
  void collected();

  // Draws the Xp Ball
  void drawExp();

  // Animation Cycle
  bool updateExp();
};
#endif