#pragma once
#include "GenderedNamedCreature.h"
#include <string>
class CCat final : 
	public CGenderedNamedCreature
{
public:
	CCat(std::string const &name, Gender const &gender) :
		CGenderedNamedCreature(name, gender)
	{
	}
};

