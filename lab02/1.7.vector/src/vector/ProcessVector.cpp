#include "stdafx.h"

using namespace std;

vector<double> ProcessVector(vector<double> const &vectorOfDouble)
{
	vector<double> result = vectorOfDouble;

	if (result.size() < 3)  // возвращаем вектор, не удовлетворяющий заднным
	{                       // условиям в первозданном виде
		return result;
	}
	
	sort(result.begin(), result.end());

	double sum3min = 0;
	for (int i = 0; i < 3; i++)
	{
		sum3min += result[i];
	}

	int len = (int)result.size();
	for (int i = 0; i < len; i++)
	{
		result[i] += sum3min;
	}

	return result;
}