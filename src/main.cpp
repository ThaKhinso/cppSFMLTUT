#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
const int width = 800;
const int height = 600;



struct windowinfo {
    int width = 0;
    int height = 0;
};

// std::unique_ptr<windowinfo>window;

struct font {
    std::string filelocation;
    int size;
    int red, green, blue = 0;
};

struct Circle {
    std::string name;
    float firstPosX = 0;
    float firstPosY = 0;
    float initialSpeedX = 0;
    float initialSpeedY = 0;
    int red, green, blue = 0;
    int radius = 0;
};

struct Rectangle {
    std::string name;
    float firstPosX = 0;
    float firstPosY = 0;
    float initialSpeedX = 0;
    float initialSpeedY = 0;
    int red, green, blue = 0;
    int Width, Height = 0;
};

std::vector<font>fonts;
std::vector<Circle>circles;
std::vector<Rectangle>rectangles;
std::unique_ptr<windowinfo>window = std::make_unique<windowinfo>();
std::unique_ptr<font> fontt = std::make_unique<font>();

void fileread(std::string& filename) {
    std::ifstream file(filename);
    std::string temp;

    
    
    Circle tempCircle;
    Rectangle tempRectangle;
    windowinfo tempWin;
    while (file >> temp)
    {
        if (temp == "Window")
        {
            file >> window->width;
            file >> window->height;
            // window.push_back(tempWin);
        }
        else if (temp == "Font") {
            file >> fontt->filelocation;
            file >> fontt->size;
            file >> fontt->red;
            file >> fontt->green;
            file >> fontt->blue;
        }
        else if (temp == "Circle")
        {   
            file >> tempCircle.name;
            file >> tempCircle.firstPosX;
            file >> tempCircle.firstPosY;
            file >> tempCircle.initialSpeedX;
            file >> tempCircle.initialSpeedY;
            file >> tempCircle.red >> tempCircle.green >> tempCircle.blue >> tempCircle.radius;

            circles.push_back(tempCircle);
        } else if (temp == "Rectangle") {
            file >> tempRectangle.name >> tempRectangle.firstPosX >> tempRectangle.firstPosY >> tempRectangle.initialSpeedX >> tempRectangle.initialSpeedY >> tempRectangle.red >> tempRectangle.green >> tempRectangle.blue >> tempRectangle.Width >> tempRectangle.Height;

            rectangles.push_back(tempRectangle);
        }
    }
}


int main()
{
    // create the window
    // sf::RenderWindow ddwindow(sf::VideoMode(window[0].width,window[0].height), "My window is that time i got reincarneated as a slime");
    
    
    std::string ccc = "config.txt";
    fileread(ccc);
    sf::RenderWindow ddwindow(sf::VideoMode(window->width,window->height), "My window is that time i got reincarneated as a slime");
    
    sf::Font FFont;
    FFont.loadFromFile(fontt->filelocation);
    

    sf::Text text;
    text.setFont(FFont);
    text.setFillColor(sf::Color(fontt->red,fontt->green,fontt->blue));
    

    // #ifdef __linux
    // text.loadFromFile("bin/OIP.jpg");
    // font.loadFromFile("bin/fonts/PoppkornRegular-MzKY.ttf");
    // #endif

    #ifdef __WIN64__
    /*text.loadFromFile("OIP.jpg");
    if (!font.loadFromFile("fonts/PoppkornRegular-MzKY.ttf")) {
        std::cerr << "font cannot load\n";
    }*/
    #endif

    //sf::Text sar("Sample Text", font, 50);
    //sar.setPosition(0, height - (float)sar.getCharacterSize());
    ////sar.setPosition(0, 0);
    //
    ////shape.setFillColor(sf::Color(150, 50, 250));
    //text.setSmooth(true);
    //shape.setTexture(&text);
    

    // set a 10-pixel wide orange outline
    /*shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));*/
    //shape.setPosition(sf::Vector2f(400, 200));
    // run the program as long as the window is open
    while (ddwindow.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (ddwindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                ddwindow.close();

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed with code: " << event.key.code << "\n";

                if (event.key.code == sf::Keyboard::Escape) {
                    ddwindow.close();
                }
            }
        }

        // clear the window with black color
        ddwindow.clear(sf::Color::Black);
        for (auto& rectt : rectangles) {
            sf::RectangleShape rect(sf::Vector2f(rectt.Width, rectt.Height));
            rect.setPosition(rectt.firstPosX, rectt.firstPosY);
            text.setString(rectt.name);
            text.setCharacterSize(fontt->size);
            
            text.setPosition(rect.getLocalBounds().width/2 - (float)text.getCharacterSize()/2,rect.getLocalBounds().height/2 - text.getCharacterSize()/2);
            rect.setFillColor(sf::Color(rectt.red, rectt.green, rectt.blue));
            
            ddwindow.draw(rect);
            ddwindow.draw(text);
        }

        // for (auto& cir : circles) {
        //     sf::CircleShape circle(cir.radius);
        //     circle.setPosition(cir.firstPosX, cir.firstPosY);
        //     circle.setFillColor(sf::Color(cir.red, cir.green, cir.blue));
        //     ddwindow.draw(circle);
        //     // std::cout << cir.radius << "\n";
        // }

        // for (auto& reet  : rectangles) {
        //     std::cout << reet.red << "\n";
        // }
        // draw everything here...
        //sf::Time elapsed2 = clock.getElapsedTime();/*
        //std::cout << elapsed2.asSeconds() << std::endl;*/

        // window.draw(...);

        // end the current frame
        
        ddwindow.display();
    }

    return 0;
}
