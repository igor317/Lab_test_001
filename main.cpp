#include <iostream>
#include "Maze.h"
#include <Windows.h>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15); // ����� ���� ������
	int x = 0;
	int y = 0;
	int minsteps = 0;
	int attempts = 0;
	int maxattempts = 1000000;
	cout << "columns: ";
	cin >> x;
	cout << "lines: ";
	cin >> y;
	cout << "Min steps: ";
	cin >> minsteps;
	Maze* lab = new Maze(x, y, minsteps);

	while (1 != 0) 
	{
		attempts = 0;
		lab = new Maze(x, y, minsteps);
		while (lab->GetError() != 2) 
		{
			lab->GenWay();
			if (lab->GetError() == 1) 
			{
				delete lab;
				lab = new Maze(x, y, minsteps);
				attempts++;
			}
			if (attempts > maxattempts)
			{
				delete lab;
				cout << "Error" << endl;
				system("pause");
				return 0;
			}
		}

		for (int j = 0; j < y; j++) // ��������� �������
		{
			for (int i = 0; i < x; i++) {
				SetConsoleTextAttribute(hStdOut, 15);

				switch (lab->WriteArr(i, j))
				{
				case 2:
					SetConsoleTextAttribute(hStdOut, 6); // ���� (�����)
					break;
				case 3:
					SetConsoleTextAttribute(hStdOut, 12); // ����� (�������)
					break;
				case 1:
					SetConsoleTextAttribute(hStdOut, 14); // ������ ������� (������)
					break;
				case 6:
					SetConsoleTextAttribute(hStdOut, 9); // ������� �� �.�. (�����)
					break;
				case 7:
					SetConsoleTextAttribute(hStdOut, 10); // ������� ������ �.�. (������-�������)
					break;
				}
				cout << lab->WriteArr(i, j) << " ";
			}
			cout << endl;
		}
		cout << "attempts: " << attempts << "  steps: " << lab->GetSteps() << endl; // ����������
		delete lab;
		cout << "end?(y/n): ";
		string t;
		cin >> t;
		if (t == "y") break;
	}
	return 0;
}
