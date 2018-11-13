#include <iostream>
#include "Array.h"
#include <Windows.h>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15); // белый цвет текста
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
	Arr* mass = new Arr(x, y, minsteps);

	while (1 != 0) 
	{
		attempts = 0;
		mass = new Arr(x, y, minsteps);
		while (mass->GetError() != 2) 
		{
			mass->GenWay();
			if (mass->GetError() == 1) 
			{
				delete mass;
				mass = new Arr(x, y, minsteps);
				attempts++;
			}
			if (attempts > maxattempts)
			{
				delete mass;
				cout << "Error" << endl;
				system("pause");
				return 0;
			}
		}

		for (int j = 0; j < y; j++) // Отрисовка массива
		{
			for (int i = 0; i < x; i++) {
				SetConsoleTextAttribute(hStdOut, 15);

				switch (mass->WriteArr(i, j))
				{
				case 2:
					SetConsoleTextAttribute(hStdOut, 6); // Вход (серый)
					break;
				case 3:
					SetConsoleTextAttribute(hStdOut, 12); // Выход (КРАСНЫЙ)
					break;
				case 1:
					SetConsoleTextAttribute(hStdOut, 14); // Прямой коридор (Желтый)
					break;
				case 6:
					SetConsoleTextAttribute(hStdOut, 9); // Поворот по ч.с. (СИНИЙ)
					break;
				case 7:
					SetConsoleTextAttribute(hStdOut, 10); // Поворот против ч.с. (СВЕТЛО-ЗЕЛЕНЫЙ)
					break;
				}
				cout << mass->WriteArr(i, j) << " ";
			}
			cout << endl;
		}
		cout << "attempts: " << attempts << "  steps: " << mass->GetSteps() << endl; // Статистика
		delete mass;
		cout << "end?(y/n): ";
		string t;
		cin >> t;
		if (t == "y") break;
	}
	return 0;
}
