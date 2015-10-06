#include "stdafx.h"
#include "CompaniesMenu.h"
#include "CliFunctions.h"
#include "CliMenus.h"

using namespace std;


namespace
{
	void PrintCompanyProperties(ostream &ost, string const &name, string const &website)
	{
		ost << "Name: " << name << endl
			<< "Website: " << website << endl;
	}
	
	void PrintCompanyInfo(ostream &ost, CCompany const &company)
	{
		PrintCompanyProperties(ost, company.GetName(), company.GetWebsite());
	}

	void DeleteWorkersByCompanyPtr(CCompany const *pCompany, list<CWorker> &workers)
	{
		remove_nonmovable_if(workers, [pCompany](CWorker &worker){
			return worker.GetCompany() == pCompany;
		});
	}
}


CCompaniesMenu::CCompaniesMenu(ostream &ost, istream &ist, list<CCompany> &companies, list<CWorker> &workers) :
m_ost(ost),
m_ist(ist),
m_companies(companies),
m_workers(workers)
{
}


bool CCompaniesMenu::Start()
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "CompaniesMenu", {
		{ "1", bind(&CCompaniesMenu::ShowCompanies, &*this) },
		{ "2", bind(&CCompaniesMenu::AddCompany, &*this) },
		{ "3", bind(&CCompaniesMenu::EditCompanies, &*this) },
		{ "4", bind(&CCompaniesMenu::DeleteCompany, &*this) }
	});

	return HaveChangesBeenHappened();
}


// Menu relations functions

void CCompaniesMenu::ShowCompanies() const
{
	ListChoiseAndReturnWithProcessFunctionMenu<CCompany>(m_ost, m_ist, "ShowCompaniesMenu",	m_companies,
 		bind(&CCompaniesMenu::ShowCompany, &*this, placeholders::_1));
}


void CCompaniesMenu::ShowCompany(CCompany const &company) const
{
	ListChoiseAndReturnWithoutProcessFunctionMenu(m_ost, m_ist,
		bind(PrintCompanyInfo, ref(m_ost), company));
}


void CCompaniesMenu::AddCompany()
{
	CCompany newCompany("nothing");
	if (!SetCompanyName(newCompany))
	{
		return;
	}
	newCompany.SetWebsite(ReadString(m_ost, m_ist, "Enter new company's website"));

	if (EditCompany(newCompany))
	{
		m_companies.push_back(newCompany);
	}
}


void CCompaniesMenu::EditCompanies()
{
	ListChoiseAndReturnWithProcessFunctionMenu(m_ost, m_ist, "EditCompaniesMenu", m_companies,
		bind(&CCompaniesMenu::EditCompany, &*this, placeholders::_1));
}


bool CCompaniesMenu::EditCompany(CCompany &company)
{
	string menuName = "EditCompanyMenu";

	auto companyCopy = company;
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName, bind(PrintCompanyInfo, ref(m_ost), companyCopy));

		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetCompanyName(companyCopy);
		}
		else if (command == "2")
		{
			SetCompanyWebsite(companyCopy);
		}
		else if (command == "a")
		{
			company = companyCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


void CCompaniesMenu::DeleteCompany()
{
	if (m_companies.size() > 0)
	{
		if (auto pDeletedCompany = DeleteListElementMenu(m_ost, m_ist, m_companies, "DeleteCompanyMenu"))
		{
			DeleteWorkersByCompanyPtr(*pDeletedCompany, m_workers);
			MarkChangesOccurrence();
		}
	}
}


// Work with data functions

bool CCompaniesMenu::SetCompanyName(CCompany &company) const
{
	string name;
	if (ReadNameWithOccupiedCheck(m_ost, m_ist, name, m_companies,
		"Enter the company's name",
		"There already is a company with such name.\nDo you want to enter something else? (Y/N)"))
	{
		company.SetName(name);
		return true;
	}
	return false;
}


void CCompaniesMenu::SetCompanyWebsite(CCompany &company) const
{
	SkipLine(m_ist);
	company.SetWebsite(ReadString(m_ost, m_ist, "Enter company's website"));
}

