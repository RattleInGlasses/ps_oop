#pragma once
#include <string>
template <typename Human>
class CHumanCreator final
{
public:
	CHumanCreator(std::string const &name, Gender const &gender, unsigned birthCertificate) :
		m_name(name),
		m_gender(gender),
		m_birthCertificate(birthCertificate)
	{
	}

	Human operator ()()const
	{
		return Human(m_name, m_gender, m_birthCertificate);
	}
private:
	std::string m_name;
	Gender m_gender;
	unsigned m_birthCertificate;
};

