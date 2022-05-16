#include <SFML/Graphics.hpp>
#include "Triangle.h"

//constructor
Triangle::Triangle(const sf::Vector3f& a, const sf::Vector3f& b, const sf::Vector3f& c, const sf::Vector3i& d)
{
    Triangle::point_0 = a;
    Triangle::point_0.z = -Triangle::point_0.z;
    Triangle::point_1 = b;
    Triangle::point_1.z = -Triangle::point_1.z;
    Triangle::point_2 = c;
    Triangle::point_2.z = -Triangle::point_2.z;
    Triangle::colour = d;

    Triangle::norm = v_cross(Triangle::point_1 - Triangle::point_0, Triangle::point_2 - Triangle::point_0);
}

float Triangle::intersect(sf::Vector3f ro, sf::Vector3f rd) //ro - camera position; rd - ray from camera
{
    sf::Vector3f v1v0 = Triangle::point_1 - Triangle::point_0;
    sf::Vector3f v2v0 = Triangle::point_2 - Triangle::point_0;
    sf::Vector3f rov0 = ro - Triangle::point_0;
    sf::Vector3f  q = v_cross(rov0, rd);
    float d = 1.0f / v_mul(rd, Triangle::norm);
    float u = d * v_mul(-q, v2v0);
    float v = d * v_mul(q, v1v0);
    float t = d * v_mul(-Triangle::norm, rov0);
    if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t < 0.0f)
        t = -1.0f; 
    //sf::Vector3f e(t, u, v);
    return t;
}

int Triangle::r()
{
    return Triangle::colour.x;
}
int Triangle::g()
{
    return colour.y;
}
int Triangle::b()
{
    return colour.z;
}
sf::Vector3i Triangle::rgb()
{
    return colour;
}