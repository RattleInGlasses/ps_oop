#pragma once
#include "Organization.h"
#include <string>
class CUniversity :
	public COrganization
{
public:
	CUniversity(std::string const &name);
	~CUniversity() override final {};
};

