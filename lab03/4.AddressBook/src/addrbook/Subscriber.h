#pragma once
#include "Name.h"
#include "PostAddress.h"
#include <initializer_list>
#include <vector>
class CSubscriber
{
private:
	typedef std::vector<std::string> EmailList;
	typedef std::vector<std::string> PhoneList;
public:
	CSubscriber(CName const &name,
		CPostAddress const &address = CPostAddress(),
		std::initializer_list<std::string> const &phones = {},
		std::initializer_list<std::string> const &emails = {});
public:
	CName const &GetName() const;
	void SetName(CName const &);
	
	size_t GetPhonesCount() const;
	std::string const &GetPhone(size_t) const;
	std::string       &GetPhone(size_t);
	void AddPhone(std::string const &);
	void DeletePhone(size_t);
	void SetPhone(size_t, std::string const &);
	bool HasPhones(std::vector<std::string> const &) const;

	size_t GetEmailsCount() const;
	std::string const &GetEmail(size_t) const;
	std::string       &GetEmail(size_t);
	void AddEmail(std::string const &);
	void DeleteEmail(size_t);
	void SetEmail(size_t, std::string const &);
	bool HasEmails(std::vector<std::string> const &) const;

	CPostAddress const &GetAddress() const;
	void SetAddress(CPostAddress const &);
private:
	CName m_name;
	PhoneList m_phones;
	EmailList m_emails;
	CPostAddress m_address;
};

