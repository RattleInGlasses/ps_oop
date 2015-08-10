#include "stdafx.h"
#include <cstdlib>
#include "MyMath.h"


int CMyMath::GreatesCommonDivisor(int num1, int num2)
{
	return ((0 == num1) && (0 == num2)) ? -1 :
		(0 == num2) ? abs(num1) :
		GreatesCommonDivisor(num2, num1 % num2);
}


int CMyMath::LeastCommonMultiple(int num1, int num2)
{
	return ((0 == num1) || (0 == num2)) ? -1 :
		abs(num1 * num2) / GreatesCommonDivisor(num1, num2);
}
