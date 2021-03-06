#pragma once
#include "GenderedNamedCreature.h"
#include <string>
template <typename Pet>
class CPetCreator final
{
public:
	CPetCreator(std::string const &name, Gender const &gender) :
		m_name(name),
		m_gender(gender)
	{
	}

	Pet operator ()()const
	{
		return Pet(m_name, m_gender);
	}
private:
	std::string m_name;
	Gender m_gender;
};

