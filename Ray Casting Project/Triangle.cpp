#include <SFML/Graphics.hpp>
#include "Triangle.h"

// Конструктор
// Принимаем значения 
Triangle::Triangle(const sf::Vector3f& point_a, const sf::Vector3f& point_b, 
    const sf::Vector3f& point_c, const sf::Vector3i& t_colour)
{
    // Задаём значения для точек треуголника и его цвет
    Triangle::point_0 = point_a;
    Triangle::point_0.z = -Triangle::point_0.z;
    Triangle::point_1 = point_b;
    Triangle::point_1.z = -Triangle::point_1.z;
    Triangle::point_2 = point_c;
    Triangle::point_2.z = -Triangle::point_2.z;
    Triangle::colour = t_colour;

    // Создание нормали с использованием векторного произведения
    Triangle::norm = v_cross(Triangle::point_1 - Triangle::point_0, Triangle::point_2 - Triangle::point_0);
}

// Функция проверки пересечения луча и треугольника, где выводится расстояние от камеры до пересечения
float Triangle::intersect(sf::Vector3f cam_position, sf::Vector3f cam_ray)
{
    sf::Vector3f vec_p0p1 = Triangle::point_1 - Triangle::point_0;
    sf::Vector3f vec_p0p2 = Triangle::point_2 - Triangle::point_0;
    sf::Vector3f vec_p0_cam = cam_position - Triangle::point_0;
    sf::Vector3f  q = v_cross(vec_p0_cam, cam_ray);
    float d = 1.0f / v_mul(cam_ray, Triangle::norm);
    float u = d * v_mul(-q, vec_p0p2);
    float v = d * v_mul(q, vec_p0p1);
    float t = d * v_mul(-Triangle::norm, vec_p0_cam);
    if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t < 0.0f)
        t = -1.0f; 
    return t;
}

// Вывод всего цвета треугольника
sf::Vector3i Triangle::rgb()
{
    return colour;
}