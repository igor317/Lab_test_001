#ifndef MAZE_H
#define MAZE_H
#include "DArray.h"
#include <random>
#include <time.h>
struct Point    // ��������� ����� (X � Y)
{
	int x;
	int y;
};
struct Position // ��������� �������
{
	Point coord;// ���������� (X � Y)
	int vector; // �����������(��� ����������� ����������� ��������(����))
};
struct Neighbor // ��������� �������(��� �������� ������ �� �����������)
{
	Point coord;// ���������� (X � Y)
	char access; // ������
	int vector; // �����������
};

class Maze{
private:
	DArray* mass;				// �����
	Point size;					// ������ �����
	Point entry;				// ������� �����
	Point exit;					// ������� ������
	Point* freepoints;			// ���������� ������ ������

	int maxtry;					// ������������ ���������� ������� ������� (������� �������� ������������\������)
	int steps;					// ���������� �����
	int randcount;				// ���������� ������� �������
	int _error;					// ������ (0 - ��� ������/1 - ����������/2 - ����� �����)
	int minst;					// ����������� ���-�� �����
	int attempts;				// ���������� �������

	Position curpos;			// ������� �������
	Neighbor neighb[4];			// ������

	void FillMass();		// ���������� �������(�������� ������� �����)
	void GenIn();// ��������� ������� �����
	void GenOut();			// ��������� ������� ������
	void FindNeigh();		// ����� ������� ������� �������
	void GenStep();						// ��������� ����(���)
	void FindFreePoints();				// ����� ������ ������
public:
	Maze(int x, int y, int minsteps);	// ����������� ������
	~Maze();							// ���������� ������
	void GenWay();						// ��������� ����
	int GetSteps();						// �������� ���������� �����
	int GetAttemps();					// �������� ���������� �������
	char WriteArr(int x, int y);		// ����� ����� �������(�����)

	int zerocounts;				// ���-�� ������ ������
};
#endif