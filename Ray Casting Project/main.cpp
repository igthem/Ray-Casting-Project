#include <SFML/Graphics.hpp> //Library for working with graphics "sf::"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

//scalar multiplication
float v_mul(sf::Vector3f a, sf::Vector3f b)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z);
}
//deg2rad
float deg2rad(float x)
{
    return x * 3.14159265358979f / 180.0f;
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

//vector multiplication
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

class Triangle {
private:
        sf::Vector3f p0, p1, p2, colour, norm;
public:
    //constructor
    Triangle(const sf::Vector3f& a, const sf::Vector3f& b, const sf::Vector3f& c, const sf::Vector3f d)
    {
        p0 = a;
        p0.z = -p0.z;
        p1 = b;
        p1.z = -p1.z;
        p2 = c;
        p2.z = -p2.z;
        colour = d;

        norm = v_cross(p1-p0, p2-p0);
    }
    //destructor
    ~Triangle() {}

    float intersect(sf::Vector3f ro, sf::Vector3f rd) //ro - camera position; rd - ray from camera
    {
        sf::Vector3f v1v0 = p1 - p0;
        sf::Vector3f v2v0 = p2 - p0;
        sf::Vector3f rov0 = ro - p0;
        sf::Vector3f  q = v_cross(rov0, rd);
        float d = 1.0f / v_mul(rd, norm); 
        float u = d * v_mul(-q, v2v0);
        float v = d * v_mul(q, v1v0);
        float t = d * v_mul(-norm, rov0);
        if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t < 0.0f)
            t = -1.0f; 
        //sf::Vector3f e(t, u, v);
        return t;
    }
    float r()
    {
        return colour.x;
    }
    float g()
    {
        return colour.y;
    }
    float b()
    {
        return colour.z;
    }
    sf::Vector3f rgb()
    {
        return colour;
    }
};

//start ----------------------------------------------------------------------------------------------------------------------
using namespace std;
int main() {

    //screen width and height
    int w = 1280;
    int h = 720;

    //PI const
    const float  pi_f = 3.14159265358979f;

    //creating a window. sf::Style::Fullscreen - to full screen, sf::Style::Titlebar - has a name, sf::Style::Close - you can close
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", /*sf::Style::Fullscreen |*/ sf::Style::Titlebar | sf::Style::Close);

    //FPS limit
    window.setFramerateLimit(60);

    //FOV
    float FOV_deg = 90.0f;

    float speed = 0.1f;

    //camera start position
    sf::Vector3f cam(-10.0f, 0.0f, 0.0f);

    //camera direction
    sf::Vector3f dir_cam(1.0f, 0.0f, 0.0f);

    //triangle ---------------------------------------------------------------------------------------------------------------
    
    //number of triangles
    const int c_triangles = 4;

    float* v_dt = new float [c_triangles];
    sf::Vector3f* v_dc = new sf::Vector3f[c_triangles];
    
    //colour vec
    sf::Vector3f colour1(255.0f, 0.0f, 0.0f); // 0.0 <= colour < 255.0 (r,g,b)
    sf::Vector3f colour2(0.0f, 255.0f, 0.0f);
    sf::Vector3f colour3(0.0f, 0.0f, 255.0f);
    
    Triangle t1(sf::Vector3f { 0.0f, 5.0f, 0.0f }, sf::Vector3f { 0.0f, 0.0f, 5.0f }, sf::Vector3f { 5.0f, 0.0f, 0.0f }, colour1);
    Triangle t2(sf::Vector3f { 6.0f, -2.0f, 0.0f }, sf::Vector3f { 6.0f, 6.0f, 0.0f }, sf::Vector3f { 10.0f, 0.0f, 6.0f }, colour2);
    Triangle t3(sf::Vector3f{ 4.0f, -4.0f, 4.0f }, sf::Vector3f{ 4.0f, -4.0f, 2.0f }, sf::Vector3f{ 5.0f, 4.0f, 4.0f }, colour3);
    Triangle t4(sf::Vector3f{ 4.0f, -4.0f, 2.0f }, sf::Vector3f{ 5.0f, 4.0f, 4.0f }, sf::Vector3f{ 5.0f, 4.0f, 2.0f }, colour3);

    Triangle trs[c_triangles] = { t1, t2, t3, t4 };

    // -----------------------------------------------------------------------------------------------------------------------
    //matrix of vectors
    sf::Vector3f** vecs = new sf::Vector3f * [w];
    for (int i = 0; i < w; i++)
    {
        vecs[i] = new sf::Vector3f[h];
    }
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            vecs[i][j].x = w / sqrt(2);
            vecs[i][j].y = i - (w / 2);
            vecs[i][j].z = j - (h / 2);
            vecs[i][j] = v_norm(vecs[i][j]);
        }
    }

    //pixels
    sf::Uint8* pixels = new sf::Uint8[w * h * 4];

    //texture
    sf::Texture texture;
    texture.create(w, h);

    //sprite
    sf::Sprite sprite(texture);

    //window operation cycle -------------------------------------------------------------------------------------------------
    while (window.isOpen()) {

        //setting the loop variable
        sf::Event event;

        //checking all events per cycle
        while (window.pollEvent(event)) {

            //closing request
            if (event.type == sf::Event::Closed)
                window.close();

            //controls
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    break;
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    cam.x += speed;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    cam.y -= speed;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    cam.x -= speed;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    cam.y += speed;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    cam.z -= speed;
                }
                else if (event.key.code == sf::Keyboard::LShift)
                {
                    cam.z += speed;
                }
            }
        }

        //checking 
        for (int j = h - 1; j >= 0; j--)
        {
            for (int i = 0; i < w * 4; i += 4)
            {
                for (int c = 0; c < c_triangles; c++)
                {
                    v_dt[c] = trs[c].intersect(cam, vecs[i / 4][j]);
                }
                float max_t = v_dt[0];
                int count = 0; //если поставить -1, то будет интересный баг
                for (int k = 0; k < c_triangles; k++)
                {
                    if (v_dt[k] > max_t)
                    {
                        max_t = v_dt[k];
                        count = k;
                    }
                }
                
                if (max_t == -1.0f)
                {
                    pixels[w * j * 4 + i] = 255;
                    pixels[w * j * 4 + i + 1] = 255;
                    pixels[w * j * 4 + i + 2] = 255;
                    pixels[w * j * 4 + i + 3] = 255;
                }
                else
                {
                    float min_t = max_t;
                    for (int k = 0; k < c_triangles; k++)
                    {
                        if (v_dt[k] < min_t && v_dt[k] >= 0.0f)
                        {
                            min_t = v_dt[k];
                            count = k;
                        }
                    }
                    
                    pixels[w * j * 4 + i] = trs[count].r();
                    pixels[w * j * 4 + i + 1] = trs[count].g();
                    pixels[w * j * 4 + i + 2] = trs[count].b();
                    float a = 55 + 200.0f / min_t * 10.0f;
                    if (a <= 255.0f)
                        pixels[w * j * 4 + i + 3] = a;
                    else
                        pixels[w * j * 4 + i + 3] = 255;
                }
            }
        }

        //updating texture
        texture.update(pixels);

        //clear the window
        window.clear();
        
        //draw
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

    delete[] v_dt;
    delete[] v_dc;

    return 0;
}