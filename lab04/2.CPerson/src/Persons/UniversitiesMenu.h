#pragma once
#include <iostream>
#include <list>
#include "CliMenu.h"
#include "University.h"
#include "Student.h"
class CUniversitiesMenu : 
	public CCliMenu,
	boost::noncopyable
{
public:
	CUniversitiesMenu(std::ostream &ost, std::istream &ist, std::list<CUniversity> &universities, std::list<CStudent> &students);
	bool Start();
private:
	void ShowUniversities();
	void AddUniversity();
	void EditUniversities();
	bool EditUniversity(CUniversity &university);
	void DeleteUniversity();

	bool SetUniversityName(CUniversity &university) const;
private:
	std::ostream &m_ost;
	std::istream &m_ist;
	std::list<CUniversity> &m_universities;
	std::list<CStudent> &m_students;
};

