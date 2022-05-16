#include <SFML/Graphics.hpp>

#ifndef VECFUNCTIONS_H
#define VECFUNCTIONS_H

//scalar multiplication
float v_mul(sf::Vector3f a, sf::Vector3f b);

//vector len
float v_len(sf::Vector3f v);

//vector normalisation 
sf::Vector3f v_norm(sf::Vector3f v);

//vector multiplication
sf::Vector3f v_cross(sf::Vector3f a, sf::Vector3f b);

#endif
