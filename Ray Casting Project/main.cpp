#include <SFML/Graphics.hpp> // Библиотека для работы с графикой "sf::"
#include <SFML/Window.hpp>
#include "VecFunctions.h" // Функции для работы с векторами
#include "Triangle.h" // Класс треугольников
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Функция для превращения в String числа с округлением до 1 знака после запятой
string roundTo2(float x)
{
    string minus;
    if (x < 0)
        minus = "-";
    x = abs(x);
    float n;
    float y = modf(x, &n);
    int xx = (int)round(abs((x - n) * 10));
    if (xx == 10)
    {
        xx = 0;
        if (x >= 0) x++;
        else x--;
    }
    return (minus + to_string((int)x) + '.' + to_string(xx));
}

// Старт ---------------------------------------------------------------------------------------------
int main() {

    // Ширина и высота жкрана
    int w = 1280;
    int h = 720;

    // Число ПИ
    const float  pi_f = 3.14159265358979f;

    // Создание окна. sf::Style::Fullscreen - полный экран, sf::Style::Titlebar - наличие имени окна, 
    // sf::Style::Close - возможность закрыть окно
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", 
        /*sf::Style::Fullscreen |*/ sf::Style::Titlebar | sf::Style::Close);
    sf::RenderWindow help(sf::VideoMode(500, 500), "Help", sf::Style::Titlebar);

    // Ограничение кадров в секунду
    window.setFramerateLimit(60);

    // Скорость камеры
    float speed = 0.1f;

    // Начальная позиция камеры
    sf::Vector3f cam(-10.0f, 0.0f, 0.0f);

    // Направление камеры
    sf::Vector3f dir_cam(1.0f, 0.0f, 0.0f);

    // Установка шрифта
    sf::Font font;
    font.loadFromFile("UbuntuBold-1YyB.ttf");

    // Треугольники -----------------------------------------------------------------------------------

    // Вектор треугольников
    vector <Triangle> triangles;

    // Количество треугольников
    const int c_triangles = 4;

    // Вектора цветов
    sf::Vector3i colour1(255, 0, 0); // 0.0 <= colour < 255.0 (r,g,b)
    sf::Vector3i colour2(0, 255, 0);
    sf::Vector3i colour3(0, 0, 255);

    // Создание треугольников 
    Triangle t1(sf::Vector3f{ 0.0f, 5.0f, 0.0f }, sf::Vector3f{ 0.0f, 0.0f, 5.0f }, 
        sf::Vector3f{ 5.0f, 0.0f, 0.0f }, colour1);
    Triangle t2(sf::Vector3f{ 6.0f, -2.0f, 0.0f }, sf::Vector3f{ 6.0f, 6.0f, 0.0f }, 
        sf::Vector3f{ 10.0f, 0.0f, 6.0f }, colour2);
    Triangle t3(sf::Vector3f{ 4.0f, -4.0f, 4.0f }, sf::Vector3f{ 4.0f, -4.0f, 2.0f }, 
        sf::Vector3f{ 5.0f, 4.0f, 4.0f }, colour3);
    Triangle t4(sf::Vector3f{ 4.0f, -4.0f, 2.0f }, sf::Vector3f{ 5.0f, 4.0f, 4.0f }, 
        sf::Vector3f{ 5.0f, 4.0f, 2.0f }, colour3);

    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);

    // Вектор расстояний пересечений
    vector <float> v_dt;

    // Матрица векторов ------------------------------------------------------------------------------
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

    // Массив пикселей
    sf::Uint8* pixels = new sf::Uint8[w * h * 4];

    // Текстура
    sf::Texture pixels_texture;
    pixels_texture.create(w, h);

    // Спрайт
    sf::Sprite pixels_sprite(pixels_texture);

    // Цикл открытого окна ---------------------------------------------------------------------------
    while (window.isOpen()) {

        // Получаем положение камеры в виде текста
        sf::Text xyz_text("x: " + roundTo2(cam.x) + "\ny: " + roundTo2(cam.y) + 
            "\nz :" + roundTo2(-cam.z), font);
        xyz_text.setFillColor(sf::Color::Black);
        xyz_text.setPosition(w/100, h/100);

        // Получаем количество треугольников в виде текста
        sf::Text count_triangles("Triangles: " + to_string(triangles.size()), font);
        count_triangles.setFillColor(sf::Color::Black);
        count_triangles.setPosition( w / 100, h - h / 15 );

        // Задание параметра события
        sf::Event event;

        // Проверка всех возможных событий
        while (window.pollEvent(event)) {

            // Запрос закрытия экрана
            if (event.type == sf::Event::Closed)
                window.close();

            // Управление клавишами
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) // Выход
                {
                    window.close();
                    break;
                }
                else if (event.key.code == sf::Keyboard::W) // Вперёд
                {
                    cam.x += speed;
                }
                else if (event.key.code == sf::Keyboard::A) // Влево
                {
                    cam.y -= speed;
                }
                else if (event.key.code == sf::Keyboard::S) // Назад
                {
                    cam.x -= speed;
                }
                else if (event.key.code == sf::Keyboard::D) // Вправо
                {
                    cam.y += speed;
                }
                else if (event.key.code == sf::Keyboard::Space) // Вверх
                {
                    cam.z -= speed;
                }
                else if (event.key.code == sf::Keyboard::LShift) // Вниз
                {
                    cam.z += speed;
                }
            }
        }

        // Проверка пересечений (переделать отдельным файлом в дальнейшем)
        for (int j = h - 1; j >= 0; j--)
        {
            for (int i = 0; i < w * 4; i += 4)
            {
                for (int c = 0; c < triangles.size(); c++)
                {
                    // Сохраняем все возможные пересечения со всеми треугольниками, 
                    // где значение - расстояние до точки пересечения
                    v_dt.push_back(triangles[c].intersect(cam, vecs[i / 4][j])); 
                }
                float max_t = v_dt[0]; // Выбор первого элемента, предпологая что он не наибольший.
                int count = 0; // Задаём начальный индекс элементов.

                // Поиск наибольшего элемента в массиве. Если нет пересечений, то выше -1.0f не поднимется, 
                // иначе мы найдём хоть какое-то верное значение.
                for (int k = 0; k < triangles.size(); k++)
                {
                    if (v_dt[k] > max_t)
                    {
                        max_t = v_dt[k];
                        count = k;
                    }
                }

                if (max_t == -1.0f) // Если нет ни одного пересечения
                {
                    pixels[w * j * 4 + i] = 255;
                    pixels[w * j * 4 + i + 1] = 255;
                    pixels[w * j * 4 + i + 2] = 255;
                    pixels[w * j * 4 + i + 3] = 255;
                }
                else // Если есть хоть 1 пересечение
                {
                    float min_t = max_t;

                    // Ищем наименьшую длину, исключая неверные значения
                    for (int k = 0; k < triangles.size(); k++) 
                    {
                        if (v_dt[k] < min_t && v_dt[k] >= 0.0f)
                        {
                            min_t = v_dt[k];
                            count = k;
                        }
                    }

                    // Закраска пикселя соответственно с подходящим пересечением
                    pixels[w * j * 4 + i] = triangles[count].r();
                    pixels[w * j * 4 + i + 1] = triangles[count].g();
                    pixels[w * j * 4 + i + 2] = triangles[count].b();
                    float a = 55 + 200.0f / min_t * 10.0f;
                    if (a <= 255.0f)
                        pixels[w * j * 4 + i + 3] = a;
                    else
                        pixels[w * j * 4 + i + 3] = 255;
                }
                v_dt.clear();
            }
        }

        // Обновление текстуры
        pixels_texture.update(pixels);

        // Очистка окна
        window.clear();
        help.clear();

        // Отрисовываем спрайт и текста
        window.draw(pixels_sprite);
        window.draw(xyz_text);
        window.draw(count_triangles);
        
        // Отображаем экран
        window.display();
        help.display();
    }

    // Очистка кода
    for (int i = 0; i < w; i++)
    {
        delete[]vecs[i];
    }
    delete[]vecs;
    delete[]pixels;

    return 0;
}