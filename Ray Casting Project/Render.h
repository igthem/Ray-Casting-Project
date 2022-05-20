#include <SFML/Graphics.hpp>
#include "Triangle.h"
#include <vector>

#ifndef RENDER_H
#define RENDER_H

// Функция для поиска пересечений
void render(sf::Uint8*& pixels, std::vector<Triangle> triangles, int screen_width, int screen_high,
    sf::Vector3f cam, sf::Vector3f** vecs);

#endif