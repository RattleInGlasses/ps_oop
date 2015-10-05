#pragma once
#include <iostream>
#include <list>
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"
#include "UniversitiesMenu.h"
#include "StudentsMenu.h"
#include "CompaniesMenu.h"
#include "WorkersMenu.h"
class CCli
{
public:
	CCli(std::ostream &ost, std::istream &ist, std::list<CStudent> &students, 
		std::list<CUniversity> &universities, std::list<CWorker> &workers, std::list<CCompany> &companies);
	bool Start();
private:
	bool MainMenu();
private:
	std::ostream &m_ost;
	std::istream &m_ist;

	CUniversitiesMenu m_universitiesMenu;
	CStudentsMenu m_studentsMenu;
	CCompaniesMenu m_companiesMenu;
	CWorkersMenu m_workersMenu;
};

