#include "Array.h"
#include <time.h>
#include <iostream>
#include <random>
Arr::Arr(int x, int y,int minsteps) // Констурктор класса /////////////////////////////////////////
{
	srand(static_cast<unsigned int>(time(0))); // зерно рандома
	_x = x;
	_y = y;									  
	maxtry = 10;
	_error = 0;
	SetSteps(minsteps); // Минимум шагов 
	Create_arr();
	FillMass();
}

Arr::~Arr() // Деструктор класса /////////////////////////////////////////////////////
{
	for (int i = 0; i<_x; i++)
		delete[] mass[i];
	delete[] mass;
}

void Arr::Create_arr() // Создание массива ////////////////////////////////////////////
{
	mass = new int*[_x];
	for (int j = 0; j < _x; j++) {
		mass[j] = new int[_y];
	}
}

void Arr::FillMass()  // Заполнение массива ///////////////////////////////////////////
{
	for (int j = 0; j < _y; j++) {
		for (int i = 0; i < _x; i++) {
			mass[i][j] = 0;
			if (i == 0 || i == _x - 1 || j == 0 || j == _y - 1)
				mass[i][j] = 8;
			mass[0][0] = 9;
			mass[0][_y - 1] = 9;
			mass[_x - 1][0] = 9;
			mass[_x - 1][_y - 1] = 9;
		}
	}
	GenIn();
	GenOut();
	mass[randX_in][randY_in] = 2;
	mass[randX_out][randY_out] = 3;
}

void Arr::GenIn() // Генерация позиции входа ///////////////////////////////////////////
{
	randX_in = 0;
	randY_in = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, _x - 1);
	randX_in = dist(gen);
	//randX_in = rand() % (_x);
	if (randX_in == 0 || randX_in == _x - 1) 
	{
		std::uniform_int_distribution<> dist(0, _y - 1);
		while (randY_in == 0 || randY_in == _y - 1) 
		{
			randY_in = dist(gen);
			//randY_in = rand() % (_y);
		}
	}
	else
	{
		int a = 0;
		std::uniform_int_distribution<> dist(0, 1);
		a = dist(gen);
		//a = rand() % 2;
		if (a == 0) {
			randY_in = 0;
		}
		else
			randY_in = _y - 1;
	}
	curpos.x = randX_in;
	curpos.y = randY_in;
	if (curpos.x == 0)
		curpos.vector = 1;
	if (curpos.x == _x - 1)
		curpos.vector = 3;
	if (curpos.y == 0)
		curpos.vector = 2;
	if (curpos.y == _y - 1)
		curpos.vector = 0;
}

void Arr::GenOut() // Генерация позиции выхода ////////////////////////////////////////////
{
	randX_out = 0;
	randY_out = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, _x - 1);
	do
	{
		randX_out = dist(gen);
		//randX_out = rand() % (_x);
		if (randX_out == 0 || randX_out == _x - 1)
		{
			std::uniform_int_distribution<> dist(0, _y - 1);
			while (randY_out == 0 || randY_out == _y - 1) 
			{
				randY_out = dist(gen);
				//randY_out = rand() % (_y);
			}
		}
		else
		{
			std::uniform_int_distribution<> dist(0, 1);
			int a = 0;
			a = dist(gen);
			//a = rand() % 2;
			if (a == 0) {
				randY_out = 0;
			}
			else
				randY_out = _y - 1;
		}
	} 
	while (randX_out == randX_in && randY_out == randY_in);
}

void Arr::FindNeigh() // Поиск соседей текущей клетки //////////////////////////////////////
{
	/////////////////////////////////////////////////////////////
	neighb[0].x = curpos.x;					// Верхний сосед
	if (curpos.y != 0)// Если не верхная часть
	{
		neighb[0].y = curpos.y - 1;
		neighb[0].vector = 0;
	}
	else
	{
		neighb[0].y = curpos.y + 1;
		neighb[0].vector = 0;
	}
	neighb[0].access = mass[neighb[0].x][neighb[0].y];
	/////////////////////////////////////////////////////////////
	if (curpos.x != _x - 1)					// Правый сосед
	{
		neighb[1].x = curpos.x + 1;
		neighb[1].vector = 1;
	}
	else
	{
		neighb[1].x = curpos.x - 1;
		neighb[1].vector = 1;
	}

	neighb[1].y = curpos.y;
	neighb[1].access = mass[neighb[1].x][neighb[1].y];
	//////////////////////////////////////////////////////////////
	neighb[2].x = curpos.x;					// Нижний сосед
	if (curpos.y != _y - 1)
	{
		neighb[2].y = curpos.y + 1;
		neighb[2].vector = 2;
	}
	else
	{
		neighb[2].y = curpos.y - 1;
		neighb[2].vector = 2;
	}
	neighb[2].access = mass[neighb[2].x][neighb[2].y];
	//////////////////////////////////////////////////////////////
	if (curpos.x != 0)						// Левый сосед
	{
		neighb[3].x = curpos.x - 1;
		neighb[3].vector = 3;
	}
	else
	{
		neighb[3].x = curpos.x + 1;
		neighb[3].vector = 3;
	}
	neighb[3].y = curpos.y;
	neighb[3].access = mass[neighb[3].x][neighb[3].y];
	///////////////////////////////////////////////////////////////

}

void Arr::GenWay() 	// Шаг ///////////////////////////////////////////////////////////////
{
	/*	std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 3);*/
	if (curpos.x == randX_out && curpos.y == randY_out)
	{
		if (steps >= minsteps)
			_error = 2;
		else
			_error = 1;
		return;
	}
	FindNeigh();
	count = 0;
	int a = 0;
	do
	{
		//a = dist(gen);
		a = rand() % 4;
		count++;
		if (count >= maxtry)
		{
			_error = 1;
			return;
		}
	} while (neighb[a].access != 0 && neighb[a].access != 3);

	mass[curpos.x][curpos.y] = 1;
	if (curpos.vector - neighb[a].vector == -1 || curpos.vector - neighb[a].vector == 3) // Поворот по ч.с.
	{
		mass[curpos.x][curpos.y] = 7;
	}
	if (curpos.vector - neighb[a].vector == 1 || curpos.vector - neighb[a].vector == -3) // поворот против ч.с.
	{
		mass[curpos.x][curpos.y] = 6;
	}
	if (curpos.x == randX_in && curpos.y == randY_in)
		mass[curpos.x][curpos.y] = 2;


	curpos.x = neighb[a].x;
	curpos.y = neighb[a].y;
	curpos.vector = neighb[a].vector;
	steps++;
}

int Arr::GetError() // Получить ошибку ////////////////////////////////////////////////////////
{
	return _error;
}

int Arr::GetSteps() // Получить кол-во шагов //////////////////////////////////////////////////
{
	return steps;
}

int Arr::WriteArr(int x,int y) // Получить точку карты ////////////////////////////////////////
{
	return mass[x][y];
}

void Arr::SetSteps(int steps) // Установить минимальное кол-во шагов //////////////////////////
{
	minsteps = steps;
}
