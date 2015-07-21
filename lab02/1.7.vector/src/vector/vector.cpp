// vector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "ProcessVector.h"
#include "TestProcessVector.h"

using namespace std;

vector<double> ReadInputVector();
bool IsStreamEoln(istream &sin);
void SkipSpaces(istream &sin);

int main()
{
	//TestProcessVector();

	cout << "The program reads array, adds to it's every element sum of it's 3 minimal elements, output result in ascending order.\n";
	cout << "================================================================================\n";

	vector<double> vectorOfDouble = ReadInputVector();
	ProcessVector(vectorOfDouble);

	copy(vectorOfDouble.begin(), vectorOfDouble.end(), ostream_iterator<double>(cout, " "));
	cout << '\n';

	return 0;
}

vector<double> ReadInputVector()
{
	cout << "Enter a sequence of real numbers.\n";
	cout << "The amount of numbers must be no less than 3.\n";
	cout << "The delimiter between numbers must be one or more spaces.\n";

	double curNum;
	size_t count = 0;
	vector<double> vectorOfDouble;
	bool endOfInput = false;
	while (!endOfInput)
	{
		if (IsStreamEoln(cin))
		{
			endOfInput = true;
		}
		else if (!(cin >> curNum))
		{
			cout << "You need to enter a sequence of real numbers. Try again.\n";
			cin.clear();
			string garbage;
			getline(cin, garbage);
			count = 0;
			vectorOfDouble.clear();
		}
		else
		{
			count++;
			vectorOfDouble.push_back(curNum);
		}
		SkipSpaces(cin);
	}

	return vectorOfDouble;
}

bool IsStreamEoln(istream &sin)
{
	return sin.peek() == '\n';
}

void SkipSpaces(istream &sin)
{
	while ((sin.peek() == ' ') || (sin.peek() == '\t'))
	{
		sin.ignore();
	}
}

