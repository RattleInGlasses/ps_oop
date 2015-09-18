#include "stdafx.h"
#include "Solve.h"

using namespace std;

namespace solve
{
	double Arcosh(double value)
	{
		return acosh(value);
	}

	double Cosh(double value)
	{
		return cosh(value);
	}

	double Arsinh(double value)
	{
		return asinh(value);
	}

	double Sinh(double value)
	{
		return sinh(value);
	}

	int Sign(double value)
	{
		return (value < 0) ? -1 :
			(value > 0) ? 1 : 0;
	}

	bool FractionClose(double a, double b)
	{
		return abs(a - b) < DBL_EPSILON;
	}

	bool FractionMore(double a, double b)
	{
		return (a - b) > DBL_EPSILON;
	}

	EquationRoot3 Solve3ReducedWithSLessThanZero(double a, double c, double R, double Q)
	{
		EquationRoot3 result;
		result.numRoots = 1;
		if (FractionClose(Q, 0))
		{
			result.roots[0] = -cbrt(c - pow(a, 3)/27) - a/3;
		}
		else
		{
			auto fInverse = (Q > 0) ? Arcosh : Arsinh;
			auto fStraight = (Q > 0) ? Cosh : Sinh;

			double phi = (fInverse(abs(R) / sqrt(abs(pow(Q, 3))))) / 3.0;
			result.roots[0] = -2*Sign(R)*sqrt(abs(Q))*fStraight(phi) - a/3;
		}

		return result;
	}
	
	EquationRoot3 Solve3ReducedWithSMoreThanZero(double a, double R, double Q)
	{
		EquationRoot3 result;
		result.numRoots = 3;
		double phi = (acos(R / sqrt(pow(Q, 3)))) / 3.0;

		result.roots[0] = -2*sqrt(Q)*cos(phi) - a/3;
		result.roots[1] = -2*sqrt(Q)*cos(phi + 2*M_PI/3) - a/3;
		result.roots[2] = -2*sqrt(Q)*cos(phi - 2*M_PI/3) - a/3;

		return result;
	}

	EquationRoot3 Solve3ReducedWithSEqualZero(double a, double R)
	{
		EquationRoot3 result;
		result.numRoots = 2;
		result.roots[0] = -2*cbrt(R) - a/3;
		result.roots[1] = cbrt(R) - a/3;

		return result;
	}

	EquationRoot3 Solve3Reduced(double a, double b, double c)
	{
		double Q = (a*a - 3*b) / 9;
		double R = (2*pow(a, 3) - 9*a*b + 27*c) / 54;
		double S = pow(Q, 3) - pow(R, 2);

		if (FractionClose(S, 0))
		{
			return Solve3ReducedWithSEqualZero(a, R);
		}		
		else if (S > 0)
		{
			return Solve3ReducedWithSMoreThanZero(a, R, Q);
		}
		else
		{
			return Solve3ReducedWithSLessThanZero(a, c, R, Q);
		}
	}
	
	EquationRoot3 Solve3(double a, double b, double c, double d)
	{
		if (a == 0)
		{
			throw invalid_argument("The equation must be cubic. The first coefficient must not be zero.");
		}

		return Solve3Reduced(b/a, c/a, d/a);
	}


	EquationRoot4 DepressedRootsToNormalRoots(EquationRoot4 const &depressedRoots, double a, double b)
	{
		EquationRoot4 result;
		result.numRoots = depressedRoots.numRoots;
		for (int i = 0; i < depressedRoots.numRoots; ++i)
		{
			result.roots[i] = depressedRoots.roots[i] - b / (4 * a);
		}
		return result;
	}

	boost::optional<double> GetPositiveRoot(EquationRoot3 const &rootContainer)
	{
		for (int i = 0; i < rootContainer.numRoots; ++i)
		{
			if (FractionMore(rootContainer.roots[i], 0))
			{
				return  rootContainer.roots[i];
			}
		}
		return boost::none;
	}

	void FindRootsWhenQUnequalZeroUsingDiscriminant1(EquationRoot4 &rootsContainer, double D, double z0)
	{
		if (FractionMore(D, 0))
		{
			rootsContainer.numRoots += 2;
			rootsContainer.roots[rootsContainer.numRoots - 2] = (sqrt(2*z0) + sqrt(D)) / 2;
			rootsContainer.roots[rootsContainer.numRoots - 1] = (sqrt(2*z0) - sqrt(D)) / 2;
		}
		else if (FractionClose(D, 0))
		{
			rootsContainer.numRoots += 1;
			rootsContainer.roots[rootsContainer.numRoots - 1] = sqrt(2*z0) / 2;
		}
	}

	void FindRootsWhenQUnequalZeroUsingDiscriminant2(EquationRoot4 &rootsContainer, double D, double z0)
	{
		if (FractionMore(D, 0))
		{
			rootsContainer.numRoots += 2;
			rootsContainer.roots[rootsContainer.numRoots - 2] = (-sqrt(2*z0) + sqrt(D)) / 2;
			rootsContainer.roots[rootsContainer.numRoots - 1] = (-sqrt(2*z0) - sqrt(D)) / 2;
		}
		else if (FractionClose(D, 0))
		{
			rootsContainer.numRoots += 1;
			rootsContainer.roots[rootsContainer.numRoots - 1] = -sqrt(2*z0) / 2;
		}
	}

	EquationRoot4 Solve4DepressedWithQUnequalZero(double p, double q, double r)
	{
		EquationRoot4 result;
		result.numRoots = 0;

		double a = p;
		double b = (p*p - 4*r) / 4;
		double c = -q*q / 8;
		EquationRoot3 intermediateRoots = Solve3Reduced(a, b, c);

		if (auto z0 = GetPositiveRoot(intermediateRoots))
		{
			double D1 = 2*(*z0) - 4*(p/2 + *z0 + q/(2*sqrt(2*(*z0))));
			FindRootsWhenQUnequalZeroUsingDiscriminant1(result, D1, *z0);
			double D2 = 2*(*z0) - 4*(p/2 + *z0 - q/(2*sqrt(2*(*z0))));
			FindRootsWhenQUnequalZeroUsingDiscriminant2(result, D2, *z0);
		}

		return result;
	}

	void FindRootsWhenQEqualZeroUsingDiscriminant(EquationRoot4 &rootsContainer, double D)
	{
		if (D > 0)
		{
			rootsContainer.numRoots += 2;
			rootsContainer.roots[rootsContainer.numRoots - 2] = sqrt(D / 2);
			rootsContainer.roots[rootsContainer.numRoots - 1] = -rootsContainer.roots[rootsContainer.numRoots - 2];
		}
		else if (D == 0)
		{
			rootsContainer.numRoots += 1;
			rootsContainer.roots[rootsContainer.numRoots - 1] = 0;
		}
	}

	EquationRoot4 Solve4DepressedWithQEqualZero(double p, double r)
	{
		EquationRoot4 result;
		result.numRoots = 0;

		double D1 = p*p - 4*r;
		if (D1 >= 0)
		{
			FindRootsWhenQEqualZeroUsingDiscriminant(result, (-p - sqrt(D1)));
			FindRootsWhenQEqualZeroUsingDiscriminant(result, (-p + sqrt(D1)));
		}

		return result;
	}

	EquationRoot4 Solve4Depressed(double p, double q, double r)
	{
		if (FractionClose(q, 0))
		{
			return Solve4DepressedWithQEqualZero(p, r);
		}
		else
		{
			return Solve4DepressedWithQUnequalZero(p, q, r);
		}
	}

	EquationRoot4 Solve4(double a, double b, double c, double d, double e)
	{
		if (a == 0)
		{
			throw invalid_argument("The equation must be quadric. The first coefficient must not be zero.");
		}

		double p = (8*a*c - 3*pow(b, 2)) / (8*pow(a, 2));
		double q = (8*a*a*d + pow(b, 3) - 4*a*b*c) / (8*pow(a, 3));
		double r = (16*a*b*b*c - 64*a*a*b*d - 3*pow(b, 4) + 256*pow(a, 3)*e) / (256*pow(a, 4));
		
		EquationRoot4 depressedRoots = Solve4Depressed(p, q, r);
		EquationRoot4 roots = DepressedRootsToNormalRoots(depressedRoots, a, b);

		if (roots.numRoots == 0)
		{
			throw domain_error("There are no real roots.");
		}
		return roots;
	}
}

