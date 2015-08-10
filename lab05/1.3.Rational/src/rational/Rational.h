#pragma once
class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);
	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;
	std::pair<int, CRational> ToCompoundFraction()const;

	CRational const operator +() const;
	CRational const operator -() const;
	CRational &operator +=(CRational const &value);
	CRational &operator -=(CRational const &value);
	CRational &operator *=(CRational const &value);
	CRational &operator /=(CRational const &value);

	friend void ToCommonDenominator(CRational &num1, CRational &num2);
private:
	void Normalize();
private:
	int m_numerator;
	int m_denominator;
};

CRational const operator +(CRational const &num1, CRational const &num2);
CRational const operator -(CRational const &num1, CRational const &num2);
CRational const operator *(CRational const &num1, CRational const &num2);
CRational const operator /(CRational const &num1, CRational const &num2);
bool operator ==(CRational const &num1, CRational const &num2);
bool operator !=(CRational const &num1, CRational const &num2);
bool operator <(CRational num1, CRational num2);
bool operator <=(CRational const &num1, CRational const &num2);
bool operator >(CRational const &num1, CRational const &num2);
bool operator >=(CRational const &num1, CRational const &num2);
std::ostream& operator << (std::ostream &ost, CRational const &rational);
std::istream& operator >> (std::istream &ist, CRational &rational);
std::ostream& operator << (std::ostream &ost, std::pair<int, CRational>	const &compound);
