#pragma once
#include "GenderedNamedCreature.h"
template <typename Creature>
class CStandardGenderDeterminer
{
public:
	Gender operator()(Creature const& creature)const
	{
		return creature.GetGender();
	}
};

