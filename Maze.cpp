#include "Maze.h"

Maze::Maze(int x, int y, int minsteps) // Констурктор класса /////////////////////////////////////////
{
	srand(static_cast<unsigned int>(time(0))); // зерно рандома
	size.x = x;
	size.y = y;
	maxtry = 10;
	_error = 0;
	minst = minsteps;
	mass = new DArray(size.x, size.y);
}

Maze::~Maze()
{
	delete mass;
}

void Maze::FillMass()  // Заполнение массива ///////////////////////////////////////////
{
	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			mass->GetArr()[i][j] = '0';
			if (i == 0 || i == size.x - 1 || j == 0 || j == size.y - 1)
				mass->GetArr()[i][j] = '-';
			mass->GetArr()[0][0] = ' ';
			mass->GetArr()[0][size.y - 1] = ' ';
			mass->GetArr()[size.x - 1][0] = ' ';
			mass->GetArr()[size.x - 1][size.y - 1] = ' ';
		}
	}
	GenIn();
	GenOut();
	mass->GetArr()[entry.x][entry.y] = '2';
	mass->GetArr()[exit.x][exit.y] = '3';
}

char Maze::WriteArr(int x, int y) // Получить точку карты ////////////////////////////////////////
{
	return mass->GetArr()[x][y];
}

void Maze::GenIn() // Генерация позиции входа ///////////////////////////////////////////
{
	entry.x = 0;
	entry.y = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, size.x - 1);
	entry.x = dist(gen);
	if (entry.x == 0 || entry.x == size.x - 1)
	{
		std::uniform_int_distribution<> dist(0, size.y - 1);
		while (entry.y == 0 || entry.y == size.y - 1)
		{
			entry.y = dist(gen);
		}
	}
	else
	{
		int a = 0;
		std::uniform_int_distribution<> dist(0, 1);
		a = dist(gen);
		if (a == 0) {
			entry.y = 0;
		}
		else
			entry.y = size.y - 1;
	}
	curpos.coord.x = entry.x;
	curpos.coord.y = entry.y;
	if (curpos.coord.x == 0)
		curpos.vector = 1;
	if (curpos.coord.x == size.x - 1)
		curpos.vector = 3;
	if (curpos.coord.y == 0)
		curpos.vector = 2;
	if (curpos.coord.y == size.y - 1)
		curpos.vector = 0;
}
void Maze::GenOut() // Генерация позиции выхода ////////////////////////////////////////////
{
	exit.x = 0;
	exit.y = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, size.x - 1);
	do
	{
		exit.x = dist(gen);
		if (exit.x == 0 || exit.x == size.x - 1)
		{
			std::uniform_int_distribution<> dist(0, size.y - 1);
			while (exit.y == 0 || exit.y == size.y - 1)
			{
				exit.y = dist(gen);
			}
		}
		else
		{
			std::uniform_int_distribution<> dist(0, 1);
			int a = 0;
			a = dist(gen);
			if (a == 0) {
				exit.y = 0;
			}
			else
				exit.y = size.y - 1;
		}
	} while (exit.x == entry.x && exit.y == entry.y);
}

void Maze::FindNeigh() // Поиск соседей текущей клетки //////////////////////////////////////
{
	/////////////////////////////////////////////////////////////// Верхний сосед			
	if (curpos.coord.y != 0)// Если не верхная часть
		neighb[0].coord.y = curpos.coord.y - 1;
	else
		neighb[0].coord.y = curpos.coord.y + 1;

	neighb[0].coord.x = curpos.coord.x;
	neighb[0].vector = 0;
	neighb[0].access = mass->GetArr()[neighb[0].coord.x][neighb[0].coord.y];
	/////////////////////////////////////////////////////////////// Правый сосед
	if (curpos.coord.x != size.x - 1)					
		neighb[1].coord.x = curpos.coord.x + 1;
	else
		neighb[1].coord.x = curpos.coord.x - 1;

	neighb[1].vector = 1;
	neighb[1].coord.y = curpos.coord.y;
	neighb[1].access = mass->GetArr()[neighb[1].coord.x][neighb[1].coord.y];
	//////////////////////////////////////////////////////////////// Нижний сосед			
	if (curpos.coord.y != size.y - 1)
		neighb[2].coord.y = curpos.coord.y + 1;
	else
		neighb[2].coord.y = curpos.coord.y - 1;
	neighb[2].coord.x = curpos.coord.x;
	neighb[2].vector = 2;
	neighb[2].access = mass->GetArr()[neighb[2].coord.x][neighb[2].coord.y];
	//////////////////////////////////////////////////////////////// Левый сосед
	if (curpos.coord.x != 0)						
		neighb[3].coord.x = curpos.coord.x - 1;
	else
		neighb[3].coord.x = curpos.coord.x + 1;
	neighb[3].vector = 3;
	neighb[3].coord.y = curpos.coord.y;
	neighb[3].access = mass->GetArr()[neighb[3].coord.x][neighb[3].coord.y];
	///////////////////////////////////////////////////////////////
}
void Maze::GenStep() 	// Шаг ///////////////////////////////////////////////////////////////
{
	if (curpos.coord.x == exit.x && curpos.coord.y == exit.y)
	{
		if (steps >= minst)
			_error = 2;
		else
			_error = 1;
		return;
	}
	FindNeigh();
	randcount = 0;
	int a = 0;
	do
	{
		a = rand() % 4;
		randcount++;
		if (randcount >= maxtry)
		{
			_error = 1;
			return;
		}
	} while (neighb[a].access != '0' && neighb[a].access != '3');
	/*if (neighb[a].vector == curpos.vector && neighb[a].vector == 0)
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'U';
	if (neighb[a].vector == curpos.vector && neighb[a].vector == 1)
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'R';
	if (neighb[a].vector == curpos.vector && neighb[a].vector == 2)
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'D';
	if (neighb[a].vector == curpos.vector && neighb[a].vector == 3)
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'L';*/
	switch (neighb[a].vector)
	{
	case 0:
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'U';
		break;
	case 1:
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'R';
		break;
	case 2:
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'D';
		break;
	case 3:
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = 'L';
		break;
	}

	if (curpos.coord.x == entry.x && curpos.coord.y == entry.y)
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = '2';

	curpos.coord.x = neighb[a].coord.x;
	curpos.coord.y = neighb[a].coord.y;
	curpos.vector = neighb[a].vector;
	steps++;
}

void Maze::GenWay()
{
	FillMass();
	_error = 0;
	attempts = 0;
	steps = 0;
	while (_error != 2)
	{
		GenStep();
		if (_error == 1)
		{
			FillMass();
			_error = 0;
			steps = 0;
			attempts++;
		}
	}
	FindFreePoints();
}

int Maze::GetSteps()
{
	return steps;
}

int Maze::GetAttemps()
{
	return attempts;
}

void Maze::FindFreePoints() {
	if (freepoints != NULL)
		delete freepoints;
	zerocounts = 0;
	int ct = 0;
	for (int j = 0; j < size.y; j++)
	{
		for (int i = 0; i < size.x; i++)
		{
			if (mass->GetArr()[i][j] == '0')
				zerocounts++;
		}
	}
	freepoints = new Point[zerocounts];
	for (int j = 0; j < size.y; j++)
	{
		for (int i = 0; i < size.x; i++)
		{
			if (mass->GetArr()[i][j] == '0')
			{
				freepoints[ct].x = i;
				freepoints[ct].y = j;
				ct++;
			}
		}
	}
}