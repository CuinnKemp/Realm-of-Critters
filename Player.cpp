#include "Player.h"

extern double xpos, ypos;

Player::Player(double Pxpos, double Pypos, double width, double height, sf::RenderWindow* window){
    xpos = Pxpos;
    ypos = Pypos;
    this->health = 100;
    this->movSpeed = 5;
    this->window = window;
    this->sprite.setPosition(sf::Vector2f(xpos-20,ypos-20));
    this->sprite.setSize(sf::Vector2f(40,40));
    standing.loadFromFile("STANDING.png");
    standing.setSmooth(true);
    running1.loadFromFile("RUNNING1.png");
    running1.setSmooth(true);
    running2.loadFromFile("RUNNING2.png");
    running2.setSmooth(true);
    sprite.setTexture(&standing);
    camera.setCenter(0,0);
    camera.setSize(width, height);
    window->setView(camera);
    this->animationCount = 0;

    this->healthBarBack.setFillColor(sf::Color::Black);
    this->healthBarBack.setPosition(camera.getCenter().x - width/2, camera.getCenter().y - height/2);
    this->healthBarBack.setSize(sf::Vector2f(200,20));

    this->healthBarFront.setFillColor(sf::Color::Red);
    this->healthBarFront.setPosition(camera.getCenter().x - width/2, camera.getCenter().y - height/2);
    this->healthBarFront.setSize(sf::Vector2f(200,20));
}

void Player::resetPlayer(){
    xpos = 0;
    ypos = 0;
    camera.setCenter(0,0);
    this->sprite.setPosition(sf::Vector2f(xpos-20,ypos-20));
    this->sprite.setSize(sf::Vector2f(40,40));
    this->animationCount = 0;
    this->health = 100;
    
    this->healthBarBack.setPosition(camera.getCenter().x - camera.getSize().x/2, camera.getCenter().y - camera.getSize().y/2);
    this->healthBarFront.setPosition(camera.getCenter().x - camera.getSize().x/2, camera.getCenter().y - camera.getSize().y/2);
    this->healthBarFront.setSize(sf::Vector2f(200,20));

}

void Player::moveRight(){
    xpos = xpos + movSpeed;
}
void Player::moveLeft(){
    xpos = xpos - movSpeed;
    
}

void Player::moveUp(){
    ypos = ypos - movSpeed;
}

void Player::moveDown(){
    ypos = ypos + movSpeed;
}

void Player::getPosition(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->moveLeft();
        animationCount++;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->moveRight();
        animationCount++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        this->moveUp();
        animationCount++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->moveDown();
        animationCount++;
    }

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
        animationCount = 0;
    }

    if (animationCount == 0){
        sprite.setTexture(&standing);
    }
    else if (remainder(animationCount/10, 2) == 0){
        sprite.setTexture(&running2);
    }
    else{
        sprite.setTexture(&running1);
    }


}

bool Player::isAlive(){
    if (health >= 0){
        return 1;
    }
    camera.setCenter(0,0);
    window->setView(camera);
    return 0;
}

void Player::DrawPlayer(sf::RenderWindow* window){
    this->getPosition();
    sprite.setPosition(sf::Vector2f(xpos-20,ypos-20));
    window->draw(sprite);
    camera.setCenter(sprite.getPosition());
    window->setView(camera);

    this->healthBarBack.setPosition(camera.getCenter().x - camera.getSize().x/2, camera.getCenter().y - camera.getSize().y/2);
    this->healthBarFront.setPosition(camera.getCenter().x - camera.getSize().x/2, camera.getCenter().y - camera.getSize().y/2);
    this->healthBarFront.setSize(sf::Vector2f(health*2, 20));

    window->draw(healthBarBack);
    window->draw(healthBarFront);
}