// sets.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MSG_USAGE          "USAGE: sets <number>\n"
#define MSG_DESCRIPTION_1  "The program prints set of integer numbers from 1 to N that are satisfy following conditions:\n"
#define MSG_DESCRIPTION_2  "1. reminder after division of the number by sum of its digits is zero;\n"
#define MSG_DESCRIPTION_3  "2. sum of number's digits is even.\n"
#define MSG_DESCRIPTION    MSG_DESCRIPTION_1 MSG_DESCRIPTION_2 MSG_DESCRIPTION_3 MSG_USAGE
#define MSG_TOO_MANY_ARGS  "The program needs only one argument.\n" MSG_USAGE
#define MSG_NOT_INTEGER    "The argument must be integer number.\n"
#define MSG_LESS_1         "The number must be positive\n";

using namespace std;

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		return false;
	}
	if (argc > 2)
	{
		cout << MSG_TOO_MANY_ARGS;
		return false;
	}
	return true;
}

bool StrToInt(char *const pStr, int &num)
{
	char *pEndPoint;
	num = strtol(pStr, &pEndPoint, 10);
	if ((*pStr == '\0') || (*pEndPoint != '\0'))
	{
		cout << MSG_NOT_INTEGER;
		return false;
	}
	return true;
}

int DigitsSum(int num)
{
	int sum = 0;
	while (num > 0)
	{
		sum += num % 10;
		num /= 10;
	}

	return sum;
}

set<int> CreateSet1(int N)
{
	set<int> set1;
	for (int i = 1; i <= N; i++)
	{
		if (i % DigitsSum(i) == 0)
		{
			set1.insert(i);
		}
	}

	return set1;
}

set<int> CreateSet2(int N)
{
	set<int> set2;
	for (int i = 1; i <= N; i++)
	{
		if (DigitsSum(i) % 2 == 0)
		{
			set2.insert(i);
		}
	}

	return set2;
}

set<int> CrossSet(set<int> &const set1, set<int> &const set2)
{
	set<int> intersection;
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
	return intersection;
}

void PrintSet(set<int> &const printableSet)
{
	for (set<int>::iterator it = printableSet.begin(); it != printableSet.end(); it++)
	{
		cout << *it;
		if (it != --printableSet.end())
		{
			cout << ", ";
		}
	}
	cout << '\n';
}

void TestCrossSet()
{
	set<int> set1, set2, intersection, rightResult;

	intersection = CrossSet(set1, set2);
	assert(intersection == rightResult);

	set1 = { 1, 2, 3 };
	// set2 = {};
	intersection = CrossSet(set1, set2);
	assert(intersection == rightResult);

	set1 = { 1, 2, 3 };
	set2 = { 4, 5 };
	intersection = CrossSet(set1, set2);
	assert(intersection == rightResult);

	set1 = { 1, 2, 3, 4 };
	set2 = { 4, 5 };
	rightResult = { 4 };
	intersection = CrossSet(set1, set2);
	assert(intersection == rightResult);
}

int main(int argc, char* argv[])
{
	//TestCrossSet;
	
	if (!CheckArgc(argc))
	{
		return 1;
	}

	int n;
	if (StrToInt(argv[1], n))
	{
		if (n < 1)
		{
			cout << MSG_LESS_1;
			return 1;
		}

		set<int> set1 = CreateSet1(n);
		set<int> set2 = CreateSet2(n);
		set<int> intersection = CrossSet(set1, set2);

		PrintSet(intersection);
	}
	else
	{
		return 1;
	}

	return 0;
}

