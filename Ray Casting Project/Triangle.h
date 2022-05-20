#include <SFML/Graphics.hpp>
#include "VecFunctions.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
private:
    sf::Vector3f point_0, point_1, point_2, norm; // Точка 1, точка 2, точка 3, нормальнь
    sf::Vector3i colour; // Цвет
public:
    // Конструктор
    Triangle(const sf::Vector3f& point_a, const sf::Vector3f& point_b, 
        const sf::Vector3f& point_c, const sf::Vector3i& t_colour);

    // Деструктор
    ~Triangle() {}

    // Проверка пересечения
    float intersect(sf::Vector3f cam_position, sf::Vector3f cam_ray);

    // Вывод цвета
    sf::Vector3i rgb();
};

#endif