#ifndef DARRAY_H
#define DARRAY_H
class DArray {
private:
	int _x;
	int _y;
	char** mass;
	void CreateArray();
public:
	DArray(int x,int y); // Конструктор класса
	char** GetArr();	 // Получить массив
	~DArray();			 // Деструктор класса
};

#endif