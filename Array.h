/*
ДОСТУП:
	0 - Пустая клетка
	1 - Коридор прямо
	2 - Вход
	3 - Выход
	6 - Поворот против ч.с.
	7 - Поворот по ч.с.
	8 - Внешняя стена
	9 - Запрещенная клетка (в углах)
*/
#ifndef ARRAY_H
#define ARRAY_H

struct Position // Структура позиции
{
	int x;
	int y;
	int vector; // направление(для определения направление поворота(угла))
};
struct Neighbor // Структура соседей(для проверки клетки на доступность)
{
	int x;
	int y;
	int access; // доступ
	int vector;
};

class Arr
{
private:
	int _x;						// Строки
	int _y;						// Столбцы
	int randX_in, randY_in;		// позиция входа
	int randX_out, randY_out;	// позиция выхода
	int** mass;					// Карта
	int maxtry;					// Максимальное количество попыток прохода (решение проблемы зацикливания\тупика)
	int steps;					// Количество шагов
	int count;					// Количество попыток прохода
	int _error;					// Ошибки (0 - нет ошибок/1 - зациклился/2 - нашел выход)
	int minsteps;				// Минимальное кол-во шагов

	Position curpos;	// Текущая позиция
	Neighbor neighb[4]; // Соседи

	void Create_arr();	// Создание массива
	void FillMass();	// Заполнение массива(создание шаблона карты)
	void GenIn();		// Генерация позиции входа
	void GenOut();		// Генерация позиции выхода
	void FindNeigh();	// Поиск соседей текущей позиции

public:
	Arr(int x, int y, int minsteps);	// Конструктор класса
	~Arr();								// Деструктор класса
	int WriteArr(int x,int y);			// Вывод точки массива(карты)
	int GetSteps();						// Получить количество шагов
	int GetError();						// Получить ошибку
	void GenWay();						// Генерация пути (шаг)
	void SetSteps(int steps);			// Установить количество шагов
};

#endif
