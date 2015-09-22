#include "stdafx.h"
#include "Company.h"

using namespace std;

CCompany::CCompany(std::string const &name, string const &website /* = "" */) :
COrganization(name),
m_website(website)
{
}


void CCompany::SetWebsite(string const &value)
{
	m_website = value;
}


string const &CCompany::GetWebsite()
{
	return m_website;
}

