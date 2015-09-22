#pragma once
#include "stdafx.h"
#include "Rational.h"
#include "MyMath.h"
#include <iostream>
#include <utility>

using namespace std;
using namespace MyMath;

// public methods

CRational::CRational(int numerator, int denominator) :
	m_numerator(numerator),
	m_denominator(denominator)
{
	if (0 == m_denominator)
	{
		m_numerator = 0;
		m_denominator = 1;
	}

	Normalize();
}


int CRational::GetNumerator() const
{
	return m_numerator;
}


int CRational::GetDenominator() const
{
	return m_denominator;
}


double CRational::ToDouble() const
{
	return double(m_numerator) / m_denominator;
}


CompoundFraction CRational::ToCompoundFraction() const
{
	auto integerPart = m_numerator / m_denominator;
	auto fractionalPart = *this - integerPart;

	return { integerPart, fractionalPart };
}


// operations

CRational const CRational::operator +() const
{
	return *this;
}


CRational const CRational::operator -() const
{
	CRational result(-m_numerator, m_denominator);
	return result;
}


CRational const operator +(CRational const &num1, CRational const &num2)
{
	return CRational(num1) += num2;
}


CRational const operator -(CRational const &num1, CRational const &num2)
{
	return num1 + (-num2);
}


CRational& CRational::operator +=(CRational const &num2)
{
	CRational num2Copy(num2);
	ToCommonDenominator(*this, num2Copy);

	m_numerator += num2Copy.m_numerator;
	
	Normalize();
	return *this;
}


CRational& CRational::operator -=(CRational const &num2)
{
	return *this += -num2;
}


CRational const operator *(CRational const &num1, CRational const &num2)
{
	return CRational(num1) *= num2;
}


CRational const operator /(CRational const &num1, CRational const &num2)
{
	return CRational(num1) /= num2;
}


CRational& CRational::operator *=(CRational const &num2)
{
	m_numerator   *= num2.GetNumerator();
	m_denominator *= num2.GetDenominator();
	
	Normalize();
	return *this;
}


CRational& CRational::operator /=(CRational const &num2)
{
	if (num2 != 0) // skip division by zero
	{
		int num2Numerator = num2.GetNumerator();
		m_numerator *= num2.GetDenominator();
		m_denominator *= num2Numerator;

		Normalize();
	}
	
	return *this;
}


bool operator ==(CRational const &num1, CRational const &num2)
{
	return ((num1.GetNumerator() == num2.GetNumerator()) && (num1.GetDenominator() == num2.GetDenominator()));
}


bool operator !=(CRational const &num1, CRational const &num2)
{
	return (!(num1 == num2));
}


bool operator <(CRational num1, CRational num2)
{
	CRational::ToCommonDenominator(num1, num2);
	
	return num1.GetNumerator() < num2.GetNumerator();
}


bool operator <=(CRational const &num1, CRational const &num2)
{
	return ((num1 < num2) || (num1 == num2));
}


bool operator >(CRational const &num1, CRational const &num2)
{
	return num2 < num1;
}


bool operator >=(CRational const &num1, CRational const &num2)
{
	return num2 <= num1;
}


ostream& operator << (ostream &output, CRational const &rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}


istream& operator >> (istream &input, CRational &rational)
{
	streamoff startPos = input.tellg();
	
	int numerator, denominator;
	if ((input >> numerator)
		&& (input.get() == '/')
		&& (input >> denominator))
	{
		rational = { numerator, denominator };
	}
	else
	{
		input.seekg(startPos);
		input.setstate(input.rdstate() | istream::failbit);
	}

	return input;
}


ostream& operator << (ostream &output, CompoundFraction	const &compound)
{
	if (compound.first < 0)
	{
		output << '-';
	}
	output << '(' << abs(compound.first) << ' ' << abs(compound.second.GetNumerator()) << '/' << compound.second.GetDenominator() << ')';
	return output;
}


// static methods


void CRational::ToCommonDenominator(CRational &num1, CRational &num2)
{
	int newDenominator = LeastCommonMultiple(num1.m_denominator, num2.m_denominator);
	num1.m_numerator *= newDenominator / num1.m_denominator;
	num2.m_numerator *= newDenominator / num2.m_denominator;
	num1.m_denominator = num2.m_denominator = newDenominator;
}


// private methods


void CRational::Normalize()
{
	// � ������ ������ ����������, � ������������� � "����������" �������������� �����
	// �������� ��, � ������� ��������� ����� ����, � ����������� ������ �����������,
	// ������� ��������������� �������������� �������� � ��� �������
	if (0 == m_numerator)
	{
		m_denominator = 1;
	}
	if (0 > m_denominator)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}

	int gcd = GreatesCommonDivisor(m_numerator, m_denominator);
	m_denominator /= gcd;
	m_numerator   /= gcd;
}
