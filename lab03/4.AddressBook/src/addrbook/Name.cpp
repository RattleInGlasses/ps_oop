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
			result.insert(part);
		}

		return result;
	}

	string Lower(string const &str)
	{
		string result = str;
		boost::to_lower(result, locale(".866"));
		return result;
	}
}


CName::CName(string const &name) :
m_name(name)
{
	trim(m_name);
}


CName::CName(char const *pName) :
m_name(pName)
{
	trim(m_name);
}


CName &CName::operator =(std::string const &value)
{
	m_name = value;
	trim(m_name);
	return *this;
}

CName::operator std::string() const
{
	return m_name;
}


bool CName::Match(std::string const &name2Str) const
{
	auto nameParts1 = BreakNameIntoParts(Lower(m_name));
	auto nameParts2 = BreakNameIntoParts(Lower(name2Str));
	return includes(nameParts1.begin(), nameParts1.end(), nameParts2.begin(), nameParts2.end());
}

