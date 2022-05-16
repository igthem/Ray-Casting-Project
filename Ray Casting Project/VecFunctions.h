#include <SFML/Graphics.hpp>

#ifndef VECFUNCTIONS_H
#define VECFUNCTIONS_H

// Скалярное произведение векторов
float v_mul(sf::Vector3f a, sf::Vector3f b);

// Расчёт длины вектора
float v_len(sf::Vector3f v);

// Нормализация вектора
sf::Vector3f v_norm(sf::Vector3f v);

// Векторное произведение 
sf::Vector3f v_cross(sf::Vector3f a, sf::Vector3f b);

#endif
