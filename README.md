# Ray Casting Project
## Курсовая работа Игоря Мельникова 1142
Данная программа будет являтся рендером графики на ПК с помощью метода Ray Casting, где используется библиотека SFML.

#
## Версия 0.0: Базовая программа
Нулевая версия включает в себя простую программу для открытия окна 1280x720.

#
## Версия 0.1: Английские комментарии
- Переход на латынь

#
## Версия 0.2: Вывод градиента и подготовка лучей
- Выполнен алгоритм выведение градиента, показывающая зависимость цвета от координат на плоскости экрана.
- Создана матрица векторов.
- Созданы функции вычисления длины векторов и их нормирования.

Картинка 1. Градиент зависимости цвета от координат. 
![image](https://user-images.githubusercontent.com/68777353/162453295-7d37e82a-194e-45e4-93d8-44866831c61d.png)

 #
 ## Версия 0.3: Базовый функционал Ray Casting
 - Реализован алгоритм рендера треугольника.
 - Добавлено движение камеры на WASD LShift и Space.
 - Для работы с векторами добавлено больше функций, как их скалярное и векторное произведения и др.

Картинка 2. Рендер треугольника в программе
![raycast](https://user-images.githubusercontent.com/68777353/167572396-ea7efa12-fd6f-48c4-aee1-cea327de003a.gif)

#
## Версия 0.3.1: "Правильный" Ray Casting
- Был пофикшен баг с отображением треугольника позади камеры.

#
## Версия 0.4: Вывод нескольких фигур
- Добавлена возможность поддержки нескольких фигур (пока только статичным способом).

Картинка 3. Рендер 2 треугольников и прямоуголника между ними (состоит из 2 треугольников)
![image](https://user-images.githubusercontent.com/68777353/167726958-19293940-8572-4df1-8c05-d7ca85d7b1c0.png)

#
## Версия 0.5: Усовершенствование кода
- Векторные функции, а также класс треуголников были вынесены отдельными файлами вне кода.
- Устранена утечка данных (не удалялся массив pixels).
- Восстановление русских комментариев, а также комментирование многих пунктов в коде для понимания.

#
## Версия 0.6: Модифицированный код
- Теперь все треугольники хранятся в одном векторе, что способствует возможности добавлению новых треугольников во время работы программы!
- Реализовано отображение расположения камеры, а также количества треугольников в программе (за счёт первого пункта).
- Создано второе окно, где будет напечатано управление программой.

Картинка 4. Рендер 2 треугольников и прямоуголника между ними, с указанием расположения камеры а также общего количества треугольников.
![image](https://user-images.githubusercontent.com/68777353/169150737-81079b4e-9d3f-425d-a54f-64b870ae0cb5.png)

#
## Версия 0.7: Любое количество треугольников
- Появилась возможность добавлять новые и удалять старые треуголники пользоывателю!
- Добавлено окно с помощью в управлении программой.

Картинка 5. Работа с программой.

![Курсач](https://user-images.githubusercontent.com/68777353/169506487-827e7675-0511-4778-9d0a-048c55cc9f65.gif)
