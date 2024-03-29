#include "VecFunctions.h"

// Скалярное произведение векторов
float v_mul(sf::Vector3f a, sf::Vector3f b)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z);
}

// Расчёт длины вектора
float v_len(sf::Vector3f v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Нормализация вектора
sf::Vector3f v_norm(sf::Vector3f v)
{
    float len = v_len(v);
    v = v * (1 / len);
    return v;
}

// Векторное произведение
sf::Vector3f v_cross(sf::Vector3f a, sf::Vector3f b)
{
    sf::Vector3f c
    {
        a.y * b.z - b.y * a.z,
        a.z * b.x - b.z * a.x,
        a.x * b.y - b.x * a.y
    };
    return(c);
}