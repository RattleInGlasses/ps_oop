#pragma once
#include <string>
class COrganization
{
public:
	COrganization(std::string const &name);
	virtual ~COrganization() {};
public:
	std::string const &GetName() const;
	void SetName(std::string value);
private:
	std::string m_name;
};

