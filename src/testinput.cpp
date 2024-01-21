#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
const int width = 800;
const int height = 600;



struct windowinfo {
    int width;
    int height;
};

windowinfo window;

struct font {
    std::string filelocation;
    int size;
    int red, green, blue;
};

struct Circle {
    std::string name;
    float firstPosX;
    float firstPosY;
    float initialSpeedX;
    float initialSpeedY;
    int red, green, blue;
    int radius;
};

struct Rectangle {
    std::string name;
    float firstPosX;
    float firstPosY;
    float initialSpeedX;
    float initialSpeedY;
    int red, green, blue;
    int Width, Height;
};

std::vector<font>fonts;
std::vector<Circle>circles;
std::vector<Rectangle>rectangles;

void fileread(std::string& filename) {
    std::ifstream file(filename);
    std::string temp;
    
    font tempFont;
    Circle tempCircle;
    Rectangle tempRectangle;
    while (file >> temp)
    {
        if (temp == "Window")
        {
            file >> window.width;
            file >> window.height;
        }
        else if (temp == "Font") {
            file >> tempFont.filelocation;
            file >> tempFont.size;
            file >> tempFont.red;
            file >> tempFont.blue;
            file >> tempFont.green;
            fonts.push_back(tempFont);
        }
        else if (temp == "Circle")
        {   
            file >> tempCircle.name;
            file >> tempCircle.firstPosX;
            file >> tempCircle.firstPosY;
            file >> tempCircle.initialSpeedX;
            file >> tempCircle.initialSpeedY;
            file >> tempCircle.red >> tempCircle.green >> tempCircle.blue ;

            circles.push_back(tempCircle);
        } else if (temp == "Rectangle") {
            file >> tempRectangle.name >> tempRectangle.firstPosX >> tempRectangle.firstPosY >> tempRectangle.initialSpeedX >> tempRectangle.initialSpeedY >> tempRectangle.red >> tempRectangle.green >> tempRectangle.blue >> tempRectangle.Width >> tempRectangle.Height;

            rectangles.push_back(tempRectangle);
        }
    }
}

int main(int argc, char** argv) {
    std::string ttt = "bin/config.txt";
    fileread(ttt);
    std::cout << window.width << "\n";
    for (auto &rectangle  : rectangles) {
        std::cout << rectangle.red << "\n";
    }
    for (auto& font : fonts) {
        std::cout << font.filelocation << "\n";
    }
}