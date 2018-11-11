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
		mass->GenWay();
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
		system("pause");
	}
	delete mass;
	return 0;
}
