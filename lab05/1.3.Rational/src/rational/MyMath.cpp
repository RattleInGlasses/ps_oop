#include "stdafx.h"
#include <cstdlib>
#include "MyMath.h"

namespace MyMath
{
	int GreatesCommonDivisor(int num1, int num2)
	{
		for (;;)
		{
			if ((0 == num1) && (0 == num2))
			{
				return -1;
			}
			if (0 == num2)
			{
				return abs(num1);
			}

			int oldNum2 = num2;
			num2 = num1 % num2;
			num1 = oldNum2;
		}
	}


	int LeastCommonMultiple(int num1, int num2)
	{
		return ((0 == num1) || (0 == num2)) ? -1 :
			abs(num1 * num2) / GreatesCommonDivisor(num1, num2);
	}
}
