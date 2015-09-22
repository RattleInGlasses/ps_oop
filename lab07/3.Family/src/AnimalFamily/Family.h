#pragma once
#include "StandardCreatureCreator.h"
#include "StandardGenderDeterminer.h"
#include "GenderedNamedCreature.h"
template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
class CFamily final
{
public:
	CFamily(Creature const &spouse1, Creature const &spouse2);
	Creature GetSpouse1()const;
	Creature GetSpouse2()const;
	Creature GetChild(size_t index)const;
	size_t GetChildCount()const;
	Creature MakeChild(CreatureCreator const &creatureCreator = CreatureCreator());
private:
	Creature m_spouse1;
	Creature m_spouse2;
	std::vector<Creature> m_children;
};

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
CFamily<Creature, CreatureCreator, GenderDeterminer>::CFamily(Creature const &spouse1, Creature const &spouse2) :
m_spouse1(spouse1),
m_spouse2(spouse2)
{
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
Creature CFamily<Creature, CreatureCreator, GenderDeterminer>::GetSpouse1() const
{
	return m_spouse1;
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
Creature CFamily<Creature, CreatureCreator, GenderDeterminer>::GetSpouse2() const
{
	return m_spouse2;
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
Creature CFamily<Creature, CreatureCreator, GenderDeterminer>::GetChild(size_t index) const
{
	/*if (index > m_children.size())
	{
	throw std::out_of_range("out of range when attempt to access a family child");
	}
	return m_children[index];*/

	/*try
	{
	return m_children.at(index);
	}
	catch (std::out_of_range &e)
	{
	throw std::out_of_range("out of range when attempt to access a family child");
	throw;
	}*/

	return m_children.at(index);
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
size_t CFamily<Creature, CreatureCreator, GenderDeterminer>::GetChildCount() const
{
	return m_children.size();
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
Creature CFamily<Creature, CreatureCreator, GenderDeterminer>::MakeChild(CreatureCreator const &creatureCreator)
{
	GenderDeterminer genderDeterminer;
	Gender gender1 = genderDeterminer(GetSpouse1());
	Gender gender2 = genderDeterminer(GetSpouse2());
	if (gender1 == gender2)
	{
		throw std::logic_error("can't create a child in a same-sex family");
	}

	Creature child = creatureCreator();
	m_children.push_back(child);
	return child;
}
