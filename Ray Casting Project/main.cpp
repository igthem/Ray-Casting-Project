#include <SFML/Graphics.hpp> //���������� ��� ������ � �������� "sf::"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    
    //������ � ������ ������
    int w = 1280;
    int h = 720;

    //������ ����. sf::Style::Fullscreen - �� ������ �����, sf::Style::Titlebar - ����� ���, sf::Style::Close - ����� �������
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", sf::Style::Titlebar | sf::Style::Close);
    
    //����������� ������ � �������
    window.setFramerateLimit(60);
    
    //���� ������ ����
    while (window.isOpen()) {   
        
        //����� ���������� �����
        sf::Event event;
        
        //�������� ���� ������� �� ����
        while (window.pollEvent(event)) {
            
            //������ ��������
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //�������� ����
        window.clear();
        
        //��������� ���� (������� ��������)
        window.display();
    }
 
    return 0;
}