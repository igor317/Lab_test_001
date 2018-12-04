#include "DArray.h"

DArray::DArray(int x, int y)
{
	_x = x;
	_y = y;
	CreateArray();
}

void DArray::CreateArray()
{
	mass = new char*[_x];
	for (int j = 0; j < _x; j++) {
		mass[j] = new char[_y];
	}
}

DArray::~DArray()
{
	for (int i = 0; i < _x; i++)
		delete[] mass[i];
	delete[] mass;
}

char** DArray::GetArr()
{
	return mass;
}