#include <SFML/Graphics.hpp> //Library for working with graphics "sf::"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

//deg2rad
float deg2rad(float x)
{
    return x * 3.14159265358979f / 180.0;
}

//vector len
float v_len(sf::Vector3f v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//vector normalisation 
sf::Vector3f v_norm(sf::Vector3f v) 
{
    float len = v_len(v);
    v = v * (1 / len);
    return v;
}

using namespace std;
int main() {
    
    //screen width and height
    int w = 1280;
    int h = 720;

    //PI const
    const float  pi_f = 3.14159265358979f;

    //creating a window. sf::Style::Fullscreen - to full screen, sf::Style::Titlebar - has a name, sf::Style::Close - you can close
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", sf::Style::Titlebar | sf::Style::Close);
    
    //FPS limit
    window.setFramerateLimit(60);

    //FOV
    float FOV_deg = 90.0f;

    //camera start position
    sf::Vector3f camera(-5.0f, 0.0f, 0.0f);
    
    //camera direction
    sf::Vector3f dir_cam(1.0f, 0.0f, 0.0f);

    //matrix of vectors
    sf::Vector3f** vecs = new sf::Vector3f* [w];
    for (int i = 0; i < w; i++)
    {
        vecs[i] = new sf::Vector3f[h];
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            vecs[i][j].x = 5.0f;
            vecs[i][j].y = i - (w / 2);
            vecs[i][j].z = j - (h / 2);
            vecs[i][j] = v_norm(vecs[i][j]);
        }
    }

    sf::Uint8* pixels = new sf::Uint8[w * h * 4];

    sf::Texture texture;
    texture.create(w, h);

    sf::Sprite sprite(texture);

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w * 4; i += 4) {
            pixels[w * j * 4 + i] = i / 4 * 256 / w;
            pixels[w * j * 4 + i + 1] = j * 256 / h;
            pixels[w * j * 4 + i + 2] = 0;
            pixels[w * j * 4 + i + 3] = 255;
        }
    }
    
    texture.update(pixels);

    //window operation cycle
    while (window.isOpen()) {   
        
        //setting the loop variable
        sf::Event event;
        
        //checking all events per cycle
        while (window.pollEvent(event)) {
            
            //closing request
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //clear the window
        window.clear();
        
        window.draw(sprite);

        //paint over the window (display a picture)
        window.display();
    }
 
    //delete pixels in memory
    for (int i = 0; i < w; i++)
    {
        delete[]vecs[i];
    }
    delete[]vecs;


    return 0;
}