#include <SFML/Graphics.hpp> //Библиотека для работы с графикой "sf::"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    
    //ширина и высота экрана
    int w = 1280;
    int h = 720;

    //создаём окно. sf::Style::Fullscreen - на полный экран, sf::Style::Titlebar - имеет имя, sf::Style::Close - можно закрыть
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", sf::Style::Titlebar | sf::Style::Close);
    
    //ограничение кадров в секунду
    window.setFramerateLimit(60);
    
    //цикл работы окна
    while (window.isOpen()) {   
        
        //задаём переменную цикла
        sf::Event event;
        
        //проверка всех событий за цикл
        while (window.pollEvent(event)) {
            
            //запрос закрытия
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //очистить окно
        window.clear();
        
        //закрасить окно (вывести картинку)
        window.display();
    }
 
    return 0;
}