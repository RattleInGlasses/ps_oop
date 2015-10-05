#include "stdafx.h"
#include "Cli.h"
#include "UniversitiesMenu.h"
#include "StudentsMenu.h"
#include "CompaniesMenu.h"
#include "CliFunctions.h"

using namespace std;

namespace
{
	void UpdateDataChangeOccurrence(bool &dataChangedVariable, bool newDataChangedState)
	{
		if (!dataChangedVariable)
		{
			dataChangedVariable = newDataChangedState;
		}
	}
}


CCli::CCli(ostream &ost, istream &ist, std::list<CStudent> &students,
	std::list<CUniversity> &universities, std::list<CWorker> &workers, std::list<CCompany> &companies) :
m_ost(ost),
m_ist(ist),
m_universitiesMenu(ost, ist, universities, students),
m_studentsMenu(ost, ist, students, universities),
m_companiesMenu(ost, ist, companies, workers),
m_workersMenu(ost, ist, workers, companies)
{
}


bool CCli::Start()
{
	return MainMenu();
}

bool CCli::MainMenu()
{
	string menuName = "MainMenu";

	bool dataChanged = false;
	
	for (;;)
	{
		PrintMenuPrompt(m_ost, menuName);
		string command = ReadUserCommand(m_ist);
		if (command == "1")
		{
			UpdateDataChangeOccurrence(dataChanged, m_universitiesMenu.Start());
		}
		else if (command == "2")
		{
			UpdateDataChangeOccurrence(dataChanged, m_studentsMenu.Start());
		}
		else if (command == "3")
		{
			UpdateDataChangeOccurrence(dataChanged, m_companiesMenu.Start());
		}
		else if (command == "4")
		{
			UpdateDataChangeOccurrence(dataChanged, m_workersMenu.Start());
		}
		else if (command == "q")
		{
			return dataChanged;
		}
		ClearScreen();
	}
}

