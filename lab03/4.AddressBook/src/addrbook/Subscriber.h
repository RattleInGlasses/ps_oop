#pragma once
#include "Name.h"
#include "PostAddress.h"
#include <vector>
class CSubscriber
{
private:
	typedef std::vector<std::string> EmailList;
	typedef std::vector<std::string> PhoneList;
public:
	CSubscriber(CName const &name,
		CPostAddress const &address = CPostAddress(),
		std::vector<std::string> const &phones = {},
		std::vector<std::string> const &emails = {});
public:
	CName const &GetName() const;
	void SetName(CName const &);

	CPostAddress const &GetAddress() const;
	void SetAddress(CPostAddress const &);

	std::vector<std::string> const &GetPhones() const;
	void SetPhones(std::vector<std::string> const &);

	std::vector<std::string> const &GetEmails() const;
	void SetEmails(std::vector<std::string> const &);


	bool Match(std::string const &name,
		CPostAddress const &address,
		std::vector<std::string> const &phones,
		std::vector<std::string> const &emails) const;
private:
	bool HavePhones(std::vector<std::string> const &) const;
	bool HaveEmails(std::vector<std::string> const &) const;
private:
	CName m_name;
	PhoneList m_phones;
	EmailList m_emails;
	CPostAddress m_address;
};

