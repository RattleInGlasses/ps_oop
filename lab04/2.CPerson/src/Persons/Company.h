#pragma once
#include "Organization.h"
#include <string>
class CCompany :
	public COrganization
{
public:
	CCompany(std::string const &name, std::string const &website = "");
	virtual ~CCompany() override final {};
public:
	void SetWebsite(std::string const &value);
	std::string const &GetWebsite() const;
private:
	std::string m_website;
};

