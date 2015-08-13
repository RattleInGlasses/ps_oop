// MySet.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vld.h>


struct MyArray
{
	int *m_data = new int[10];

	int& at(int index)
	{
		return m_data[index];
	}

	void Destroy()
	{
		delete m_data;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	MyArray arr;

	int x = arr.at(3);
	x = 21;
	printf("%d\n", arr.at(3));
	arr.at(3) = 31;
	printf("%d\n", arr.at(3));

	arr.Destroy();
	return 0;
}

