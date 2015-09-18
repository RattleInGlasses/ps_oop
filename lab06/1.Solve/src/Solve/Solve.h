#pragma once
namespace solve
{
	struct EquationRoot3
	{
		int numRoots;
		double roots[3];
	};

	struct EquationRoot4
	{
		int numRoots;
		double roots[4];
	};

	EquationRoot3 Solve3(double a, double b, double c, double d);
	EquationRoot4 Solve4(double a, double b, double c, double d, double e);
}
