#include "stdafx.h"
#include "ProcessVector.h"

using namespace std;

void TestProcessVector()
{
	vector<double> testingVector, aquiredResult, expectedResult;

	// работа с целыми числами
	testingVector = { 1, 2, 3 };
	expectedResult = { 7, 8, 9 };
	ProcessVector(testingVector);
	assert(testingVector == expectedResult);

	// работа с дробными числами, числами разных знаков и нулём
	testingVector = { -10, 5.5, 7.3, 6.8, -5, 0 };
	expectedResult = { -25, -20, -15, -9.5, -8.2, -7.7 };
	ProcessVector(testingVector);
	assert(testingVector == expectedResult);

	// работа с вектором длиной < 3
		// нулевая длина
	testingVector.clear();
	expectedResult.clear();
	ProcessVector(testingVector);
	assert(testingVector == expectedResult);

		// длина == 1
	testingVector = { 2.3 };
	expectedResult = { 4.6 };
	ProcessVector(testingVector);
	assert(testingVector == expectedResult);

		// длина == 2
	testingVector = { 2, 3 };
	expectedResult = { 7, 8 };
	ProcessVector(testingVector);
	assert(testingVector == expectedResult);

	cout << "Testing of processing vectors completed successfully.\n";
}