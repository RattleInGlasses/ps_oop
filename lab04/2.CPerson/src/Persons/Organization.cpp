#include "stdafx.h"
#include "Organization.h"

using namespace std;
using boost::trim;

namespace
{
	void CheckNameThrow(string const &name)
	{
		if (name == "")
		{
			throw invalid_argument("The name must not be empty");
		}
	}
}


COrganization::COrganization(string const &name) :
m_name(name)
{
	trim(m_name);
	CheckNameThrow(m_name);
}


string const &COrganization::GetName() const
{
	return m_name;
}


void COrganization::SetName(string value)
{
	trim(value);
	CheckNameThrow(value);
	m_name = value;
}
