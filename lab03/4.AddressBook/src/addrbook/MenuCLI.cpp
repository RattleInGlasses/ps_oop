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
				{ "1. Find subscriber records" },
				{ "2. Add new subscriber record" },
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
			"ChooseSubscriber",
			{
				{ "<subscriber id>. Make choice" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"ChooseSubscriberAction",
			{
				{ "1. Edit subscriber" },
				{ "2. Delete subscriber" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditSubscriber",
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
				{ "1. Add phone" },
				{ "2. Choose phone" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"ChoosePhone",
			{
				{ "<phone id>. Make choice" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"ChoosePhoneAction",
			{
				{ "1. Edit phone" },
				{ "2. Delete phone" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditEmails",
			{
				{ "1. Add email" },
				{ "2. Choose email" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"ChooseEmail",
			{
				{ "<email id>. Make choice" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"ChooseEmailAction",
			{
				{ "1. Edit email" },
				{ "2. Delete email" },
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
	};


	void PrintPhone(ostream &ost, string const &phone)
	{
		ost << "Phone: " << phone << endl;
	}


	void PrintEmail(ostream &ost, string const &email)
	{
		ost << "Email: " << email << endl;
	}
	

	void PrintSubscribersId(ostream &ost, CAddressBook::CSubscriberReferenceList const &subscribers)
	{
		ost << "Subscribers:" << endl;
		for (size_t i = 0; i < subscribers.size(); ++i)
		{
			ost << i + 1 << ". " << subscribers[i].GetName().GetValue() << endl;
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


	void PrintPhonesId(ostream &ost, vector<string> const &phones)
	{
		PrintVectorDataId(ost, "Phones:", phones);
	}


	void PrintAddress(ostream &ost, CPostAddress const &address)
	{
		ost << "Address: ";
		if (address.GetCity() != "")
		{
			ost << address.GetCity() << " ";
		}
		if (address.GetStreet() != "")
		{
			ost << address.GetStreet() << " ";
		}
		if (address.GetHouse() != "")
		{
			ost << address.GetHouse() << " ";
		}
		if (address.GetApartment() != 0)
		{
			ost << address.GetApartment();
		}
		ost << endl;
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
	T ReadFromLine(string const &line)
	{
		T result;
		istringstream lineStream(line);
		lineStream >> result;
		return result;
	}

	template <typename T>
	T ReadFromStream(istream &ist)
	{
		T result;
		ist >> result;
		return result;
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


void CMenuCLI::PrintSubscriberInfo(string const &name,
	CPostAddress const &address,
	std::vector<std::string> const phones,
	std::vector<std::string> const emails) const
{
	PrintName(m_ost, name);
	PrintAddress(m_ost, address);
	PrintPhonesLine(m_ost, phones);
	PrintEmailsLine(m_ost, emails);
	m_ost << endl;
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
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			FindSubscribers(addressBook);
		}
		else if (command == "2")
		{
			AddSubscriber(addressBook);
		}
		else if (command == "q")
		{
			return;
		}
	}
}


void CMenuCLI::FindSubscribers(CAddressBook &addressBook) const
{
	string menuName = "FindSubscribers";

	string name;
	CPostAddress address;
	vector<string> phones;
	vector<string> emails;
	for (;;)
	{
		m_ost << endl;
		PrintSubscriberInfo(name, address, phones, emails);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditName(name);
		}
		if (command == "2")
		{
			EditAddress(address);
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
			ChooseSubscriber(addressBook, name, address, phones, emails);
		}
		if (command == "c")
		{
			return;
		}
	}
}


// choose from list functions

void CMenuCLI::ChooseSubscriber(CAddressBook &addressBook,
	string const &name,
	CPostAddress const &address, 
	vector<string> const &phones,
	vector<string> const &emails) const
{
	string menuName = "ChooseSubscriber";

	auto foundRecords = addressBook.FindSubscribers(name, address, phones, emails);
	for (;;)
	{
		m_ost << endl;
		PrintSubscribersId(m_ost, foundRecords);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		unsigned choosenRecord = ReadFromLine<unsigned>(command) - 1;
		if (choosenRecord < foundRecords.size())
		{
			string action = ChooseSubscriberAction();
			if (action == "1")
			{
				EditSubscriber(foundRecords[choosenRecord]);
			}
			if (action == "2")
			{
				// addressBook.Delete(foundRecords[choosenRecord]);
			}
		}

		if (command == "a")
		{
			return;
		}
		if (command == "c")
		{
			return;
		}
	}

	/*auto copySubscribers = subscribers;
	for (;;)
	{
		m_ost << endl;
		PrintSubscribersId(m_ost, copySubscribers);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		unsigned choosenSubscriber = ReadFromLine<unsigned>(command) - 1;
		if (choosenSubscriber < copySubscribers.size())
		{
			ChooseSubscriberAction(copySubscribers[choosenSubscriber]);
			if ()
		}
	}*/
}


string CMenuCLI::ChooseSubscriberAction() const
{
	string menuName = "ChooseSubscriberAction";

	m_ost << endl;
	PrintMenuPrompt(menuName);
	
	string result = ReadLine(m_ist);
	trim(result);
	return result;
}


void CMenuCLI::ChoosePhone(std::vector<std::string> &phones) const
{
	string menuName = "ChoosePhone";

	auto copyPhones = phones;
	for (;;)
	{
		m_ost << endl;
		PrintPhonesId(m_ost, copyPhones);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		unsigned choosenPhone = ReadFromLine<unsigned>(command) - 1;
		if (choosenPhone < copyPhones.size())
		{
			ChoosePhoneAction(copyPhones.at(choosenPhone));
			if (copyPhones.at(choosenPhone) == "")
			{
				copyPhones.erase(copyPhones.begin() + choosenPhone);
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


void CMenuCLI::ChoosePhoneAction(std::string &phone) const
{
	string menuName = "ChoosePhoneAction";

	string copyPhone(phone);
	for (;;)
	{
		m_ost << endl;
		PrintPhone(m_ost, copyPhone);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditPhone(copyPhone);
		}
		if (command == "2")
		{
			DeletePhone(copyPhone);
		}
		if (command == "a")
		{
			phone = move(copyPhone);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::ChooseEmail(std::vector<std::string> &emails) const
{
	string menuName = "ChooseEmail";

	auto copyEmails = emails;
	for (;;)
	{
		m_ost << endl;
		PrintEmailIds(m_ost, copyEmails);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		unsigned chooseEmail = ReadFromLine<unsigned>(command) -1;
		if (chooseEmail < copyEmails.size())
		{
			ChooseEmailAction(copyEmails.at(chooseEmail));
			if (copyEmails.at(chooseEmail) == "")
			{
				copyEmails.erase(copyEmails.begin() + chooseEmail);
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


void CMenuCLI::ChooseEmailAction(std::string &email) const
{
	string menuName = "ChooseEmailAction";

	string copyEmail(email);
	for (;;)
	{
		m_ost << endl;
		PrintEmail(m_ost, copyEmail);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditEmail(copyEmail);
		}
		if (command == "2")
		{
			DeleteEmail(copyEmail);
		}
		if (command == "a")
		{
			email = move(copyEmail);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}



// Edit choice functions

void CMenuCLI::EditAddress(CPostAddress &address) const
{
	string menuName = "EditAddress";

	string city = address.GetCity();
	string street = address.GetStreet();
	string house = address.GetHouse();
	unsigned apartment = address.GetApartment();
	for (;;)
	{
		m_ost << endl;
		PrintAddress(m_ost, city, street, house, apartment);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditCity(city);
		}
		if (command == "2")
		{
			EditStreet(street);
		}
		if (command == "3")
		{
			EditHouse(house);
		}
		if (command == "4")
		{
			EditApartment(apartment);
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
		m_ost << endl;
		PrintPhonesLine(m_ost, copyPhones);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			AddPhone(copyPhones);
		}
		if (command == "2")
		{
			ChoosePhone(copyPhones);
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


void CMenuCLI::EditEmails(vector<string> &emails) const
{
	string menuName = "EditEmails";
	vector<string> copyEmails(emails);
	for (;;)
	{
		m_ost << endl;
		PrintEmailsLine(m_ost, copyEmails);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			AddEmail(copyEmails);
		}
		if (command == "2")
		{
			ChooseEmail(copyEmails);
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


// Edit functions

void CMenuCLI::EditSubscriber(CSubscriber &subscriber) const
{
	string menuName = "EditSubscriber";

	string name;
	CPostAddress address;
	vector<string> phones;
	vector<string> emails;
	for (;;)
	{
		m_ost << endl;
		PrintSubscriberInfo(name, address, phones, emails);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditName(name);
		}
		if (command == "2")
		{
			EditAddress(address);
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
			subscriber.SetName(name);
			subscriber.SetAddress(address);
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}

void CMenuCLI::EditName(string &name) const
{
	string menuName = "EditName";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);
		
		name = ReadLine(m_ist);
		m_ost << "The name has been changed to " << name << endl;
		return;
	}
}


void CMenuCLI::EditCity(std::string &city) const
{
	string menuName = "EditCity";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		city = ReadLine(m_ist);
		m_ost << "The city has been changed to " << city << endl;
		return;
	}
}


void CMenuCLI::EditStreet(std::string &street) const
{
	string menuName = "EditStreet";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		street = ReadLine(m_ist);
		m_ost << "The street has been changed to " << street << endl;
		return;
	}
}


void CMenuCLI::EditHouse(std::string &house) const
{
	string menuName = "EditHouse";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		house = ReadLine(m_ist);
		m_ost << "The house has been changed to " << house << endl;
		return;
	}
}


void CMenuCLI::EditApartment(unsigned &apartment) const
{
	string menuName = "EditApartment";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		apartment = ReadFromStream<unsigned>(m_ist);
		m_ost << "The apartment number has been changed to " << apartment << endl;
		return;
	}
}


void CMenuCLI::EditPhone(string &phone) const
{
	string menuName = "EditPhone";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		phone = ReadLine(m_ist);
		trim(phone);
		m_ost << "The phone number has been changed to " << phone << endl;
		return;
	}
}


void CMenuCLI::EditEmail(string &email) const
{
	string menuName = "EditEmail";

	for (;;)
	{
		m_ost << endl;
		PrintMenuPrompt(menuName);

		email = ReadLine(m_ist);
		trim(email);
		m_ost << "The email has been changed to " << email << endl;
		return;
	}
}


// Add functions

void CMenuCLI::AddSubscriber(CAddressBook &addressBook) const
{
	string menuName = "AddSubscriber";

	string name;
	CPostAddress address;
	vector<string> phones;
	vector<string> emails;
	for (;;)
	{
		m_ost << endl;
		PrintSubscriberInfo(name, address, phones, emails);
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			EditName(name);
		}
		if (command == "2")
		{
			EditAddress(address);
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
			return;
		}
		if (command == "c")
		{
			return;
		}
	}
}


void CMenuCLI::AddPhone(vector<string> &phones) const
{
	string newPhone;
	EditPhone(newPhone);
	if (newPhone != "")
	{
		phones.push_back(newPhone);
	}
}


void CMenuCLI::AddEmail(vector<string> &emails) const
{
	string newEmail;
	EditEmail(newEmail);
	if (newEmail != "")
	{
		emails.push_back(newEmail);
	}
}


// Delete functions

void CMenuCLI::DeletePhone(string &phone) const
{
	m_ost << "The phone " << phone << " has been deleted" << endl;
	phone = "";
}

void CMenuCLI::DeleteEmail(string &email) const
{
	m_ost << "The email " << email << " has been deleted" << endl;
	email = "";
}