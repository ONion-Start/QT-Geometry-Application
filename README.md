# Geometry Application

Geometry Application — это программа, демонстрирующая использование базового и производных классов для работы с геометрическими фигурами, такими как точки, круги и цилиндры. Она предоставляет графический интерфейс для генерации данных, их обработки и сохранения в текстовом и бинарном форматах.

## Описание проекта

Программа позволяет:

1. Создавать объекты класса Point (точки), Circle (круги) и Cylinder (цилиндры).
2. Рассчитывать характеристики фигур, такие как площадь, периметр и объём.
3. Генерировать случайные данные для фигур и отображать их в таблице.
4. Сохранять данные в текстовый файл или бинарный файл.
5. Очищать таблицу данных.

## Основные функции

### Генерация элементов

- Создание случайных объектов фигур с их характеристиками:
  - Координаты X и Y для точек.
  - Радиус для кругов.
  - Радиус и высота для цилиндров.

### Расчёты

- Для **Circle**:
  - Площадь: \( \pi r^2 \).
  - Периметр: \( 2\pi r \).

- Для **Cylinder**:
  - Площадь: \( 2\pi r(r + h) \).
  - Объём: \( \pi r^2 h \).

### Сохранение данных

- **Текстовый формат**: Сохранение данных в файл `data.txt`.
- **Бинарный формат**: Сохранение данных в файл `data.bin`.

### Очистка

- Удаление всех данных из таблицы.

## Используемые технологии

- **C++**: Язык программирования для основной логики приложения.
- **Qt Framework**: Создание графического интерфейса.

## Сборка и запуск

### Требования

- Qt версии 5.12 или выше.
- Компилятор, поддерживающий стандарт C++11 или выше.

### Инструкции по сборке

1. Склонируйте репозиторий:
   ```bash
   git clone [https://github.com/<ваш-репозиторий>/geometry-application.git](https://github.com/ONion-Start/QT-Geometry-Application)
   ```

2. Откройте проектный файл в Qt Creator.

3. Соберите и запустите проект.

## Как использовать

1. Запустите приложение.
2. Нажмите "Сгенерировать элементы" для генерации случайных фигур и их характеристик.
3. Нажмите "Занести в текстовый файл" для сохранения данных в формате текста (`data.txt`).
4. Нажмите "Занести в бинарный файл" для сохранения данных в бинарном формате (`data.bin`).
5. Нажмите "Очистить поле ввода" для очистки таблицы.
6. Используйте кнопку "Help" для получения справочной информации о функциональности приложения.

## Пример данных

| X       | Y       | Radius | Height | Type     | Area    | Perimeter | Volume |
|---------|---------|--------|--------|----------|---------|-----------|--------|
| 12.34   | -45.67  | 10.0   | 20.0   | Cylinder | 1884.96 | N/A       | 6283.19|
| -23.45  | 67.89   | 5.0    | N/A    | Circle   | 78.54   | 31.42     | N/A    |

## Лицензия

Проект распространяется под лицензией MIT. Подробнее см. файл LICENSE.



