#include "stdafx.h"
#include "..\Solve\Solve.h"

using namespace std;
using namespace solve;

BOOST_AUTO_TEST_SUITE(Solve4_works_correctly_when)

	double QuadricFunctionPointValue(double a, double b, double c, double d, double e, double x)
	{
		return a*pow(x, 4) + b*pow(x, 3) + c*pow(x, 2) + d*x + e;
	}

	void CheckRoots(EquationRoot4 const &rootsContainer, double a, double b, double c, double d, double e)
	{
		for (int i = 0; i < rootsContainer.numRoots; ++i)
		{
			BOOST_CHECK_SMALL(QuadricFunctionPointValue(a, b, c, d, e, rootsContainer.roots[i]), 1e-10);
		}
	}

	void FindAndCheckCubicEquationRoots(double a, double b, double c, double d, double e)
	{
		CheckRoots(Solve4(a, b, c, d, e), a, b, c, d, e);
	}

	void CheckZeroRoots(double a, double b, double c, double d, double e)
	{
		BOOST_CHECK_THROW(Solve4(a, b, c, d, e), domain_error);
	}


	BOOST_AUTO_TEST_CASE(q_unequal_0)
	{
		FindAndCheckCubicEquationRoots(10, 20, 11, 12, -16);
	}


	BOOST_AUTO_TEST_CASE(q_equal_0)
	{
		CheckZeroRoots(1, 2, 2, 1, 10);
		FindAndCheckCubicEquationRoots(1, 0, 0, 0, -16);
	}

BOOST_AUTO_TEST_SUITE_END()