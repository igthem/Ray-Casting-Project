#include <SFML/Graphics.hpp> // Библиотека для работы с графикой "sf::"
#include <SFML/Window.hpp>
#include "VecFunctions.h" // Функции для работы с векторами
#include "Triangle.h" // Класс треугольников
#include "Render.h" // Просчёт и отрисовка пикселей
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Функция для превращения в String число типа float с округлением до 1 знака после запятой
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
        if (x >= 0) x+=1;
        else x-=1;
    }
    return (minus + to_string((int)x) + '.' + to_string(xx));
}

// Функция создания нового треугольника
void new_triangle(vector<Triangle> &triangles)
{
    cout << "----------------------------------------" << endl;
    
    sf::Vector3i rgb;
    sf::Vector3f point1, point2, point3;

    cout << "New Triangle!!!\nEnter colour (red green blue) (in range from 0 to 255):\n";
    cin >> rgb.x >> rgb.y >> rgb.z;
    cout << "\n";
    cout << "Enter first point (x y z):\n";
    cin >> point1.x >> point1.y >> point1.z;
    cout << "\n";
    cout << "Enter second point (x y z):\n";
    cin >> point2.x >> point2.y >> point2.z;
    cout << "\n";
    cout << "Enter third point (x y z):\n";
    cin >> point3.x >> point3.y >> point3.z;

    if (point1 == point2 || point1 == point3 || point3 == point2)
    {
        cout << "Triangles, not lines or points!!!\n";
        cin;
    }
    else
    {
        triangles.push_back(Triangle(point1, point2, point3, rgb));
    }
}

// Старт ---------------------------------------------------------------------------------------------
int main() {
    cout << "Made by Melnikov Igor 1142\n";

    // Ширина экрана
    int w = 1280;
    // Высота экрана
    int h = 720;

    // Ширина экрана для экрана помощи
    int w2 = 850;
    // Высота экрана для экрана помощи
    int h2 = 380;

    // Создание окна. sf::Style::Fullscreen - полный экран, sf::Style::Titlebar - наличие имени окна, 
    // sf::Style::Close - возможность закрыть окно
    sf::RenderWindow window(sf::VideoMode(w, h), "RayCasting", sf::Style::Titlebar | sf::Style::Close);
    sf::RenderWindow help(sf::VideoMode(w2, h2), "Help", sf::Style::Titlebar);

    // Ограничение кадров в секунду
    window.setFramerateLimit(60);

    // Скорость камеры
    float speed = 0.1f;

    // Начальная позиция камеры
    sf::Vector3f cam(-10.0f, 0.0f, 0.0f);

    // Установка шрифта
    sf::Font font;
    font.loadFromFile("UbuntuBold-1YyB.ttf");

    // Вектор треугольников
    vector <Triangle> triangles;

    // Матрица векторов 
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
        xyz_text.setOutlineColor(sf::Color::White);
        xyz_text.setOutlineThickness(1);
        xyz_text.setPosition(w/100, h/100);

        // Получаем количество треугольников в виде текста
        sf::Text count_triangles("Triangles: " + to_string(triangles.size()), font);
        count_triangles.setFillColor(sf::Color::Black);
        count_triangles.setOutlineColor(sf::Color::White);
        count_triangles.setOutlineThickness(1);
        count_triangles.setPosition( w / 100, h - h / 15 );

        // Скорость камеры в виде текста
        sf::Text speed_text("Speed: " + roundTo2(speed), font);
        speed_text.setFillColor(sf::Color::Black);
        speed_text.setOutlineColor(sf::Color::White);
        speed_text.setOutlineThickness(1);
        speed_text.setPosition(w - w / 7 - 15, h/100);

        // Текс для экрана помощи
        sf::Text help_text(L"Управление программой : \n\nWASD - перемещение по осям oX oY; \n"
            "SpaceBar и LShift - подъём и спуск;\nBackspace - удалить последний треугольник;\n"
            "E - увеличить скорость камеры;\nQ - уменьшить скорость камеры;\n"
            "Enter - добавить новый треуголник\n(нужно будет открыть консоль и ввести значения);\n"
            "Пример ввода в консоль значений: '152 -65 18' ", font);
        help_text.setFillColor(sf::Color::White);
        help_text.setPosition(w2 / 100, h2 / 100);

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
                else if (event.key.code == sf::Keyboard::E) // Увеличить скорость
                {
                    if (speed < 100.0f)
                        speed = speed * 10;
                }
                else if (event.key.code == sf::Keyboard::Q) // Уменьшить скорость
                {
                    if (speed > 0.1f)
                        speed = speed / 10;
                }
                else if (event.key.code == sf::Keyboard::Enter) // Добавить треугольник
                {
                    // Текст с предупреждением об создании нового треугольника
                    sf::Text warning(L"Откройте командную строку!", font);
                    warning.setFillColor(sf::Color::Red);
                    warning.setOutlineColor(sf::Color::Black);
                    warning.setOutlineThickness(5);
                    warning.setPosition(w / 50, h / 2 - h / 8);
                    warning.setCharacterSize(75);
                    window.draw(warning);
                    window.display();

                    // Получаем значения для треугольника
                    new_triangle(triangles);
                }
                else if (event.key.code == sf::Keyboard::BackSpace) // Удалить последний треугольник
                {
                    if (triangles.size() > 0)
                    {
                        triangles.pop_back();
                    }
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

        // Просчёт каждого векторого на наличие пересечений
        render(pixels, triangles, w, h, cam, vecs);
        
        // Обновление текстуры
        pixels_texture.update(pixels);

        // Очистка окна
        window.clear();
        help.clear();

        // Отрисовываем спрайт и текст для экрана помощи
        window.draw(pixels_sprite);
        help.draw(help_text);
        
        // Отрисовка текста с координатами, кол-вом треуголников и скоростью
        window.draw(xyz_text);
        window.draw(count_triangles);
        window.draw(speed_text);
        
        // Отображаем экран
        help.display();
        window.display();
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