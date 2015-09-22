#include "stdafx.h"
#include "Name.h"

using namespace std;
using boost::trim;

namespace
{
	multiset<string> BreakNameIntoParts(string const &name)
	{
		multiset<string> result;
		istringstream iss(name);
		string part;
		while (iss >> part)
		{
			boost::to_lower(part);
			result.insert(part);
		}

		return result;
	}
}


CName::CName(string const &name) :
m_data(name)
{
	trim(m_data);
}


string CName::GetValue() const
{
	return m_data;
}


void CName::SetValue(string const &value)
{
	m_data = value;
	trim(m_data);
}


bool CName::operator ==(string const &name2Str) const
{
	auto nameParts1 = BreakNameIntoParts(m_data);
	auto nameParts2 = BreakNameIntoParts(name2Str);
	return includes(nameParts1.begin(), nameParts1.end(), nameParts2.begin(), nameParts2.end());
}


bool CName::operator !=(string const &name2Str) const
{
	return !(*this == name2Str);
}
