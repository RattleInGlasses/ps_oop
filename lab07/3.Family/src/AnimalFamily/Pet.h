#pragma once
#include "GenderedNamedCreature.h"
template <typename Tag>
class CPet final : public CGenderedNamedCreature
{
public:
	CPet(std::string const &name, Gender const &gender) :
		CGenderedNamedCreature(name, gender)
	{
	}
};
