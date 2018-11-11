/*
0 - ������ ������
1 - ������� �����
6 - ������� �����
7 - ������� ������
2 - ����
3 - �����
8 - ������� �����
9 - ����������� ������ (� �����)
*/
#ifndef ARRAY_H
#define ARRAY_H
struct Position 
{
	int x;
	int y;
	int vector;
	int color;
};
struct Neigh 
{
	int x;
	int y;
	int access;
	int vector;
};

class Arr
{
private:
	int _x;
	int _y;
	int randX_in, randY_in;
	int randX_out, randY_out;
	int** mass;
	int maxtry;
	int count;
	Position curpos;
	Neigh neighb[4];

	void Create_arr();
	void FillMass();
	void GenIn();
	void GenOut();
	void FindNeigh();
	void Regenerate();



public:
	Arr(int x, int y);
	~Arr();
	int WriteArr(int x,int y);
	void GenWay();
	Position GetPosition();
	void test();
};

#endif