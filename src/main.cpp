#include <SFML/Graphics.hpp>
#include <iostream>

#ifdef __WIN_64
#endif


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Clock clock;

    sf::Time elapsed1 = clock.getElapsedTime();
    std::cout << elapsed1.asSeconds() << std::endl;
    clock.restart();

    sf::CircleShape shape(50.f);
    sf::Texture text;

    #ifdef __linux
    text.loadFromFile("bin/OIP.jpg");
    #endif

    #ifdef __WINDOW__
    text.loadFromFile("OIP.jpg");
    #endif
    
    //shape.setFillColor(sf::Color(150, 50, 250));
    text.setSmooth(true);
    shape.setTexture(&text);
    

    // set a 10-pixel wide orange outline
    /*shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));*/
    shape.setPosition(sf::Vector2f(400, 200));
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Blue);
        window.draw(shape);
        // draw everything here...
        //sf::Time elapsed2 = clock.getElapsedTime();/*
        //std::cout << elapsed2.asSeconds() << std::endl;*/

        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}
