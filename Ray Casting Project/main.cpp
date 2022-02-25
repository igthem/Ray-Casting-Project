#include <SFML/Graphics.hpp> //Library for working with graphics "sf::"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    
    //screen width and height
    int w = 1280;
    int h = 720;

    //creating a window. sf::Style::Fullscreen - to full screen, sf::Style::Titlebar - has a name, sf::Style::Close - you can close
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", sf::Style::Titlebar | sf::Style::Close);
    
    //FPS limit
    window.setFramerateLimit(60);
    
    //window operation cycle
    while (window.isOpen()) {   
        
        //setting the loop variable
        sf::Event event;
        
        //checking all events per cycle
        while (window.pollEvent(event)) {
            
            //closing request
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //clear the window
        window.clear();
        
        //paint over the window (display a picture)
        window.display();
    }
 
    return 0;
}