#include "stdafx.h"
#include "MenuCLI.h"

using namespace std;
using boost::trim;

namespace
{
	map<string, vector<string>> const menuPrompt = 
	{
		{
			"MainMenu",
			{
				{ "1. Show subscriber records" },
				{ "2. Edit subscriber records"},
				{ "3. Delete subscriber record" },
				{ "4. Add new subscriber record" },
				{ "Q. Exit the program" }
			}
		},
		{
			"AddSubscriber",
			{
				{ "1. Edit name" },
				{ "2. Edit address" },
				{ "3. Edit phones" },
				{ "4. Edit emails" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"FindSubscribers",
			{
				{ "1. Edit name" },
				{ "2. Edit address" },
				{ "3. Edit phones" },
				{ "4. Edit emails" },
				{ "A. Find it" },
				{ "C. Cancel" }
			}
		},
		{
			"ShowSubscriberRecords",
			{
				{ "<id>. Show subscriber" },
				{ "C. Cancel" }
			}
		},
		{
			"ShowSubscriberRecord",
			{
				{ "C. Cancel" }
			}
		},
		{
			"EditSubscriberRecords",
			{
				{ "<id>. Edit subscriber" },
				{ "C. Cancel" }
			}
		},
		{
			"EditSubscriberRecord",
			{
				{ "1. Edit name" },
				{ "2. Edit address" },
				{ "3. Edit phones" },
				{ "4. Edit emails" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteSubscriberRecord",
			{
				{ "<id>. Delete subscriber" },
				{ "C. Cancel" }
			}
		},
		{
			"EditAddress",
			{
				{ "1. Edit city" },
				{ "2. Edit street" },
				{ "3. Edit house" },
				{ "4. Edit apartment" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditPhones",
			{
				{ "1. Update phones" },
				{ "2. Delete phones" },
				{ "3. Add phone" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"UpdatePhones",
			{
				{ "<phone id>. Update phone" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditEmails",
			{
				{ "1. Update emails" },
				{ "2. Delete emails" },
				{ "3. Add email" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"UpdateEmails",
			{
				{ "<email id>. Update email" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditName",
			{
				{ "Please enter new name:" }
			}
		},
		{
			"EditCity",
			{
				{ "Please enter new city name:" }
			}
		},
		{
			"EditStreet",
			{
				{ "Please enter new street name:" }
			}
		},
		{
			"EditHouse",
			{
				{ "Please enter new house name:" }
			}
		},
		{
			"EditApartment",
			{
				{ "Please enter new apartment number:" }
			}
		},
		
		{
			"EditPhone",
			{
				{ "Please enter new phone number:" }
			}
		},
		{
			"EditEmail",
			{
				{ "Please enter new email:" }
			}
		},
		{
			"AddPhone",
			{
				{ "Please enter new phone number:" }
			}
		},
		{
			"AddEmail",
			{
				{ "Please enter new email:" }
			}
		},
		{
			"DeletePhones",
			{
				{ "<phone id>. Delete phone" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteEmails",
			{
				{ "<email id>. Delete email" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		}
	};


	void PrintSubscriberIds(ostream &ost, vector<size_t> const &subscriberIndexes, CAddressBook const &addressBook)
	{
		ost << "Subscribers:" << endl;
		for (size_t i = 0; i < subscriberIndexes.size(); ++i)
		{
			ost << i + 1 << ". " << string(addressBook[subscriberIndexes.at(i)].GetName()) << endl;
		}
	}

	void PrintVectorDataId(ostream &ost, string const &prompt, vector<string> const &data)
	{
		if (data.size() > 0)
		{
			ost << prompt << endl;
			for (size_t i = 0; i < data.size(); ++i)
			{
				ost << i + 1 << ". " << data.at(i) << endl;
			}
		}
	}

	
	void PrintEmailIds(ostream &ost, vector<string> const &emails)
	{
		PrintVectorDataId(ost, "Emails:", emails);
	}
	

	void PrintPhoneIds(ostream &ost, vector<string> const &phones)
	{
		PrintVectorDataId(ost, "Phones:", phones);
	}
	

	void PrintAddress(ostream &ost, CPostAddress const &address)
	{
		ost << "Address: "
			<< "\"" << address.GetCity() << "\","
			<< "\"" << address.GetStreet() << "\","
			<< "\"" << address.GetHouse() << "\","
			<< "\"" << ((address.GetApartment() == 0) ? "" : to_string(address.GetApartment())) << "\""
			<< endl;
	}


	void PrintAddress(ostream &ost, string city, string street, string house, unsigned apartment)
	{
		PrintAddress(ost, CPostAddress(city, street, house, apartment));
	}


	void PrintVector(ostream &ost, string const &prompt, vector<string> const &data)
	{
		ost << prompt;
		for (auto it = data.begin(); it != data.end();)
		{
			ost << *it;
			if (++it != data.end())
			{
				ost << ", ";
			}
		}
		ost << endl;
	}

	
	void PrintPhonesLine(ostream &ost, vector<string> const &phones)
	{
		PrintVector(ost, "Phones: ", phones);
	}


	void PrintEmailsLine(ostream &ost, vector<string> const &emails)
	{
		PrintVector(ost, "Emails: ", emails);
	}


	void PrintName(ostream &ost, string const &name)
	{
		ost << "Name: " << name << endl;
	}


	void PrintSubscriberInfo(ostream &ost,
		string const &name,
		CPostAddress const &address,
		std::vector<std::string> const phones,
		std::vector<std::string> const emails)
	{
		PrintName(ost, name);
		PrintAddress(ost, address);
		PrintPhonesLine(ost, phones);
		PrintEmailsLine(ost, emails);
	}

	void PrintSubscriberInfo(ostream &ost, CSubscriber const &subscriber)
	{
		PrintSubscriberInfo(ost,
			subscriber.GetName(),
			subscriber.GetAddress(),
			subscriber.GetPhones(),
			subscriber.GetEmails());
	}

	void ClearScreen()
	{
		system("cls");
	}

	
	string ReadLine(istream &ist)
	{
		string line;
		while (line == "")
		{
			getline(ist, line);
		}
		return line;
	}
	
	template <typename T>
	boost::optional<T> ReadFromLine(string const &line)
	{
		T result;
		istringstream lineStream(line);
		if (lineStream >> result)
		{
			return result;
		}
		return boost::none;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CMenuCLI::CMenuCLI(istream &ist, ostream &ost) :
m_ist(ist),
m_ost(ost)
{
}


void CMenuCLI::PrintMenuPrompt(string const &menuName) const
{
	for (auto &line : menuPrompt.at(menuName))
	{
		m_ost << line << endl;
	}
}


string CMenuCLI::ReadUserCommand() const
{
	string command;
	m_ist >> command;
	boost::to_lower(command);
	return command;
}


// menu relations functions

void CMenuCLI::Start(CAddressBook &addressBook)
{
	MainMenu(addressBook);
}


void CMenuCLI::MainMenu(CAddressBook &addressBook) const
{
	string menuName = "MainMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowSubscribers(addressBook);
		}
		else if (command == "2")
		{
			EditSubscribers(addressBook);
		}
		else if (command == "3")
		{
			DeleteSubscriber(addressBook);
		}
		else if (command == "4")
		{
			AddSubscriber(addressBook);
		}
		else if (command == "q")
		{
			return;
		}
		m_ost << endl;
	}
}


void CMenuCLI::ShowSubscribers(CAddressBook const &addressBook) const
{
	if (auto subscriberIndexes = FindSubscribers(addressBook))
	{
		ShowSubscriberRecords(addressBook, *subscriberIndexes);
	}
}


void CMenuCLI::ShowSubscriberRecords(CAddressBook const &addressBook, std::vector<size_t> const &subscriberIndexes) const
{
	string menuName = "ShowSubscriberRecords";

	for (;;)
	{
		ClearScreen();
		PrintSubscriberIds(m_ost, subscriberIndexes, addressBook);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto chooserRecord = ReadFromLine<unsigned>(command))
		{
			if (*chooserRecord - 1 < subscriberIndexes.size())
			{
				ShowSubscriberRecord(addressBook[subscriberIndexes.at(*chooserRecord - 1)]);
			}
		}

		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::ShowSubscriberRecord(CSubscriber const &subscriber) const
{
	string menuName = "ShowSubscriberRecord";

	for (;;)
	{
		ClearScreen();
		PrintSubscriberInfo(m_ost, subscriber);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::EditSubscribers(CAddressBook &addressBook) const
{
	if (auto subscriberIndexes = FindSubscribers(addressBook))
	{
		EditSubscriberRecords(addressBook, *subscriberIndexes);
	}
}


void CMenuCLI::EditSubscriberRecords(CAddressBook &addressBook, std::vector<size_t> const &subscriberIndexes) const
{
	string menuName = "EditSubscriberRecords";

	for (;;)
	{
		ClearScreen();
		PrintSubscriberIds(m_ost, subscriberIndexes, addressBook);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto chooserRecord = ReadFromLine<unsigned>(command))
		{
			if (*chooserRecord - 1 < subscriberIndexes.size())
			{
				EditSubscriberRecord(addressBook[subscriberIndexes.at(*chooserRecord - 1)]);
			}
		}

		if (command == "c")
		{
			return;
		}
	}
}


bool CMenuCLI::EditSubscriberRecord(CSubscriber &subscriber) const
{
	string menuName = "EditSubscriberRecord";

	string name = subscriber.GetName();
	CPostAddress address = subscriber.GetAddress();
	vector<string> phones = subscriber.GetPhones();
	vector<string> emails = subscriber.GetEmails();
	for (;;)
	{
		ClearScreen();
		if (name == "")
		{
			m_ost << "The record can't be saved. The name must not be empty." << endl;
		}
		PrintSubscriberInfo(m_ost, name, address, phones, emails);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			UpdateName(name);
		}
		if (command == "2")
		{
			UpdateAddress(address);
		}
		if (command == "3")
		{
			EditPhones(phones);
		}
		if (command == "4")
		{
			EditEmails(emails);
		}
		if ((command == "a")
			&& (name != ""))
		{
			subscriber.SetName(name);
			subscriber.SetAddress(address);
			subscriber.SetPhones(phones);
			subscriber.SetEmails(emails);
			return true;
		}
		if (command == "c")
		{
			return false;
		}
	}
}


void CMenuCLI::DeleteSubscriber(CAddressBook &addressBook) const
{
	if (auto subscriberIndexes = FindSubscribers(addressBook))
	{
		DeleteSubscriberRecord(addressBook, *subscriberIndexes);
	}
}


void CMenuCLI::DeleteSubscriberRecord(CAddressBook &addressBook, std::vector<size_t> const &subscriberIndexes) const
{
	string menuName = "DeleteSubscriberRecord";

	for (;;)
	{
		ClearScreen();
		PrintSubscriberIds(m_ost, subscriberIndexes, addressBook);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<unsigned>(command))
		{
			if (*choosenRecord - 1 < subscriberIndexes.size())
			{
				addressBook.DeleteSubscriber(subscriberIndexes.at(*choosenRecord - 1));
				return;
			}
		}

		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::AddSubscriber(CAddressBook &addressBook) const
{
	CSubscriber newRecord("new record");
	if (EditSubscriberRecord(newRecord))
	{
		addressBook.AddSubscriber(newRecord);
	}
}


// choose from list functions

boost::optional<vector<size_t>> CMenuCLI::FindSubscribers(CAddressBook const &addressBook) const
{
	string menuName = "FindSubscribers";

	string name;
	CPostAddress address;
	vector<string> phones;
	vector<string> emails;
	for (;;)
	{
		ClearScreen();
		m_ost << "Enter properties of subscribers you want to find" << endl;

		PrintSubscriberInfo(m_ost, name, address, phones, emails);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			UpdateName(name);
		}
		if (command == "2")
		{
			UpdateAddress(address);
		}
		if (command == "3")
		{
			EditPhones(phones);
		}
		if (command == "4")
		{
			EditEmails(emails);
		}
		if (command == "a")
		{
			return addressBook.FindSubscribers(name, address, phones, emails);
		}
		if (command == "c")
		{
			return boost::none;
		}
	}
}


// Edit choice functions

void CMenuCLI::UpdateAddress(CPostAddress &address) const
{
	string menuName = "EditAddress";

	string city = address.GetCity();
	string street = address.GetStreet();
	string house = address.GetHouse();
	unsigned apartment = address.GetApartment();
	for (;;)
	{
		ClearScreen();
		PrintAddress(m_ost, city, street, house, apartment);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			UpdateCity(city);
		}
		if (command == "2")
		{
			UpdateStreet(street);
		}
		if (command == "3")
		{
			UpdateHouse(house);
		}
		if (command == "4")
		{
			UpdateApartment(apartment);
		}
		if (command == "a")
		{
			address.SetCity(city);
			address.SetStreet(street);
			address.SetHouse(house);
			address.SetApartment(apartment);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::EditPhones(vector<string> &phones) const
{
	string menuName = "EditPhones";
	vector<string> copyPhones(phones);
	for (;;)
	{
		ClearScreen();
		PrintPhonesLine(m_ost, copyPhones);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			if (copyPhones.size() > 0)
			{
				UpdatePhones(copyPhones);
			}
		}
		if (command == "2")
		{
			if (copyPhones.size() > 0)
			{
				DeletePhones(copyPhones);
			}
		}
		if (command == "3")
		{
			AddPhone(copyPhones);
		}

		if (command == "a")
		{
			phones = copyPhones;
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::UpdatePhones(vector<string> &phones) const
{
	string menuName = "UpdatePhones";

	auto copyPhones = phones;
	for (;;)
	{
		ClearScreen();
		PrintPhoneIds(m_ost, copyPhones);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenPhone = ReadFromLine<unsigned>(command))
		{
			if (*choosenPhone - 1 < copyPhones.size())
			{
				UpdatePhone(copyPhones.at(*choosenPhone - 1));
			}
		}

		if (command == "a")
		{
			phones = move(copyPhones);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::EditEmails(vector<string> &emails) const
{
	string menuName = "EditEmails";
	vector<string> copyEmails(emails);
	for (;;)
	{
		ClearScreen();
		PrintEmailsLine(m_ost, copyEmails);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			if (copyEmails.size() > 0)
			{
				UpdateEmails(copyEmails);
			}
		}
		if (command == "2")
		{
			if (copyEmails.size() > 0)
			{
				DeleteEmails(copyEmails);
			}
		}
		if (command == "3")
		{
			AddEmail(copyEmails);
		}
		if (command == "a")
		{
			emails = copyEmails;
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::UpdateEmails(vector<string> &emails) const
{
	string menuName = "UpdateEmails";

	auto copyEmails = emails;
	for (;;)
	{
		ClearScreen();
		PrintEmailIds(m_ost, copyEmails);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenEmail = ReadFromLine<unsigned>(command))
		{
			if (*choosenEmail - 1 < copyEmails.size())
			{
				UpdateEmail(copyEmails.at(*choosenEmail - 1));
			}
		}

		if (command == "a")
		{
			emails = move(copyEmails);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


// Update functions

void CMenuCLI::UpdateName(string &name) const
{
	string menuName = "EditName";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		
		name = ReadLine(m_ist);
		trim(name);
		return;
	}
}


void CMenuCLI::UpdateCity(std::string &city) const
{
	string menuName = "EditCity";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		city = ReadLine(m_ist);
		return;
	}
}


void CMenuCLI::UpdateStreet(std::string &street) const
{
	string menuName = "EditStreet";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		street = ReadLine(m_ist);
		return;
	}
}


void CMenuCLI::UpdateHouse(std::string &house) const
{
	string menuName = "EditHouse";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		house = ReadLine(m_ist);
		return;
	}
}


void CMenuCLI::UpdateApartment(unsigned &apartment) const
{
	string menuName = "EditApartment";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		if (auto newApartmentNumber = ReadFromLine<unsigned>(ReadLine(m_ist)))
		{
			apartment = *newApartmentNumber;
			return;
		}
	}
}


void CMenuCLI::UpdatePhone(string &phone) const
{
	string menuName = "EditPhone";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		phone = ReadLine(m_ist);
		trim(phone);
		return;
	}
}


void CMenuCLI::UpdateEmail(string &email) const
{
	string menuName = "EditEmail";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);

		email = ReadLine(m_ist);
		trim(email);
		return;
	}
}


// Add functions

void CMenuCLI::AddPhone(vector<string> &phones) const
{
	string newPhone;
	UpdatePhone(newPhone);
	if (newPhone != "")
	{
		phones.push_back(newPhone);
	}
}


void CMenuCLI::AddEmail(vector<string> &emails) const
{
	string newEmail;
	UpdateEmail(newEmail);
	if (newEmail != "")
	{
		emails.push_back(newEmail);
	}
}


// Delete functions


void CMenuCLI::DeletePhones(vector<string> &phones) const
{	
	string menuName = "DeletePhones";

	auto copyPhones = phones;
	for (;;)
	{
		ClearScreen();
		PrintPhoneIds(m_ost, copyPhones);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenPhone = ReadFromLine<unsigned>(command))
		{
			if (*choosenPhone - 1 < copyPhones.size())
			{
				copyPhones.erase(copyPhones.begin() + *choosenPhone - 1);
			}
		}

		if (command == "a")
		{
			phones = move(copyPhones);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}

void CMenuCLI::DeleteEmails(vector<string> &emails) const
{
	string menuName = "DeleteEmails";

	auto copyEmails = emails;
	for (;;)
	{
		ClearScreen();
		PrintEmailIds(m_ost, copyEmails);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenEmail = ReadFromLine<unsigned>(command))
		{
			if (*choosenEmail - 1 < copyEmails.size())
			{
				copyEmails.erase(copyEmails.begin() + *choosenEmail - 1);
			}
		}

		if (command == "a")
		{
			emails = move(copyEmails);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}