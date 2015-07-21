#include "stdafx.h"

using namespace std;

void ProcessVector(vector<double> &vectorOfDouble)
{
	size_t sumElementsCount = 3;
	if (vectorOfDouble.size() < 3)
	{                       
		sumElementsCount = vectorOfDouble.size();
	}

	sort(vectorOfDouble.begin(), vectorOfDouble.end());
	double sumMinElements = accumulate(vectorOfDouble.begin(), vectorOfDouble.begin() + sumElementsCount, 0.0);
	transform(vectorOfDouble.begin(), vectorOfDouble.end(), vectorOfDouble.begin(), [sumMinElements](double el){ return el + sumMinElements; });
}
