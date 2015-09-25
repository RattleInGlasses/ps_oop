#pragma once
#include <iostream>
#include "AddressBook.h"
class CMenuCLI
{
public:
	CMenuCLI(std::istream &, std::ostream &);
	void Start(CAddressBook &);
	CMenuCLI& operator=(const CMenuCLI &) = delete;
private:
	void PrintMenuPrompt(std::string const &menuName) const;
 	std::string ReadUserCommand() const;

 	void MainMenu(CAddressBook &) const;
	void ShowSubscribers(CAddressBook const &) const;
	void ShowSubscriberRecords(CAddressBook const &, std::vector<size_t> const &) const;
	void ShowSubscriberRecord(CSubscriber const &) const;
	void EditSubscribers(CAddressBook &) const;
	void EditSubscriberRecords(CAddressBook &, std::vector<size_t> const &) const;
	bool EditSubscriberRecord(CSubscriber &) const;
	void DeleteSubscriber(CAddressBook &) const;
	void DeleteSubscriberRecord(CAddressBook &, std::vector<size_t> const &) const;
	void AddSubscriber(CAddressBook &) const;

	boost::optional<std::vector<size_t>> FindSubscribers(CAddressBook const &) const;

	void UpdateName(std::string &) const;
 	
 	void UpdateAddress(CPostAddress &) const;
 	void UpdateCity(std::string &) const;
 	void UpdateStreet(std::string &) const;
 	void UpdateHouse(std::string &) const;
 	void UpdateApartment(unsigned &) const;
 
 	void EditPhones(std::vector<std::string> &) const;
	void UpdatePhones(std::vector<std::string> &) const;
	void UpdatePhone(std::string &) const;
 	void DeletePhones(std::vector<std::string> &) const;
 	void AddPhone(std::vector<std::string> &) const;

 	void EditEmails(std::vector<std::string> &) const;
	void UpdateEmails(std::vector<std::string> &) const;
 	void UpdateEmail(std::string &) const;
 	void DeleteEmails(std::vector<std::string> &) const;
 	void AddEmail(std::vector<std::string> &) const;
private:
	std::istream &m_ist;
	std::ostream &m_ost;
};

