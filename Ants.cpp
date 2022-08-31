#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

class Ant{
    public:
    int wander = 10;
    int xpos;
    int ypos;
    double xdir;
    double ydir;
    Ant(){
        xpos = 0;
        ypos = 1;
        xdir = ((rand() % 3000)/1000 - 1);
        ydir = ((rand() % 3000)/1000 - 1);
    }
    Ant(int awidth, int aheight){
        xpos = awidth;
        ypos = aheight;
        xdir = ((rand() % 3000)/1000 - 1);
        ydir = ((rand() % 3000)/1000 - 1);
    }
    void UpdatePosition(){
        if ((rand() % wander + 1) == wander){
            xdir = ((rand() % 3000)/1000 - 1);
            ydir = ((rand() % 3000)/1000 - 1);
        }
        else{
            if ((rand() % 2) == 1){
                xdir = xdir + 0.5;
            }

            if ((rand() % 2) == 1){
                xdir = xdir - 0.5;
            }
            
            if ((rand() % 2) == 1){
                ydir = ydir + 0.5;
            }
            
            if ((rand() % 2) == 1){
                ydir = ydir - 0.5;
            }
        }

        xpos = xpos + xdir;
        ypos = ypos + ydir;
    }

};

class Colony{
    public:
    Ant* ants;
    int numAnts;
    int width;
    int height;
    sf::Color colour;

    Colony(){
        numAnts = 1;
        ants = new Ant[numAnts];
        Ant ant;
        ants[0] = ant;
        width = 0;
        height = 0;
        colour.r = 0;
        colour.g = 100;
        colour.b = 0;
        colour.a = 0;
    }

    Colony(int AnumAnts, int strtx, int strty,int r,int g,int b){
        numAnts = AnumAnts;
        ants = new Ant[numAnts];
        for (int i = 0; i < numAnts; i++){
            Ant ant(strtx,strty);
            ants[i] = ant;
        }
        colour.r = r;
        colour.g = g;
        colour.b = b;
    }
    void display(sf::RenderWindow* window){
        for (int i = 0; i < numAnts; i++){

            ants[i].UpdatePosition();
            sf::CircleShape circle;
            circle.setRadius(0.5);
            circle.setFillColor(colour);
            circle.setPosition(ants[i].xpos,ants[i].ypos);
            window->draw(circle);
        }
    }


};


int main(){
    srand(time(NULL));
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    Colony colony1(500, (width/3), (height/2),255,182,193);
    Colony colony2(500, (width*2/3), (height/2),255,105,180);
    Colony colony3(500, (width/2), (height/2),255,20,147);
    sf::RenderWindow window(sf::VideoMode(width, height), "GAME");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color(0,0,0,10));

        window.draw(rectangle);
        
        colony1.display(&window);
        colony2.display(&window);
        colony3.display(&window);



        window.display();
    }

    return 0;
}