#include <SFML/Graphics.hpp>
#include "VecFunctions.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
private:
    sf::Vector3f point_0, point_1, point_2, norm;
    sf::Vector3i colour;
public:
    //consructor
    Triangle(const sf::Vector3f& a, const sf::Vector3f& b, const sf::Vector3f& c, const sf::Vector3i& d);

    //destructor
    ~Triangle() {}

    float intersect(sf::Vector3f ro, sf::Vector3f rd); //ro - camera position; rd - ray from camera

    int r();
    int g();
    int b();
    sf::Vector3i rgb();
};

#endif