#pragma once
#include <iostream>
#include <list>
#include "CliMenu.h"
#include "Student.h"
#include "University.h"
class CStudentsMenu :
	public CCliMenu,
	boost::noncopyable
{
public:
	CStudentsMenu(std::ostream &ost, std::istream &ist, std::list<CStudent> &students, std::list<CUniversity> &universities);
	bool Start();
private:
	void ShowStudents() const;
	void ShowAllStudents() const;
	void ShowStudentsByUniverisity() const;
	template <typename T>
	void ShowStudentList(std::list<T> const &students, std::string const &menuName) const;
	void ShowStudent(CStudent const &student) const;
	void AddStudent();
	bool EditStudentProperties(Gender &gender, std::string &name, unsigned &age, unsigned &height,
		unsigned &weight, int &studyYear, CUniversity const *&pUniversity);
	void EditStudents();
	void EditStudent(CStudent &student);
	void DeleteStudent();

	void SetStudentName(std::string &name) const;
	void SetStudentGender(Gender &gender) const;
	void SetStudentAge(unsigned &age, unsigned min = 1u) const;
	void SetStudentHeight(unsigned &height, unsigned min = 1u) const;
	void SetStudentWeight(unsigned &weight) const;
	void SetStudentStudyYear(int &studyYear, int min = 1) const;
	void SetStudentUniversity(CUniversity const *&pUniversity) const;
private:
	std::ostream &m_ost;
	std::istream &m_ist;
	std::list<CStudent> &m_students;
	std::list<CUniversity> const &m_universities;
};


template <typename T>
void CStudentsMenu::ShowStudentList(std::list<T> const &students, std::string const &menuName) const
{
	ListChoiseAndReturnWithProcessFunctionMenu(m_ost, m_ist, menuName, students,
		bind(&CStudentsMenu::ShowStudent, &*this, std::placeholders::_1));
}
