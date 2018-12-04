#include <iostream>
#include "Maze.h"
#include <Windows.h>
using namespace std;

void DrawMass(Maze* m,int x,int y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
	for (int j = 0; j < y; j++)
	{
		for (int i = 0; i < x; i++) {
			SetConsoleTextAttribute(hStdOut, 15);

			switch (m->WriteArr(i, j))
			{
			case '2':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			case '3':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			case 'U':
				SetConsoleTextAttribute(hStdOut, 14);
				break;
			case 'L':
				SetConsoleTextAttribute(hStdOut, 9);
				break;
			case 'R':
				SetConsoleTextAttribute(hStdOut, 10);
				break;
			case 'D':
				SetConsoleTextAttribute(hStdOut, 11);
				break;
			}
			cout << m->WriteArr(i, j) << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	int x = 7;
	int y = 7;
	int minsteps = 3;
	Maze* m = new Maze(x, y, minsteps);
	while (1 != 0) 
	{
		system("cls");
		m->GenWay();
		DrawMass(m, x, y);
		cout << "Attempts: " << m->GetAttemps() << "| Steps: " << m->GetSteps() << "| free: " << m->zerocounts << endl;
		system("pause");
	}
	delete m;
	return 0;
}