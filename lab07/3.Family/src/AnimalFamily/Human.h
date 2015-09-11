#pragma once
#include "GenderedNamedCreature.h"
#include <string>
class CHuman final :
	public CGenderedNamedCreature
{
public:
	CHuman(std::string const &name, Gender const &gender, unsigned birthCertificate);
	unsigned GetBirthCertificate() const;
private:
	unsigned m_birthCertificate;
};

CHuman::CHuman(std::string const &name, Gender const &gender, unsigned birthCertificate) :
CGenderedNamedCreature(name, gender),
m_birthCertificate(birthCertificate)
{
}

unsigned CHuman::GetBirthCertificate() const
{
	return m_birthCertificate;
}

