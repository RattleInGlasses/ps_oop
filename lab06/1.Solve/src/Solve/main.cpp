// Solve.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Solve.h"
#include <float.h>

using namespace std;
using namespace solve;

bool ReadAnswer(istream &input)
{
	string answerString;
	bool gotAnswer = false;
	bool result;
	while (!gotAnswer)
	{
		input >> answerString;
		if ((answerString == "Y") || (answerString == "y"))
		{
			gotAnswer = true;
			result = true;
		}
		if ((answerString == "N") || (answerString == "n"))
		{
			gotAnswer = true;
			result = false;
		}
	}
	return result;
}

void PrintRoots(ostream &ost, EquationRoot4 const &rootContainer)
{
	ost << "Roots are:" << endl;
	for (int i = 0; i < rootContainer.numRoots; ++i)
	{
		ost << "x" << i + 1 << " = " << rootContainer.roots[i] << endl;
	}
}

void FindAndPrintSolution(ostream &ost, double a, double b, double c, double d, double e)
{
	try
	{
		PrintRoots(ost, Solve4(a, b, c, d, e));
	}
	catch (invalid_argument &e)
	{
		ost << "Error: " << e.what() << endl;
	}
	catch (domain_error &e)
	{
		ost << e.what() << endl;
	}
}

double ReadDouble(istream &input)
{
	double result;
	string line;
	istringstream inputString;
	while (true)
	{
		input >> line;
		inputString.clear();
		inputString.str(line);
		if (inputString >> result)
		{
			return result;
		}
	}
}

void ReadEquationCoefficients(istream &ist, ostream &ost, double &a, double &b, double &c, double &d, double &e)
{
	ost << "Please input equation coefficients" << endl;
	ost << "a = ";
	a = ReadDouble(ist);
	ost << "b = ";
	b = ReadDouble(ist);
	ost << "c = ";
	c = ReadDouble(ist);
	ost << "d = ";
	d = ReadDouble(ist);
	ost << "e = ";
	e = ReadDouble(ist);
}

int _tmain()
{
	cout << "The program calculates roots of a quadric equation" << endl;
	cout << "a*x^4 + b*x^3 + c*x^2 + d*x + e = 0" << endl;

	do
	{
		double a, b, c, d, e;
		ReadEquationCoefficients(cin, cout, a, b, c, d, e);
		FindAndPrintSolution(cout, a, b, c, d, e);
		
		cout << endl << "Do you want to solve one more equation? (Y/N) ";
	} while (ReadAnswer(cin));
	
	return 0;
}

