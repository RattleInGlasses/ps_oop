#include "stdafx.h"
#include "Person.h"

using namespace std;
using boost::trim;

namespace
{
	void CheckHeightThrow(unsigned newHeight)
	{
		if (newHeight == 0)
		{
			throw invalid_argument("Height must be more than 0");
		}
	}

	void CheckWeightThrow(unsigned weight)
	{
		if (weight == 0)
		{
			throw invalid_argument("Weight must be more than 0");
		}
	}

	void CheckNameThrow(string const &name)
	{
		if (name == "")
		{
			throw invalid_argument("Name must not be empty");
		}
	}
}


CPerson::CPerson(Gender gender, unsigned age, std::string const &name, unsigned height, unsigned weight) :
m_gender(gender),
m_age(age),
m_name(name),
m_height(height),
m_weight(weight)
{
	trim(m_name);
	CheckNameThrow(m_name);
	CheckHeightThrow(m_height);
	CheckWeightThrow(m_weight);
}


Gender CPerson::GetGender() const
{
	return m_gender;
}


unsigned CPerson::GetAge() const
{
	return m_age;
}


string const &CPerson::GetName() const
{
	return m_name;
}


unsigned CPerson::GetHeight() const
{
	return m_height;
}


unsigned CPerson::GetWeight() const
{
	return m_weight;
}


void CPerson::SetAge(unsigned value)
{
	if (value <= m_age)
	{
		throw invalid_argument("Age can only increase");
	}
	m_age = value;
}


void CPerson::SetName(std::string value)
{
	trim(value);
	CheckNameThrow(value);
	m_name = value;
}


void CPerson::SetHeight(unsigned value)
{
	if (value <= m_height)
	{
		throw invalid_argument("Height can only increase");
	}
	m_height = value;
}


void CPerson::SetWeight(unsigned value)
{
	CheckWeightThrow(value);
	m_weight = value;
}
