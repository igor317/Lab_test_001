#ifndef MAZE_H
#define MAZE_H
#include "DArray.h"
#include <random>
#include <time.h>
struct Point    // Структура точки (X и Y)
{
	int x;
	int y;
};
struct Position // Структура позиции
{
	Point coord;// Координаты (X и Y)
	int vector; // направление(для определения направление поворота(угла))
};
struct Neighbor // Структура соседей(для проверки клетки на доступность)
{
	Point coord;// Координаты (X и Y)
	char access; // доступ
	int vector; // направление
};

class Maze{
private:
	DArray* mass;				// Карта
	Point size;					// Размер карты
	Point entry;				// Позиция входа
	Point exit;					// Позиция выхода
	Point* freepoints;			// координаты пустых клеток

	int maxtry;					// Максимальное количество попыток прохода (решение проблемы зацикливания\тупика)
	int steps;					// Количество шагов
	int randcount;				// Количество попыток рандома
	int _error;					// Ошибки (0 - нет ошибок/1 - зациклился/2 - нашел выход)
	int minst;					// Минимальное кол-во шагов
	int attempts;				// Количество попыток

	Position curpos;			// Текущая позиция
	Neighbor neighb[4];			// Соседи

	void FillMass();		// Заполнение массива(создание шаблона карты)
	void GenIn();// Генерация позиции входа
	void GenOut();			// Генерация позиции выхода
	void FindNeigh();		// Поиск соседей текущей позиции
	void GenStep();						// Генерация пути(шаг)
	void FindFreePoints();				// Поиск пустых клеток
public:
	Maze(int x, int y, int minsteps);	// Конструктор класса
	~Maze();							// Деструктор класса
	void GenWay();						// Генерация пути
	int GetSteps();						// Получить количество шагов
	int GetAttemps();					// Получить количество попыток
	char WriteArr(int x, int y);		// Вывод точки массива(карты)

	int zerocounts;				// Кол-во пустых клеток
};
#endif