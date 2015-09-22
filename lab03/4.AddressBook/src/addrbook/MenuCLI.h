#pragma once
#include <iostream>
#include "AddressBook.h"
class CMenuCLI
{
public:
	CMenuCLI(std::istream &, std::ostream &);
	void Start(CAddressBook &);
private:
	void PrintMenuPrompt(std::string const &menuName) const;
	std::string ReadUserCommand() const;
	void PrintSubscriberInfo(std::string const &name,
		CPostAddress const &address,
		std::vector<std::string> const phones,
		std::vector<std::string> const emails) const;

	void MainMenu(CAddressBook &) const;
	void FindSubscribers(CAddressBook &) const;
	void ChooseSubscriber(CAddressBook &adressbook, std::string const &name, CPostAddress const &address, std::vector<std::string> const &phones, std::vector<std::string> const &emails) const;
	std::string ChooseSubscriberAction() const;
	void EditSubscriber(CSubscriber &) const;
	void AddSubscriber(CAddressBook &) const;

	void EditName(std::string &) const;
	
	void EditAddress(CPostAddress &) const;
	void EditCity(std::string &) const;
	void EditStreet(std::string &) const;
	void EditHouse(std::string &) const;
	void EditApartment(unsigned &) const;

	void EditPhones(std::vector<std::string> &) const;
	void ChoosePhone(std::vector<std::string> &) const;
	void ChoosePhoneAction(std::string &) const;
	void EditPhone(std::string &) const;
	void DeletePhone(std::string &) const;
	void AddPhone(std::vector<std::string> &) const;

	void EditEmails(std::vector<std::string> &) const;
	void ChooseEmail(std::vector<std::string> &) const;
	void ChooseEmailAction(std::string &) const;
	void EditEmail(std::string &) const;
	void DeleteEmail(std::string &) const;
	void AddEmail(std::vector<std::string> &) const;
private:
	std::istream &m_ist;
	std::ostream &m_ost;
};

