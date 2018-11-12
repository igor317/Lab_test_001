#include <iostream>
#include "Array.h"
#include <Windows.h>
using namespace std;

int main(int argc, char** argv)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = 0;
	int y = 0;
	cout << "colomns: ";
	cin >> x;
	cout << "lines: ";
	cin >> y;
	Arr* mass = new Arr(x, y);

	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			cout << mass->WriteArr(i, j) << " ";
		}
		cout << endl;
	}
	Position curpos;
	system("pause");
	while (1 != 0) 
	{
		mass = new Arr(x, y);
		//mass->tries = 0;
		//Arr* mass = new Arr(x, y);
		//Position curpos;
		while (mass->f != 2) 
		{
			mass->GenWay();
			if (mass->f == 1) 
			{
				mass = new Arr(x, y);
				mass->tries++;
			}
		}
		//mass->test();
		curpos = mass->GetPosition();
		for (int j = 0; j < y; j++) {
			for (int i = 0; i < x; i++) {
				if (curpos.x == i && curpos.y == j) 
				{
					cout << mass->WriteArr(i, j) << " ";
				}
				else
				{
					SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
					cout << mass->WriteArr(i, j) << " "; 
					SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				}
			}
			cout << endl;
		}
		cout << "tries: " << mass->tries << "  steps: " << mass->steps << "  counts: " << mass->count << endl;
		//delete mass;
		system("pause");
		

	}
	delete mass;
	return 0;
}
