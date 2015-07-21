// sets.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

string const MSG_USAGE =          "USAGE: sets <number>\n";
string const MSG_DESCRIPTION_1 =  "The program prints set of integer numbers from 1 to N that are satisfy following conditions:\n";
string const MSG_DESCRIPTION_2 =  "1. reminder after division of the number by sum of its digits is zero;\n";
string const MSG_DESCRIPTION_3 =  "2. sum of number's digits is even.\n";
string const MSG_DESCRIPTION =    MSG_DESCRIPTION_1 + MSG_DESCRIPTION_2 + MSG_DESCRIPTION_3 + MSG_USAGE;
string const MSG_TOO_MANY_ARGS =  "The program needs only one argument.\n" + MSG_USAGE;
string const MSG_NOT_INTEGER =    "The argument must be integer number.\n";
string const MSG_LESS_1 =         "The number must be positive\n";

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

boost::optional<int> StrToInt(char *const pStr)
{
	char *pEndPoint;
	int num = strtol(pStr, &pEndPoint, 10);
	if ((*pStr == '\0') || (*pEndPoint != '\0'))
	{
		return boost::none;
	}
	return num;
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
	for (int i = 1; i <= N; ++i)
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
	for (int i = 1; i <= N; ++i)
	{
		if (DigitsSum(i) % 2 == 0)
		{
			set2.insert(i);
		}
	}

	return set2;
}

set<int> CrossSet(set<int> const &set1, set<int> const &set2)
{
	set<int> intersection;
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
	return intersection;
}

void PrintSet(set<int> const & printableSet)
{
	for (set<int>::iterator it = printableSet.begin(); it != printableSet.end(); it++)
	{
		cout << *it;
		if (it != --printableSet.end())
		{
			cout << ", ";
		}
	}
	cout << endl;
}

bool SetsAreEqual(set<int> s1, set<int> s2)
{
	return s1 == s2;
}

void TestCrossSet()
{
	set<int> set1, set2, intersection, rightResult;

	// set1 = set2 = {}
	intersection = CrossSet(set1, set2);
	assert(SetsAreEqual(intersection, {}));

	set1 = { 1, 2, 3 };
	// set2 = {};
	intersection = CrossSet(set1, set2);
	assert(SetsAreEqual(intersection, {}));

	set1 = { 1, 2, 3 };
	set2 = { 4, 5 };
	intersection = CrossSet(set1, set2);
	assert(SetsAreEqual(intersection, {}));

	set1 = { 1, 2, 3, 4 };
	set2 = { 4, 5 };
	intersection = CrossSet(set1, set2);
	assert(SetsAreEqual(intersection, { 4 }));
}

int main(int argc, char* argv[])
{
	//TestCrossSet;
	
	if (!CheckArgc(argc))
	{
		return 1;
	}

	if (auto n = StrToInt(argv[1]))
	{
		if (*n < 1)
		{
			cout << MSG_LESS_1;
			return 1;
		}

		PrintSet(CrossSet(CreateSet1(*n), CreateSet2(*n)));
	}
	else
	{
		cout << MSG_NOT_INTEGER;
		return 1;
	}

	return 0;
}

