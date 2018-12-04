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
	FillDecoder();
}

Maze::~Maze()
{
	delete mass;
}

void Maze::FillDecoder()
{
	dec[0].decode = "LL"; // Лево-лево
	dec[0].encode = 'L';

	dec[1].decode = "LU"; // Лево-верх
	dec[1].encode = 'C';

	dec[2].decode = "LD"; // Лево-низ
	dec[2].encode = 'V';

	dec[3].decode = "UU"; // Верх-верх
	dec[3].encode = 'U';

	dec[4].decode = "UL"; // Верх-лево
	dec[4].encode = 'B';

	dec[5].decode = "UR"; // Верх-право
	dec[5].encode = 'V';

	dec[6].decode = "RR"; // Право-право
	dec[6].encode = 'L';

	dec[7].decode = "RU"; // Право-верх
	dec[7].encode = 'X';

	dec[8].decode = "RD"; // Право-низ
	dec[8].encode = 'B';

	dec[9].decode = "DD"; // Низ-низ
	dec[9].encode = 'U';

	dec[10].decode = "DL"; // Низ-лево
	dec[10].encode = 'X';

	dec[11].decode = "DR"; // Низ-право
	dec[11].encode = 'C';
}

char Maze::FindCode(std::string code)
{
	for (int i = 0; i < 12; ++i)
	{
		if (code == dec[i].decode)
			return dec[i].encode;
	}
	return ' ';
}

void Maze::FillMass()  // Заполнение массива ///////////////////////////////////////////
{
	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			mass->GetArr()[i][j] = '0';
			if (i == 0 || i == size.x - 1 || j == 0 || j == size.y - 1)
				mass->GetArr()[i][j] = '-';
			mass->GetArr()[0][0] = '-';
			mass->GetArr()[0][size.y - 1] = '-';
			mass->GetArr()[size.x - 1][0] = '-';
			mass->GetArr()[size.x - 1][size.y - 1] = '-';
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
		curpos.vector = 'R';
	if (curpos.coord.x == size.x - 1)
		curpos.vector = 'L';
	if (curpos.coord.y == 0)
		curpos.vector = 'D';
	if (curpos.coord.y == size.y - 1)
		curpos.vector = 'U';
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
	{
		neighb[0].coord.y = curpos.coord.y - 1;
		neighb[0].vector = 'U';
	}
	else
	{
		neighb[0].coord.y = curpos.coord.y + 1;
		neighb[0].vector = 'D';
	}
	neighb[0].coord.x = curpos.coord.x;
	neighb[0].access = mass->GetArr()[neighb[0].coord.x][neighb[0].coord.y];
	/////////////////////////////////////////////////////////////// Правый сосед
	if (curpos.coord.x != size.x - 1)
	{
		neighb[1].coord.x = curpos.coord.x + 1;
		neighb[1].vector = 'R';
	}
	else
	{
		neighb[1].coord.x = curpos.coord.x - 1;
		neighb[1].vector = 'L';
	}
	neighb[1].coord.y = curpos.coord.y;
	neighb[1].access = mass->GetArr()[neighb[1].coord.x][neighb[1].coord.y];
	//////////////////////////////////////////////////////////////// Нижний сосед			
	if (curpos.coord.y != size.y - 1)
	{
		neighb[2].coord.y = curpos.coord.y + 1;
		neighb[2].vector = 'D';
	}
	else
	{
		neighb[2].coord.y = curpos.coord.y - 1;
		neighb[2].vector = 'U';
	}
	neighb[2].coord.x = curpos.coord.x;

	neighb[2].access = mass->GetArr()[neighb[2].coord.x][neighb[2].coord.y];
	//////////////////////////////////////////////////////////////// Левый сосед
	if (curpos.coord.x != 0)
	{
		neighb[3].coord.x = curpos.coord.x - 1;
		neighb[3].vector = 'L';
	}
	else
	{
		neighb[3].coord.x = curpos.coord.x + 1;
		neighb[3].vector = 'R';
	}
	neighb[3].coord.y = curpos.coord.y;
	neighb[3].access = mass->GetArr()[neighb[3].coord.x][neighb[3].coord.y];
	///////////////////////////////////////////////////////////////
}
void Maze::GenStep() 	// Шаг ///////////////////////////////////////////////////////////////
{
	std::string turn = "";			// Для расчета поворота
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
	
	turn.push_back(curpos.vector);
	turn.push_back(neighb[a].vector);
	mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn);
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