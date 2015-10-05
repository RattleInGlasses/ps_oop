#include "stdafx.h"
#include "UniversitiesMenu.h"
#include "CliFunctions.h"
#include "CliMenus.h"
#include <boost\bind\placeholders.hpp>

using namespace std;
using namespace std::placeholders;


namespace
{
	void PrintUniversityProperty(ostream &ost, string const &name)
	{
		ost << "Name: " << name << endl;
	}

	void PrintUniversityInfo(ostream &ost, CUniversity const &university)
	{
		PrintUniversityProperty(ost, university.GetName());
	}

	void DeleteStudentsByUniversityPtr(CUniversity const *pUniversity, std::list<CStudent> &students)
	{
		remove_nonmovable_if(students, [pUniversity](CStudent &student){
			return student.GetUniversity() == pUniversity;
		});
	}
}


CUniversitiesMenu::CUniversitiesMenu(std::ostream &ost, std::istream &ist, std::list<CUniversity> &universities, std::list<CStudent> &students) :
m_ost(ost),
m_ist(ist),
m_universities(universities),
m_students(students)
{
}


bool CUniversitiesMenu::Start()
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "UniversitiesMenu", {
		{ "1", bind(&CUniversitiesMenu::ShowUniversities, &*this) },
		{ "2", bind(&CUniversitiesMenu::AddUniversity, &*this) },
		{ "3", bind(&CUniversitiesMenu::EditUniversities, &*this) },
		{ "4", bind(&CUniversitiesMenu::DeleteUniversity, &*this) }
	});

	return HaveChangesBeenHappened();
}


// Menu functions

void CUniversitiesMenu::ShowUniversities()
{
	ListChoiseAndReturnWithoutProcessFunctionMenu(m_ost, m_ist, 
		bind(PrintList<CUniversity>, ref(m_ost), m_universities));
}


void CUniversitiesMenu::AddUniversity()
{
	CUniversity university("nothing");
	if (!SetUniversityName(university))
	{
		return;
	}
	
	if (EditUniversity(university))
	{
		m_universities.push_back(university);
		MarkChangesOccurrence();
	}
}

void CUniversitiesMenu::EditUniversities()
{
	ListChoiseAndReturnWithProcessFunctionMenu<CUniversity>(m_ost, m_ist, "EditUniversitiesMenu", m_universities,
		bind(&CUniversitiesMenu::EditUniversity, &*this, std::placeholders::_1));
}


bool CUniversitiesMenu::EditUniversity(CUniversity &university)
{
	string menuName = "EditUniversityMenu";

	auto universityCopy(university);
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName, bind(PrintUniversityInfo, ref(m_ost), universityCopy));
		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetUniversityName(universityCopy);
		}
		else if (command == "a")
		{
			university = universityCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


void CUniversitiesMenu::DeleteUniversity()
{
	if (m_universities.size() > 0)
	{
		if (auto pDeletedUniversity = DeleteListElementMenu<CUniversity>(m_ost, m_ist, m_universities, "DeleteUniversityMenu"))
		{
			DeleteStudentsByUniversityPtr(*pDeletedUniversity, m_students);
			MarkChangesOccurrence();
		}

	}
}


// Work with data functions

bool CUniversitiesMenu::SetUniversityName(CUniversity &university) const
{
	string name;
	if (ReadNameWithOccupiedCheck(m_ost, m_ist, name, m_universities,
		"Enter the university's name",
		"There already is a university with such name.\nDo you want to enter something else? (Y/N)"))
	{
		university.SetName(name);
		return true;
	}
	return false;
}

