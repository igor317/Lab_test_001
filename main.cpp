#include <iostream>
#include "Maze.h"
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

void DrawMass(Maze* m,int x,int y)
{
	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
	for (int j = 0; j < y; j++)
	{
		for (int i = 0; i < x; i++) {
			SetConsoleTextAttribute(hStdOut, 15);

			switch (m->WriteArr(i, j))
			{
			case '2':
				SetConsoleTextAttribute(hStdOut, 11);
				break;
			case '3':
				SetConsoleTextAttribute(hStdOut, 11);
				break;
			case 'L':
				SetConsoleTextAttribute(hStdOut, 2);
				break;
			case 'U':
				SetConsoleTextAttribute(hStdOut, 3);
				break;
			case 'X':
				SetConsoleTextAttribute(hStdOut, 4);
				break;
			case 'C':
				SetConsoleTextAttribute(hStdOut, 5);
				break;
			case 'V':
				SetConsoleTextAttribute(hStdOut, 6);
				break;
			case 'B':
				SetConsoleTextAttribute(hStdOut, 7);
				break;
			case 'Q':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			case 'W':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			case 'E':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			case 'R':
				SetConsoleTextAttribute(hStdOut, 12);
				break;
			}
			cout << m->WriteArr(i, j) << " ";
		}
		cout << endl;
	}
}

void SendToFile(string filename,Maze* m,int x,int y)
{
	fstream _desc;
	_desc.open(filename, fstream::out);
	for (int j = 0; j < y; j++)
	{
		for (int i = 0; i < x; i++) 
		{
			_desc << m->WriteArr(i, j);
		}
		_desc << "\n";
	}
	_desc.close();
}

int main(int argc, char** argv)
{
	system("cls");
	int x = 0;
	int y = 0;
	int minsteps = 0;
	string test = "";
	string a = "";
	while (test != "n") 
	{
		cout << "column: ";
		cin >> x;
		cout << "lines: ";
		cin >> y;
		cout << "min steps: ";
		cin >> minsteps;
		Maze* m = new Maze(x, y, minsteps);
		m->GenWay();
		DrawMass(m, x, y);
		cout << "Attempts: " << m->GetAttemps() << "| Steps: " << m->GetSteps() << endl;
		cout << "SaveFile? (y//n): ";
		cin >> a;
		if (a == "y")
			SendToFile("E:\\UnityProject\\testProject\\Assets\\test2.txt", m, x, y);
		cout << "Create new maze? (y//n): ";
		cin >> test;
		delete m;
	}
	return 0;
}