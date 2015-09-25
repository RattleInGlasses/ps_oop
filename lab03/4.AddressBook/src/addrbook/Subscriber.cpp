#include "stdafx.h"
#include "Subscriber.h"

using namespace std;

namespace
{
	void CheckNameThrow(CName const &name)
	{
		if (string(name) == "")
		{
			throw invalid_argument("A subscriber's name must not be empty");
		}
	}

	bool VectorHasElements(vector<string> const &base, vector<string> elements)
	{
		if (elements.size() == 0)
		{
			return true;
		}

		sort(elements.begin(), elements.end());
		return includes(base.begin(), base.end(), elements.begin(), elements.end());
	}
}


CSubscriber::CSubscriber(CName const &name,
	CPostAddress const &address,
	vector<string> const &phones,
	vector<string> const &emails) :
m_name(name),
m_address(address),
m_phones(phones),
m_emails(emails)
{
	CheckNameThrow(m_name);
}

CName const &CSubscriber::GetName() const
{
	return m_name;
}


void CSubscriber::SetName(CName const &value)
{
	CheckNameThrow(value);
	m_name = value;
}


vector<string> const &CSubscriber::GetPhones() const
{
	return m_phones;
}


void CSubscriber::SetPhones(std::vector<std::string> const &value)
{
	m_phones = value;
}


vector<string> const &CSubscriber::GetEmails() const
{
	return m_emails;
}


void CSubscriber::SetEmails(vector<string> const &value)
{
	m_emails = value;
}


CPostAddress const &CSubscriber::GetAddress() const
{
	return m_address;
}


void CSubscriber::SetAddress(CPostAddress const &value)
{
	m_address = value;
}


bool CSubscriber::Match(string const &name,
	CPostAddress const &address,
	vector<string> const &phones,
	vector<string> const &emails) const
{
	return ((m_name.Match(name))
		&& (m_address.Match(address))
		&& (HavePhones(phones))
		&& (HaveEmails(emails)));
}


// private methods

bool CSubscriber::HavePhones(std::vector<std::string> const &phonesToCheck) const
{
	return VectorHasElements(m_phones, phonesToCheck);
}


bool CSubscriber::HaveEmails(std::vector<std::string> const &emailsToCheck) const
{
	return VectorHasElements(m_emails, emailsToCheck);
}
