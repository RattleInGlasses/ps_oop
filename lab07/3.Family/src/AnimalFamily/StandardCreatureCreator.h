#pragma once
template <typename Creature>
class CStandardCreatureCreator
{
public:
	Creature operator ()()const
	{
		return Creature();
	}
};

