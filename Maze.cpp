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
	dubmass = new DArray(size.x, size.y);
	FillDecoder();
}

Maze::~Maze()
{
	delete mass;
	if (freepoints != NULL)
		delete freepoints;
	if (dubmass != NULL)
	{
		delete dubmass;
	}
}

void Maze::FillDecoder()
{
	dec[0].decode = "LL"; // Лево-лево
	dec[0].encode = 'L';
	othdec[0].decode = "LL"; // Лево-лево
	othdec[0].encode = 'l';

	dec[1].decode = "LU"; // Лево-верх
	dec[1].encode = 'C';
	othdec[1].decode = "LU"; // Лево-верх
	othdec[1].encode = 'c';

	dec[2].decode = "LD"; // Лево-низ
	dec[2].encode = 'V';
	othdec[2].decode = "LD"; // Лево-низ
	othdec[2].encode = 'v';

	dec[3].decode = "UU"; // Верх-верх
	dec[3].encode = 'U';
	othdec[3].decode = "UU"; // Верх-верх
	othdec[3].encode = 'u';

	dec[4].decode = "UL"; // Верх-лево
	dec[4].encode = 'B';
	othdec[4].decode = "UL"; // Верх-лево
	othdec[4].encode = 'b';

	dec[5].decode = "UR"; // Верх-право
	dec[5].encode = 'V';
	othdec[5].decode = "UR"; // Верх-право
	othdec[5].encode = 'v';

	dec[6].decode = "RR"; // Право-право
	dec[6].encode = 'L';
	othdec[6].decode = "RR"; // Право-право
	othdec[6].encode = 'l';

	dec[7].decode = "RU"; // Право-верх
	dec[7].encode = 'X';
	othdec[7].decode = "RU"; // Право-верх
	othdec[7].encode = 'x';

	dec[8].decode = "RD"; // Право-низ
	dec[8].encode = 'B';
	othdec[8].decode = "RD"; // Право-низ
	othdec[8].encode = 'b';

	dec[9].decode = "DD"; // Низ-низ
	dec[9].encode = 'U';
	othdec[9].decode = "DD"; // Низ-низ
	othdec[9].encode = 'u';

	dec[10].decode = "DL"; // Низ-лево
	dec[10].encode = 'X';
	othdec[10].decode = "DL"; // Низ-лево
	othdec[10].encode = 'x';

	dec[11].decode = "DR"; // Низ-право
	dec[11].encode = 'C';
	othdec[11].decode = "DR"; // Низ-право
	othdec[11].encode = 'c';
}

char Maze::FindCode(std::string code, Decoder* dec)
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
	ReplaceMap(mass, dubmass);
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
	mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn,dec);
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
	GenInOther();
	while (_error != 4)
	{
		if (_error == 3)
		{
			ReplaceMap(dubmass, mass);
			_error = 2;
		}
		GenOtherStep();
	}
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

void Maze::GenInOther()
{
	int a = 0;
	FindFreePoints();
	if (zerocounts != 0)
	{
		ReplaceMap(mass, dubmass);
		a = rand() % zerocounts;
		curpos.coord.x = freepoints[a].x;
		curpos.coord.y = freepoints[a].y;
		mass->GetArr()[curpos.coord.x][curpos.coord.y] = '2';
		//FindFreePoints();
	}
	else
		_error = 4;

}

void Maze::GenOtherStep()
{
	std::string turn = "";			// Для расчета поворота

	FindNeigh();
	randcount = 0;
	int a = 0;
	do
	{
		a = rand() % 4;
		randcount++;
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'L')
		{
			if (neighb[a].vector == 0)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'E';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'Q';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'U')
		{
			if (neighb[a].vector == 1)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'W';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'R';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'X')
		{
			if (neighb[a].vector == 0)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'W';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'Q';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'C')
		{
			if (neighb[a].vector == 1)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'Q';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'R';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'V')
		{
			if (neighb[a].vector == 3)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'R';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'E';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'B')
		{
			if (neighb[a].vector == 3)
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'E';
			else
				mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = 'W';
			turn.push_back(curpos.vector);
			turn.push_back(neighb[a].vector);
			mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
			rmp();
			GenInOther();
			return;
		}
		if (randcount >= maxtry)
		{
			_error = 3;
			ReplaceMap(dubmass, mass);
			return;
		}
	} while (neighb[a].access != '0');

	turn.push_back(curpos.vector);
	turn.push_back(neighb[a].vector);
	mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn,othdec);

	curpos.coord.x = neighb[a].coord.x;
	curpos.coord.y = neighb[a].coord.y;
	curpos.vector = neighb[a].vector;
}

void Maze::ReplaceMap(DArray* from, DArray* to)
{
	for (int j = 0; j < size.y; ++j) 
		for (int i = 0; i < size.x; ++i)
			to->GetArr()[i][j] = from->GetArr()[i][j];
}

void Maze::rmp()
{
	for (int j = 0;j<size.y;j++)
		for (int i = 0;i<size.x;i++)
	switch (mass->GetArr()[i][j]) {
	case 'l':
		mass->GetArr()[i][j] = 'L';
		break;
	case 'u':
		mass->GetArr()[i][j] = 'U';
		break;
	case 'x':
		mass->GetArr()[i][j] = 'X';
		break;
	case 'c':
		mass->GetArr()[i][j] = 'C';
		break;
	case 'v':
		mass->GetArr()[i][j] = 'V';
		break;
	case 'b':
		mass->GetArr()[i][j] = 'B';
		break;
	}
}

/*if (mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'L' || mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'U'
|| mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'X' || mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'C'
|| mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'V' || mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] == 'B')
{
turn.push_back(curpos.vector);
turn.push_back(neighb[a].vector);
mass->GetArr()[curpos.coord.x][curpos.coord.y] = FindCode(turn, othdec);
mass->GetArr()[neighb[a].coord.x][neighb[a].coord.y] = '@';
rmp();
GenInOther();
return;
}*/