#pragma once
class CRational
{
public:
	typedef std::pair<int, CRational> CompoundFraction;

	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;
	CompoundFraction ToCompoundFraction()const;

	CRational const operator +() const;
	CRational const operator -() const;
	CRational &operator +=(CRational const &value);
	CRational &operator -=(CRational const &value);
	CRational &operator *=(CRational const &value);
	CRational &operator /=(CRational const &value);

	static void ToCommonDenominator(CRational &num1, CRational &num2);
private:
	void Normalize();
private:
	int m_numerator;
	int m_denominator;
};
typedef CRational::CompoundFraction CompoundFraction;

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
std::ostream& operator << (std::ostream &ost, CompoundFraction	const &compound);
