#include "Array.h"
#include <time.h>
#include <iostream>
Arr::Arr(int x, int y)
{
	_x = x;
	_y = y;
	maxtry = 100;
	Create_arr();
	GenIn();
	GenOut();
	FillMass();
	//GenWay();
}

Arr::~Arr() {
	for (int i = 0; i<_x; i++)
		delete[] mass[i];
	delete[] mass;
}

void Arr::Create_arr() 
{
	mass = new int*[_x];
	for (int j = 0; j < _x; j++) {
		mass[j] = new int[_y];
	}
}

void Arr::FillMass()  // ���������� �������
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
	mass[randX_in][randY_in] = 2;
	mass[randX_out][randY_out] = 3;
}

void Arr::GenIn() 
{
	randX_in = 0;
	randY_in = 0;
	srand(time(0));

	randX_in = rand() % (_x);
	if (randX_in == 0 || randX_in == _x - 1) 
	{
		while (randY_in == 0 || randY_in == _y-1)
			randY_in = rand() % (_y);
	}
	else
	{
		int a = 0;
		a = rand() % 2;
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
void Arr::GenOut()
{
	srand(time(0));
	randX_out = 0;
	randY_out = 0;

	do
	{
		randX_out = rand() % (_x);
		if (randX_out == 0 || randX_out == _x - 1)
		{
			while (randY_out == 0 || randY_out == _y - 1)
				randY_out = rand() % (_y);
		}
		else
		{
			int a = 0;
			a = rand() % 2;
			if (a == 0) {
				randY_out = 0;
			}
			else
				randY_out = _y - 1;
		}
	} 
	while (randX_out == randX_in && randY_out == randY_in);
}

void Arr::FindNeigh() {
	/////////////////////////////////////////////////////////////
	neighb[0].x = curpos.x;					// ������� �����
	if (curpos.y != 0)// ���� �� ������� �����
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
	if (curpos.x != _x - 1)					// ������ �����
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
	neighb[2].x = curpos.x;					// ������ �����
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
	if (curpos.x != 0)						// ����� �����
	{
		neighb[3].x = curpos.x - 1;
		neighb[3].vector = 1;
	}
	else
	{
		neighb[3].x = curpos.x + 1;
		neighb[3].vector = 1;
	}
	neighb[3].y = curpos.y;
	neighb[3].access = mass[neighb[3].x][neighb[3].y];
	///////////////////////////////////////////////////////////////

}

void Arr::GenWay() 	/////////////////////////////////////////////////////////////	 ������
{
	if (curpos.x == randX_out && curpos.y == randY_out)
		return;
	FindNeigh();
	count = 0;
	int a = 0;
	srand(time(0));
	do
	{
		a = rand() % 4;
		count++;
		if (count >= maxtry)
		{
			Regenerate();
			return;
		}
	} while (neighb[a].access != 0 && neighb[a].access != 3);

	if (curpos.vector == neighb[a].vector) // �����
	{
		mass[curpos.x][curpos.y] = 1;
	}
	else
	{
		mass[curpos.x][curpos.y] = 1;
		if (curpos.vector - neighb[a].vector == -1 || curpos.vector - neighb[a].vector == 3) // ������
		{
			mass[curpos.x][curpos.y] = 7;
		}
		if (curpos.vector - neighb[a].vector == 1 || curpos.vector - neighb[a].vector == -3) // �����
		{
			mass[curpos.x][curpos.y] = 6;
		}
	}


	curpos.x = neighb[a].x;
	curpos.y = neighb[a].y;
	//mass[curpos.x][curpos.y] = 1;
	curpos.vector = neighb[a].vector;
	GenWay();
}

int Arr::WriteArr(int x,int y) {
	return mass[x][y];
}

Position Arr::GetPosition() {
	return curpos;
}

void Arr::Regenerate() {
	GenIn();
	GenOut();
	FillMass();
	GenWay();
}

void Arr::test() {
	count = 0;
	while (curpos.x != randX_out && curpos.y != randY_out)
	{
		if (count > maxtry)
		{
			Regenerate();
		}
		else
			GenWay();
	}

}