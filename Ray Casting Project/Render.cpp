#include "Render.h"

// Функция для закрашивания пикселя
void drawing(sf::Uint8*& pixels, int i, int j, sf::Vector3i colour, float t, int screen_width)
{
    pixels[screen_width * j * 4 + i] = colour.x;
    pixels[screen_width * j * 4 + i + 1] = colour.y;
    pixels[screen_width * j * 4 + i + 2] = colour.z;

    // Эффект затемнения при отдалении
    float a = 55 + 200.0f / t * 10.0f;
    if (a <= 255.0f)
        pixels[screen_width * j * 4 + i + 3] = a;
    else
        pixels[screen_width * j * 4 + i + 3] = 255;
}

// Функция рендера
void render(sf::Uint8* &pixels, std::vector<Triangle> triangles, int screen_width, int screen_high, 
    sf::Vector3f cam, sf::Vector3f** vecs)
{
    // Проверка пересечений каждого вектора относительно пикселей
    for (int j = 0; j < screen_high; j++)
    {
        for (int i = 0; i < screen_width * 4; i += 4)
        {
            // Если нет треугольников
            if (triangles.size() < 1)
            {
                drawing(pixels, i, j, sf::Vector3i(255, 255, 255), 0, screen_width);
                continue;
            }

            // Вектор расстояний пересечений
            std::vector <float> v_dt;

            // Сохраняем все возможные пересечения со всеми треугольниками, 
            // где значение - расстояние до точки пересечения
            for (int c = 0; c < triangles.size(); c++)
            {
                v_dt.push_back(triangles[c].intersect(cam, vecs[i / 4][j]));
            }

            // Выбор первого элемента, предполагая что он не наибольший.
            float max_t = v_dt[0];

            // Задаём начальный индекс элементов.
            int count = 0; 

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

            // Если нет ни одного пересечения (т.е. наибольшое значение = -1)
            if (max_t == -1.0f) 
            {
                drawing(pixels, i, j, sf::Vector3i(255,255,255), 0, screen_width);
            }
            else // Если есть хоть 1 пересечение
            {
                // Предполагаем, что наибольший элемент является одновременно наименьшим
                // Так мы избавляемся от ошибки 
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
                drawing(pixels, i, j, triangles[count].rgb(),
                    min_t, screen_width);
            }
        }
    }
}