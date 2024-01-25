#include <SFML/Graphics.hpp>
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


std::vector<Circle>circles;
std::vector<Rectangle>rectangles;
std::vector<windowinfo>window;
std::vector<font>fontt;

void fileread(std::string& filename) {
    std::ifstream file(filename);
    std::string temp;

    
    
    Circle tempCircle;
    Rectangle tempRectangle;
    windowinfo tempWin;
    font tempfont;
    while (file >> temp)
    {
        if (temp == "Window")
        {
            file >> tempWin.width;
            file >> tempWin.height;
            window.push_back(tempWin);
        }
        else if (temp == "Font") {
            file >> tempfont.filelocation;
            file >> tempfont.size;
            file >> tempfont.red;
            file >> tempfont.green;
            file >> tempfont.blue;
            fontt.push_back(tempfont);
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
    if (fontt.size() > 0)
    {
        std::cout << "multiple fonts loading is unsportted\n";
    }
    sf::RenderWindow ddwindow(sf::VideoMode(window[0].width, window[0].height), L"မောင်စိုးသီဟ");
    ddwindow.setFramerateLimit(60);
    
    sf::Font FFont;
    FFont.loadFromFile(fontt[0].filelocation);
    FFont.isSmooth();
    

    sf::Text text;
    text.setFont(FFont);
    text.setFillColor(sf::Color(fontt[0].red, fontt[0].green, fontt[0].blue));
    
    float deltatime = 15.0f;
    
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
            
            rect.setPosition(rectt.firstPosX , rectt.firstPosY );
            
            text.setString(rectt.name);
            text.setCharacterSize(fontt[0].size);
            //std::cout << text.getLocalBounds().width << "\n";
            //text.setPosition((float)rectt.firstPosX /2 - (float)text.getCharacterSize()/2,(float)rectt.firstPosY/2 - text.getCharacterSize()/2);
            text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
            //text.setPosition(rect.getPosition().x + (rect.getLocalBounds().width /2) - text.getLocalBounds().width / 2, rect.getPosition().y + (rect.getLocalBounds().height/2) - text.getLocalBounds().height );
            text.setPosition(rect.getPosition().x + rect.getLocalBounds().width / 2.f, rect.getPosition().y + rect.getLocalBounds().height / 2.0f);
            rect.setFillColor(sf::Color(rectt.red, rectt.green, rectt.blue));
            
            ddwindow.draw(rect);
            ddwindow.draw(text);
            rectt.firstPosX += rectt.initialSpeedX * deltatime;
            rectt.firstPosY += rectt.initialSpeedY * deltatime;
            if (rectt.firstPosX < 0 || rect.getLocalBounds().width + rectt.firstPosX> window[0].width) {
                rectt.initialSpeedX *= -1.0f;
            }
            if (rectt.firstPosY < 0 || rect.getLocalBounds().height + rectt.firstPosY> window[0].height) {
                rectt.initialSpeedY *= -1.0f;
            }
        }

        for (auto& cir : circles) {
            sf::CircleShape circle(cir.radius);
            circle.setPosition(cir.firstPosX, cir.firstPosY);
            text.setString(cir.name);
            text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
            //text.setPosition(circle.getPosition().x + (circle.getLocalBounds().width/2) - text.getLocalBounds().width /2, circle.getPosition().y + (circle.getLocalBounds().height /2) - text.getLocalBounds().height);
            text.setPosition(circle.getPosition().x + circle.getLocalBounds().width / 2.f, circle.getPosition().y + circle.getLocalBounds().height / 2.0f);
            
            circle.setFillColor(sf::Color(cir.red, cir.green, cir.blue));
            ddwindow.draw(circle);
            ddwindow.draw(text);
            cir.firstPosX += cir.initialSpeedX * deltatime;
            cir.firstPosY += cir.initialSpeedY * deltatime;
            if (cir.firstPosX < 0 || circle.getLocalBounds().width + cir.firstPosX> window[0].width) {
                cir.initialSpeedX *= -1.0f;
            }
            if (cir.firstPosY < 0 || circle.getLocalBounds().height + cir.firstPosY> window[0].height) {
                cir.initialSpeedY *= -1.0f;
            }
            // std::cout << cir.radius << "\n";
        }

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
