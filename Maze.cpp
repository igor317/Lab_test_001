#include "Maze.h"
#include <time.h>
#include <iostream>
#include <random>
Maze::Maze(int x, int y,int minsteps) // Констурктор класса /////////////////////////////////////////
{
	srand(static_cast<unsigned int>(time(0))); // зерно рандома
	map.x = x;
	map.y = y;									  
	maxtry = 10;
	_error = 0;
	SetSteps(minsteps); // Минимум шагов 
	Create_arr();
	FillMass();
}

Maze::~Maze() // Деструктор класса /////////////////////////////////////////////////////
{
	for (int i = 0; i<map.x; i++)
		delete[] mass[i];
	delete[] mass;
}

void Maze::Create_arr() // Создание массива ////////////////////////////////////////////
{
	mass = new int*[map.x];
	for (int j = 0; j < map.x; j++) {
		mass[j] = new int[map.y];
	}
}

void Maze::FillMass()  // Заполнение массива ///////////////////////////////////////////
{
	for (int j = 0; j < map.y; j++) {
		for (int i = 0; i < map.x; i++) {
			mass[i][j] = 0;
			if (i == 0 || i == map.x - 1 || j == 0 || j == map.y - 1)
				mass[i][j] = 8;
			mass[0][0] = 9;
			mass[0][map.y - 1] = 9;
			mass[map.x - 1][0] = 9;
			mass[map.x - 1][map.y - 1] = 9;
		}
	}
	GenIn();
	GenOut();
	mass[entry.x][entry.y] = 2;
	mass[exit.x][exit.y] = 3;
}

void Maze::GenIn() // Генерация позиции входа ///////////////////////////////////////////
{
	entry.x = 0;
	entry.y = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, map.x - 1);
	entry.x = dist(gen);
	//entry.x = rand() % (map.x);
	if (entry.x == 0 || entry.x == map.x - 1) 
	{
		std::uniform_int_distribution<> dist(0, map.y - 1);
		while (entry.y == 0 || entry.y == map.y - 1) 
		{
			entry.y = dist(gen);
			//entry.y = rand() % (map.y);
		}
	}
	else
	{
		int a = 0;
		std::uniform_int_distribution<> dist(0, 1);
		a = dist(gen);
		//a = rand() % 2;
		if (a == 0) {
			entry.y = 0;
		}
		else
			entry.y = map.y - 1;
	}
	curpos.coord.x = entry.x;
	curpos.coord.y = entry.y;
	if (curpos.coord.x == 0)
		curpos.vector = 1;
	if (curpos.coord.x == map.x - 1)
		curpos.vector = 3;
	if (curpos.coord.y == 0)
		curpos.vector = 2;
	if (curpos.coord.y == map.y - 1)
		curpos.vector = 0;
}

void Maze::GenOut() // Генерация позиции выхода ////////////////////////////////////////////
{
	exit.x = 0;
	exit.y = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, map.x - 1);
	do
	{
		exit.x = dist(gen);
		//exit.x = rand() % (map.x);
		if (exit.x == 0 || exit.x == map.x - 1)
		{
			std::uniform_int_distribution<> dist(0, map.y - 1);
			while (exit.y == 0 || exit.y == map.y - 1) 
			{
				exit.y = dist(gen);
				//exit.y = rand() % (map.y);
			}
		}
		else
		{
			std::uniform_int_distribution<> dist(0, 1);
			int a = 0;
			a = dist(gen);
			//a = rand() % 2;
			if (a == 0) {
				exit.y = 0;
			}
			else
				exit.y = map.y - 1;
		}
	} 
	while (exit.x == entry.x && exit.y == entry.y);
}

void Maze::FindNeigh() // Поиск соседей текущей клетки //////////////////////////////////////
{
	/////////////////////////////////////////////////////////////
	neighb[0].coord.x = curpos.coord.x;					// Верхний сосед
	if (curpos.coord.y != 0)// Если не верхная часть
	{
		neighb[0].coord.y = curpos.coord.y - 1;
		neighb[0].vector = 0;
	}
	else
	{
		neighb[0].coord.y = curpos.coord.y + 1;
		neighb[0].vector = 0;
	}
	neighb[0].access = mass[neighb[0].coord.x][neighb[0].coord.y];
	/////////////////////////////////////////////////////////////
	if (curpos.coord.x != map.x - 1)					// Правый сосед
	{
		neighb[1].coord.x = curpos.coord.x + 1;
		neighb[1].vector = 1;
	}
	else
	{
		neighb[1].coord.x = curpos.coord.x - 1;
		neighb[1].vector = 1;
	}

	neighb[1].coord.y = curpos.coord.y;
	neighb[1].access = mass[neighb[1].coord.x][neighb[1].coord.y];
	//////////////////////////////////////////////////////////////
	neighb[2].coord.x = curpos.coord.x;					// Нижний сосед
	if (curpos.coord.y != map.y - 1)
	{
		neighb[2].coord.y = curpos.coord.y + 1;
		neighb[2].vector = 2;
	}
	else
	{
		neighb[2].coord.y = curpos.coord.y - 1;
		neighb[2].vector = 2;
	}
	neighb[2].access = mass[neighb[2].coord.x][neighb[2].coord.y];
	//////////////////////////////////////////////////////////////
	if (curpos.coord.x != 0)						// Левый сосед
	{
		neighb[3].coord.x = curpos.coord.x - 1;
		neighb[3].vector = 3;
	}
	else
	{
		neighb[3].coord.x = curpos.coord.x + 1;
		neighb[3].vector = 3;
	}
	neighb[3].coord.y = curpos.coord.y;
	neighb[3].access = mass[neighb[3].coord.x][neighb[3].coord.y];
	///////////////////////////////////////////////////////////////

}

void Maze::GenWay() 	// Шаг ///////////////////////////////////////////////////////////////
{
	/*	std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 3);*/
	if (curpos.coord.x == exit.x && curpos.coord.y == exit.y)
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

	mass[curpos.coord.x][curpos.coord.y] = 1;
	if (curpos.vector - neighb[a].vector == -1 || curpos.vector - neighb[a].vector == 3) // Поворот по ч.с.
	{
		mass[curpos.coord.x][curpos.coord.y] = 7;
	}
	if (curpos.vector - neighb[a].vector == 1 || curpos.vector - neighb[a].vector == -3) // поворот против ч.с.
	{
		mass[curpos.coord.x][curpos.coord.y] = 6;
	}
	if (curpos.coord.x == entry.x && curpos.coord.y == entry.y)
		mass[curpos.coord.x][curpos.coord.y] = 2;


	curpos.coord.x = neighb[a].coord.x;
	curpos.coord.y = neighb[a].coord.y;
	curpos.vector = neighb[a].vector;
	steps++;
}

int Maze::GetError() // Получить ошибку ////////////////////////////////////////////////////////
{
	return _error;
}

int Maze::GetSteps() // Получить кол-во шагов //////////////////////////////////////////////////
{
	return steps;
}

int Maze::WriteArr(int x,int y) // Получить точку карты ////////////////////////////////////////
{
	return mass[x][y];
}

void Maze::SetSteps(int steps) // Установить минимальное кол-во шагов //////////////////////////
{
	minsteps = steps;
}