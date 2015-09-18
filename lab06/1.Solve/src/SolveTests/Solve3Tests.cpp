#include "stdafx.h"
#include "..\Solve\Solve.h"

using namespace std;
using namespace solve;

BOOST_AUTO_TEST_SUITE(Solve3_works_correctly_when)

	double CubicFunctionPointValue(double a, double b, double c, double d, double x)
	{
		return a*pow(x, 3) + b*pow(x, 2) + c*pow(x, 1) + d;
	}

	void CheckRoots(EquationRoot3 const &rootsContainer, double a, double b, double c, double d)
	{
		for (int i = 0; i < rootsContainer.numRoots; ++i)
		{
			BOOST_CHECK_SMALL(CubicFunctionPointValue(a, b, c, d, rootsContainer.roots[i]), 1e-10);
		}
	}

	void FindAndCheckCubicEquationRoots(double a, double b, double c, double d)
	{
		CheckRoots(Solve3(a, b, c, d), a, b, c, d);
	}


	BOOST_AUTO_TEST_CASE(S_more_than_zero)
	{
		FindAndCheckCubicEquationRoots(1, 2, -10, 1);
	}

	BOOST_AUTO_TEST_CASE(S_equal_zero)
	{
		FindAndCheckCubicEquationRoots(1, 1, 0, 0);
	}

	BOOST_AUTO_TEST_CASE(S_less_than_zero)
	{
		// Q==0
		FindAndCheckCubicEquationRoots(1, 3, 3, 0);
		// Q < 0
		FindAndCheckCubicEquationRoots(1, 3, 6, 1);
		// Q > 0
		FindAndCheckCubicEquationRoots(1, 6, 3, 1);
	}
	
BOOST_AUTO_TEST_SUITE_END()