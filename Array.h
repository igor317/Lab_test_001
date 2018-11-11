/*
0 - Пустая клетка
1 - Коридор прямо
6 - Поворот влево
7 - Поворот вправо
2 - Вход
3 - Выход
8 - Внешняя стена
9 - Запрещенная клетка (в углах)
*/
#ifndef ARRAY_H
#define ARRAY_H
struct Position 
{
	int x;
	int y;
	int vector;
	int color;
};
struct Neigh 
{
	int x;
	int y;
	int access;
	int vector;
};

class Arr
{
private:
	int _x;
	int _y;
	int randX_in, randY_in;
	int randX_out, randY_out;
	int** mass;
	int maxtry;
	int count;
	Position curpos;
	Neigh neighb[4];

	void Create_arr();
	void FillMass();
	void GenIn();
	void GenOut();
	void FindNeigh();
	void Regenerate();



public:
	Arr(int x, int y);
	~Arr();
	int WriteArr(int x,int y);
	void GenWay();
	Position GetPosition();
	void test();
};

#endif