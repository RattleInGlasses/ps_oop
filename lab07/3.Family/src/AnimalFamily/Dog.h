#pragma once
#include "GenderedNamedCreature.h"
#include <string>
class CDog final :
	public CGenderedNamedCreature
{
public:
	CDog(std::string const &name, Gender const &gender) :
		CGenderedNamedCreature(name, gender)
	{
	}
};

