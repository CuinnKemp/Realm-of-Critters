#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>


class Platforms{
    public:
    double screenWidth;
    double screenHeight;
    int platformCount;
    sf::RectangleShape** platforms; //tops, bottoms, leftside, rightside, mask

    void startPlatforms(){
        platformCount = 7;
        platforms = new sf::RectangleShape*[platformCount];
        for (int i = 0; i < platformCount; i++){
            platforms[i] = new sf::RectangleShape[5];
        }
        platforms[0][0].setSize(sf::Vector2f(200,50));
        platforms[0][0].setPosition(sf::Vector2f((screenWidth/2.0)-100, screenHeight*2.0/3.0));
        platforms[0][0].setFillColor(sf::Color::White);
        
        platforms[0][1].setSize(sf::Vector2f(platforms[0][0].getSize().x, 1));
        platforms[0][1].setPosition(sf::Vector2f(platforms[0][0].getPosition().x, platforms[0][0].getPosition().y + platforms[0][0].getSize().y));
        platforms[0][1].setFillColor(sf::Color::Blue);
       
        for (int j = 2; j < 4; j++){
            platforms[0][j].setSize(sf::Vector2f(1,platforms[0][0].getSize().y - 2));
            platforms[0][j].setFillColor(sf::Color::Red);
        }
        platforms[0][2].setPosition(sf::Vector2f(platforms[0][0].getPosition().x,platforms[0][0].getPosition().y + 1));
        platforms[0][3].setPosition(sf::Vector2f(platforms[0][0].getPosition().x + platforms[0][0].getSize().x - platforms[0][3].getSize().x,platforms[0][0].getPosition().y + 1));

        platforms[0][4].setSize(sf::Vector2f(platforms[0][0].getSize().x, platforms[0][0].getSize().y + 1));
        platforms[0][4].setPosition(sf::Vector2f(platforms[0][0].getPosition().x, platforms[0][0].getPosition().y));

        for (int i = 1; i < platformCount; i++){
            platforms[i][0].setSize(sf::Vector2f(200,50));
            int check = 0;
            while (check == 0){
                if (rand() % 2 == 1){
                    platforms[i][0].setPosition(sf::Vector2f(platforms[i-1][0].getPosition().x + (rand() % 300 + 200), platforms[i-1][0].getPosition().y - 150));
                }
                else{
                    platforms[i][0].setPosition(sf::Vector2f(platforms[i-1][0].getPosition().x - (rand() % 300 + 200 ), platforms[i-1][0].getPosition().y - 150));
                }
                if (0 <= platforms[i][0].getPosition().x && (platforms[i][0].getPosition().x + platforms[i][0].getSize().x) <= screenWidth){check = 1;}
            }
            platforms[i][1].setSize(sf::Vector2f(platforms[i][0].getSize().x, 1));
            platforms[i][1].setPosition(sf::Vector2f(platforms[i][0].getPosition().x, platforms[i][0].getPosition().y + platforms[i][0].getSize().y));
            platforms[i][1].setFillColor(sf::Color::Blue);
        
            for (int j = 2; j < 4; j++){
                platforms[i][j].setSize(sf::Vector2f(1,platforms[i][0].getSize().y - 2));
                platforms[i][j].setFillColor(sf::Color::Red);
            }
            platforms[i][2].setPosition(sf::Vector2f(platforms[i][0].getPosition().x,platforms[i][0].getPosition().y + 1));
            platforms[i][3].setPosition(sf::Vector2f(platforms[i][0].getPosition().x + platforms[i][0].getSize().x - platforms[i][3].getSize().x,platforms[i][0].getPosition().y + 1));

            platforms[i][4].setSize(sf::Vector2f(platforms[i][0].getSize().x, platforms[i][0].getSize().y + 1));
            platforms[i][4].setPosition(sf::Vector2f(platforms[i][0].getPosition().x, platforms[i][0].getPosition().y));
        }

    }

    void spawnNewPlatform(int num){
        srand(time(NULL));
        int prevNum = num - 1;
        if (num == 0){
            prevNum = platformCount - 1;
        }
        int check = 0;
        while (check == 0){
            if (rand() % 2 == 1){
                platforms[num][0].setPosition(sf::Vector2f(platforms[prevNum][0].getPosition().x + (rand() % 300 + 200), platforms[prevNum][0].getPosition().y - 150));
            }
            else{
                platforms[num][0].setPosition(sf::Vector2f(platforms[prevNum][0].getPosition().x - (rand() % 300 + 200 ), platforms[prevNum][0].getPosition().y - 150));
            }
            if (0 <= platforms[num][0].getPosition().x && (platforms[num][0].getPosition().x + platforms[num][0].getSize().x) <= screenWidth){check = 1;}
        }

        platforms[num][1].setSize(sf::Vector2f(platforms[num][0].getSize().x, 1));
        platforms[num][1].setPosition(sf::Vector2f(platforms[num][0].getPosition().x, platforms[num][0].getPosition().y + platforms[num][0].getSize().y));
        platforms[num][1].setFillColor(sf::Color::Blue);
    
        for (int j = 2; j < 4; j++){
            platforms[num][j].setSize(sf::Vector2f(1,platforms[num][0].getSize().y - 2));
            platforms[num][j].setFillColor(sf::Color::Red);
        }
        platforms[num][2].setPosition(sf::Vector2f(platforms[num][0].getPosition().x,platforms[num][0].getPosition().y + 1));
        platforms[num][3].setPosition(sf::Vector2f(platforms[num][0].getPosition().x + platforms[num][0].getSize().x - platforms[num][3].getSize().x,platforms[num][0].getPosition().y + 1));

        platforms[num][4].setSize(sf::Vector2f(platforms[num][0].getSize().x, platforms[num][0].getSize().y + 1));
        platforms[num][4].setPosition(sf::Vector2f(platforms[num][0].getPosition().x, platforms[num][0].getPosition().y));
    }

    void movePlatforms(){
        for (int i = 0; i < platformCount; i++){
            for (int j = 0; j < 4; j++){
                platforms[i][j].setPosition(sf::Vector2f(platforms[i][j].getPosition().x, platforms[i][j].getPosition().y + 0.5));
            }
            
            if (platforms[i][0].getPosition().y >= screenHeight){
                this->spawnNewPlatform(i);
            }

        }
    }

    void drawPlatforms(sf::RenderWindow* window){
        this->movePlatforms();

        for (int i = 0; i < platformCount; i++){
            for (int j = 0; j < 4; j++){
                window->draw(platforms[i][j]);
            }
        }
    }

};

class Player{
    public:
    double xpos, ypos;
    double gravity = 5;
    double fallTime = 0;
    double movSpeed = 10;
    double jumpSpeed = 50;

    //collision detections
    int floorTouch = 0;
    int roofTouch = 0;
    int leftTouch = 0;
    int rightTouch = 0;

    sf::RectangleShape sprite;
    Platforms gamePlatforms;
    
    Player(){
        xpos = 0;
        ypos = 0;
        gamePlatforms.screenWidth = 0;
        gamePlatforms.screenHeight = 0;
        gamePlatforms.startPlatforms();
        sprite.setSize(sf::Vector2f(50,50));
        sprite.setFillColor(sf::Color(255,255,255));
    }

    Player(double Pxpos, double Pypos, double width, double height){
        xpos = Pxpos;
        ypos = Pypos;
        gamePlatforms.screenWidth = width;
        gamePlatforms.screenHeight = height;
        gamePlatforms.startPlatforms();
        sprite.setPosition(sf::Vector2f(xpos-25,ypos-25));
        sprite.setSize(sf::Vector2f(50,50));
        sprite.setFillColor(sf::Color(255,255,255));
    }


    void moveRight(){
        xpos = xpos + movSpeed;
        
    }
    void moveLeft(){
        xpos = xpos - movSpeed;
        
    }

    void jump(){
        if (fallTime <= 0.1){
            ypos = ypos - (jumpSpeed * (1-fallTime));
        }
    }

    void applyGravity(){
        ypos = ypos + (gravity * pow(fallTime,2));
        fallTime = fallTime + 0.002;

    }
    
    void collisionCheck(){
        int floorTouch = 0;
        int roofTouch = 0;
        int leftTouch = 0;
        int rightTouch = 0;


        for (int i = 0; i < gamePlatforms.platformCount; i++){
            if (sprite.getGlobalBounds().intersects(gamePlatforms.platforms[i][0].getGlobalBounds())){
                fallTime = 0;
                floorTouch = 1;
                double a = sprite.getPosition().y + sprite.getSize().y;
                double b = gamePlatforms.platforms[i][0].getPosition().y;
                double result = abs(a-b);
                ypos = ypos - result;

            }
            else{this->applyGravity();}
        }

        for (int i = 0; i < gamePlatforms.platformCount; i++){
            if (sprite.getGlobalBounds().intersects(gamePlatforms.platforms[i][1].getGlobalBounds())){
                roofTouch = 1;

                double a = sprite.getPosition().y;
                double b = gamePlatforms.platforms[i][1].getPosition().y + gamePlatforms.platforms[i][1].getSize().y;
                double result = abs(a-b);

                ypos = ypos + result;
            }
        }
        
        for (int i = 0; i < gamePlatforms.platformCount; i++){
            if (sprite.getGlobalBounds().intersects(gamePlatforms.platforms[i][2].getGlobalBounds())){
                leftTouch = 1;
                
                double a = sprite.getPosition().x + sprite.getSize().x;
                double b = gamePlatforms.platforms[i][2].getPosition().x;
                double result = abs(a-b);

                xpos = xpos - result;

            }
        }

        for (int i = 0; i < gamePlatforms.platformCount; i++){
            if (sprite.getGlobalBounds().intersects(gamePlatforms.platforms[i][3].getGlobalBounds())){
                rightTouch = 1;

                double a = sprite.getPosition().x;
                double b = gamePlatforms.platforms[i][3].getPosition().x + gamePlatforms.platforms[i][3].getSize().x;
                double result = abs(a-b);

                xpos = xpos + result;
            }
        }
    }
    
    void getPosition(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->moveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->jump();
        }

        this->collisionCheck();
    }

    void DrawPlayer(sf::RenderWindow* window){
        this->getPosition();
        sprite.setPosition(sf::Vector2f(xpos-25,ypos-25));

        gamePlatforms.drawPlatforms(window);
        window->draw(sprite);
    }

};


int main(){
    double width = sf::VideoMode::getDesktopMode().width;
    double height = sf::VideoMode::getDesktopMode().height;
    Player P1(width/2,height/2, width, height);
    sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color(0,0,0));
        window.draw(rectangle);
        


        P1.DrawPlayer(&window);

        window.display();
    }

    return 0;
}