#include "stdafx.h"
#include "Subscriber.h"

using namespace std;

namespace
{
	void CheckNameThrow(CName const &name)
	{
		if (name.GetValue() == "")
		{
			throw invalid_argument("A subscriber's name must not be empty");
		}
	}
}


CSubscriber::CSubscriber(CName const &name,
	CPostAddress const &address,
	initializer_list<string> const &phones,
	initializer_list<string> const &emails) :
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


size_t CSubscriber::GetPhonesCount() const
{
	return m_phones.size();
}


string const &CSubscriber::GetPhone(size_t index) const
{
	return m_phones.at(index);
}


string &CSubscriber::GetPhone(size_t index)
{
	return m_phones.at(index);
}


void CSubscriber::AddPhone(string const &phone)
{
	m_phones.push_back(phone);
}


void CSubscriber::DeletePhone(size_t index)
{
	assert(index < m_phones.size());
	m_phones.erase(m_phones.begin() + index);
}


void CSubscriber::SetPhone(size_t index, std::string const &value)
{
	m_phones.at(index) = value;
}


bool CSubscriber::HasPhones(std::vector<std::string> const &phonesToCheck) const
{
	return includes(m_phones.begin(), m_phones.end(), phonesToCheck.begin(), phonesToCheck.end());
}


size_t CSubscriber::GetEmailsCount() const
{
	return m_emails.size();
}


string const &CSubscriber::GetEmail(size_t index) const
{
	return m_emails.at(index);
}


string &CSubscriber::GetEmail(size_t index)
{
	return m_emails.at(index);
}


void CSubscriber::AddEmail(string const &email)
{
	m_emails.push_back(email);
}


void CSubscriber::DeleteEmail(size_t index)
{
	assert(index < m_emails.size());
	m_emails.erase(m_emails.begin() + index);
}


void CSubscriber::SetEmail(size_t index, std::string const &value)
{
	m_emails.at(index) = value;
}


bool CSubscriber::HasEmails(std::vector<std::string> const &emailsToCheck) const
{
	return includes(m_emails.begin(), m_emails.end(), emailsToCheck.begin(), emailsToCheck.end());
}


CPostAddress const &CSubscriber::GetAddress() const
{
	return m_address;
}


void CSubscriber::SetAddress(CPostAddress const &value)
{
	m_address = value;
}
