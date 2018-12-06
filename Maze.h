#ifndef MAZE_H
#define MAZE_H
#include "DArray.h"
#include <random>
#include <time.h>
struct Decoder
{
	std::string decode;
	char encode;
};
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
	char vector; // �����������
};

class Maze{
private:
	DArray* mass;				// �����
	DArray* dubmass;			// �������� ����� (��� �������� ���������)
	Point size;					// ������ �����
	Point entry;				// ������� �����
	Point exit;					// ������� ������
	Point* freepoints;			// ���������� ������ ������

	int maxtry;					// ������������ ���������� ������� ������� (������� �������� ������������\������)
	int steps;					// ���������� �����
	int randcount;				// ���������� ������� �������

	int minst;					// ����������� ���-�� �����
	int attempts;				// ���������� �������


	Position curpos;			// ������� �������
	Neighbor neighb[4];			// ������
	Decoder dec[12];
	Decoder othdec[12];

	void FillDecoder();			// ��������� �������

	void FillMass();		// ���������� �������(�������� ������� �����)
	void GenIn();// ��������� ������� �����
	void GenOut();			// ��������� ������� ������
	void FindNeigh();		// ����� ������� ������� �������
	void GenStep();						// ��������� ����(���)
	void FindFreePoints();				// ����� ������ ������
	char FindCode(std::string code,Decoder* dec);
	void ReplaceMap(DArray* from, DArray* to);
	void rmp();
public:
	Maze(int x, int y, int minsteps);	// ����������� ������
	~Maze();							// ���������� ������
	void GenWay();						// ��������� ����
	int GetSteps();						// �������� ���������� �����
	int GetAttemps();					// �������� ���������� �������
	char WriteArr(int x, int y);		// ����� ����� �������(�����)
	void GenInOther();					// ��������� ����� �� ������ ������
	void GenOtherStep();
	int zerocounts;				// ���-�� ������ ������

	int _error;					// ������ (0 - ��� ������/1 - ����������/2 - ����� �����)
};
#endif