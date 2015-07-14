#include "stdafx.h"
#include "ProcessVector.h"

using namespace std;

void TestProcessVector()
{
	vector<double> tesingVector, aquiredResult, expectedResult;

	// работа с целыми числами
	tesingVector = { 1, 2, 3 };
	expectedResult = { 7, 8, 9 };
	aquiredResult = ProcessVector(tesingVector);
	assert(aquiredResult == expectedResult);

	// работа с дробными числами, числами разных знаков и нулём
	tesingVector = { -10, 5.5, 7.3, 6.8, -5, 0 };
	expectedResult = { -25, -20, -15, -9.5, -8.2, -7.7 };
	aquiredResult = ProcessVector(tesingVector);
	assert(aquiredResult == expectedResult);

	// работа с вектором длиной < 3
		// нулевая длина
	tesingVector.clear();
	expectedResult.clear();
	aquiredResult = ProcessVector(tesingVector);
	assert(aquiredResult == expectedResult);

		// длина == 1
	tesingVector = { 2.3 };
	expectedResult = { 2.3 };
	aquiredResult = ProcessVector(tesingVector);
	assert(aquiredResult == expectedResult);

		// длина == 2
	tesingVector = { 2, 3 };
	expectedResult = { 2, 3 };
	aquiredResult = ProcessVector(tesingVector);
	assert(aquiredResult == expectedResult);

	cout << "Testing of processing vectors completed successfully.\n";
}