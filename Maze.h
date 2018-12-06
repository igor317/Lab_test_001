#ifndef MAZE_H
#define MAZE_H
#include "DArray.h"
#include <random>
#include <time.h>
struct Decoder
{
	std::string decode;
	char encode;
};
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
	char vector; // направление
};

class Maze{
private:
	DArray* mass;				// Карта
	DArray* dubmass;			// Дубликат карты (для создания коридоров)
	Point size;					// Размер карты
	Point entry;				// Позиция входа
	Point exit;					// Позиция выхода
	Point* freepoints;			// координаты пустых клеток

	int maxtry;					// Максимальное количество попыток прохода (решение проблемы зацикливания\тупика)
	int steps;					// Количество шагов
	int randcount;				// Количество попыток рандома

	int minst;					// Минимальное кол-во шагов
	int attempts;				// Количество попыток


	Position curpos;			// Текущая позиция
	Neighbor neighb[4];			// Соседи
	Decoder dec[12];
	Decoder othdec[12];

	void FillDecoder();			// Заполнить таблицу

	void FillMass();		// Заполнение массива(создание шаблона карты)
	void GenIn();// Генерация позиции входа
	void GenOut();			// Генерация позиции выхода
	void FindNeigh();		// Поиск соседей текущей позиции
	void GenStep();						// Генерация пути(шаг)
	void FindFreePoints();				// Поиск пустых клеток
	char FindCode(std::string code,Decoder* dec);
	void ReplaceMap(DArray* from, DArray* to);
	void rmp();
public:
	Maze(int x, int y, int minsteps);	// Конструктор класса
	~Maze();							// Деструктор класса
	void GenWay();						// Генерация пути
	int GetSteps();						// Получить количество шагов
	int GetAttemps();					// Получить количество попыток
	char WriteArr(int x, int y);		// Вывод точки массива(карты)
	void GenInOther();					// Генерация входа на пустой клетке
	void GenOtherStep();
	int zerocounts;				// Кол-во пустых клеток

	int _error;					// Ошибки (0 - нет ошибок/1 - зациклился/2 - нашел выход)
};
#endif