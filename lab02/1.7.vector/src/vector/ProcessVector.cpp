#include "stdafx.h"

using namespace std;

double GetSum3Min(vector<double> const &vectorOfDouble);
vector<double> AddConstantToVector(vector<double> const &vectorOfDouble, double number);

vector<double> ProcessVector(vector<double> const &vectorOfDouble)
{
	vector<double> result = vectorOfDouble;

	if (result.size() < 3)  // возвращаем вектор, не удовлетворяющий заднным
	{                       // условиям, в первозданном виде
		return result;
	}

	sort(result.begin(), result.end());
	return AddConstantToVector(result, GetSum3Min(result));
}

// get sum of 3 minimal elements of a sorted vector.
double GetSum3Min(vector<double> const &vectorOfDouble)
{
	double sum3min = 0;
	for (int i = 0; i < 3; i++)
	{
		sum3min += vectorOfDouble[i];
	}
	return sum3min;
}

// adds a number to every element of a vector
vector<double> AddConstantToVector(vector<double> const &vectorOfDouble, double number)
{
	vector<double> result;
	int len = (int)vectorOfDouble.size();
	for (int i = 0; i < len; i++)
	{
		result.push_back(vectorOfDouble[i] + number);
	}
	return result;
}