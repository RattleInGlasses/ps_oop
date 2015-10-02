#pragma once
#include <iostream>
#include <list>
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"
class CCLIMenu
{
public:
	CCLIMenu(std::ostream &ost, std::istream &ist);
public:
	bool Start(std::list<CStudent> &students,
		std::list<CUniversity> &universities,
		std::list<CWorker> &workers,
		std::list<CCompany> &companies);
private:
	CCLIMenu &operator =(CCLIMenu &);
private:
	void PrintMenuPrompt(std::string const &menuName) const;
	std::string ReadUserCommand() const;
	
	void MainMenu(std::list<CStudent> &students,
		std::list<CUniversity> &universities,
		std::list<CWorker> &workers,
		std::list<CCompany> &companies);
	void UniversitiesMenu(std::list<CUniversity> &universities, std::list<CStudent> &students);
	void StudentsMenu(std::list<CStudent> &students, std::list<CUniversity> const &universities);
	void CompaniesMenu(std::list<CCompany> &companies, std::list<CWorker> &workers);
	void WorkersMenu(std::list<CWorker> &workers, std::list<CCompany> const &companies);

	void AddUniversity(std::list<CUniversity> &universities);
	void EditUniversities(std::list<CUniversity> &universities);
	void EditUniversity(CUniversity &university, std::list<CUniversity> const &universities);
	void DeleteUniversity(std::list<CUniversity> &universities, std::list<CStudent> &students);

	void ShowStudents(std::list<CStudent> const &students, std::list<CUniversity> const &universities) const;
	void ShowAllStudents(std::list<CStudent> const &students) const;
	void ShowStudentsByUniversity(std::list<CStudent> const &students, CUniversity const &university) const;
	void ShowStudent(CStudent const &student) const;
	void AddStudent(std::list<CStudent> &students, std::list<CUniversity> const &universities);
	bool EditStudentProperties(Gender &gender, std::string &name, unsigned &age,
		unsigned &height, unsigned &weight, int &studyYear, CUniversity const *&pUniversity,
		std::list<CUniversity> const &universities);
	void EditStudents(std::list<CStudent> &students, std::list<CUniversity> const &university);
	void EditStudent(CStudent &student, std::list<CUniversity> const &universities);
	void DeleteStudent(std::list<CStudent> &students);

	void ShowCompanies(std::list<CCompany> const &companies) const;
	void ShowCompany(CCompany const &company) const;
	void AddCompany(std::list<CCompany> &companies);
	void EditCompanies(std::list<CCompany> &companies);
	bool EditCompany(CCompany &company, std::list<CCompany> const &companies);
	void DeleteCompany(std::list<CCompany> &companies, std::list<CWorker> &workers);

 	void ShowWorkers(std::list<CWorker> const &workers, std::list<CCompany> const &companies) const;
 	void ShowAllWorkers(std::list<CWorker> const &workers) const;
 	void ShowWorkersByCompany(std::list<CWorker> const &workers, CCompany const &company) const;
 	void ShowWorker(CWorker const &worker) const;
 	void AddWorker(std::list<CWorker> &workers, std::list<CCompany> const &companies);
 	bool EditWorkerProperties(Gender &gender, std::string &name, unsigned &age,
 		unsigned &height, unsigned &weight, std::string &post, CCompany const *&pCompany,
 		std::list<CCompany> const &companies);
 	void EditWorkers(std::list<CWorker> &workers, std::list<CCompany> const &companies);
	void EditWorker(CWorker &worker, std::list<CCompany> const &companies);
 	void DeleteWorker(std::list<CWorker> &workers);


	std::string GetNewUniversityName() const;
	bool SetUniversityName(CUniversity &university, std::list<CUniversity> const &universities) const;

	void SetStudentName(std::string &name) const;
	void SetStudentGender(Gender &gender) const;
	void SetStudentAge(unsigned &age, unsigned min = 1u) const;
	void SetStudentHeight(unsigned &height, unsigned min = 1u) const;
	void SetStudentWeight(unsigned &weight) const;
	void SetStudentStudyYear(int &studyYear, int min = 1) const;
	void SetStudentUniversity(CUniversity const *&university, std::list<CUniversity> const &universities) const;

	bool SetCompanyName(CCompany &company, std::list<CCompany> const &companies) const;
	void SetCompanyWebsite(CCompany &company) const;

 	void SetWorkerName(std::string &name) const;
 	void SetWorkerGender(Gender &gender) const;
 	void SetWorkerAge(unsigned &age, unsigned min = 1u) const;
 	void SetWorkerHeight(unsigned &height, unsigned min = 1u) const;
	void SetWorkerWeight(unsigned &weight) const;
 	void SetWorkerPost(std::string &post) const;
 	void SetWorkerCompany(CCompany const *&pCompany, std::list<CCompany> const &companies) const;
	
	void MarkChangesOccurrence();

	template <typename T>
	void SetValueWithRestrictions(T &value, T minValue, T maxValue,
		std::string const &mainPrompt, std::string const &errorPrompt) const;
	template <typename Organization>
	boost::optional<Organization const*> ChooseOrganizationPtr(std::list<Organization> const &organizations) const;
	template <typename Organization>
	Organization const *ChooseOrganizationPtrWithPrompt(std::list<Organization> const &organizations, std::string const &prompt) const;
	template <typename T>
	boost::optional<T*> DeleteDataListElement(std::list<T> &dataList, std::string const &menuName);
	template <typename T>
	void ShowDataList(std::list<T> const &dataList) const;	
private:
	std::ostream &m_ost;
	std::istream &m_ist;
	bool m_dataChanged = false;
};


template <typename T>
void CCLIMenu::SetValueWithRestrictions(T &value, T minValue, T maxValue,
	std::string const &mainPrompt, std::string const &errorPrompt) const
{
	if (auto result = ReadFromStreamWithRestrictions<unsigned>(m_ost, m_ist,
		minValue, maxValue, mainPrompt, errorPrompt))
	{
		value = *result;
	}
}

template<typename Organization>
boost::optional<Organization const*> CCLIMenu::ChooseOrganizationPtr(std::list<Organization> const &organizations) const
{
	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, organizations);
		m_ost << endl;
		PrintMenuPrompt("ChooseOrganizationMenu");
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= organizations.size())
			{
				return &GetListElement(organizations, *choosenRecord - 1);
			}
		}
		if (command == "c")
		{
			return boost::none;
		}
	}
}

template<typename Organization>
Organization const *CCLIMenu::ChooseOrganizationPtrWithPrompt(std::list<Organization> const &organizations, std::string const &prompt) const
{
	for (;;)
	{
		ClearScreen();
		m_ost << prompt << endl;
		PrintList(m_ost, organizations);
		m_ost << endl;
		PrintMenuPrompt("ChooseOrganizationWithPromptMenu");
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= organizations.size())
			{
				return &GetListElement(organizations, *choosenRecord - 1);
			}
		}
	}
}

template <typename T>
boost::optional<T*> CCLIMenu::DeleteDataListElement(std::list<T> &dataList, std::string const &menuName)
{
	for (;;)
	{
		ClearScreen();
		PrintList<T>(m_ost, dataList);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		std::string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= dataList.size())
			{
				T* pElement = &GetListElement(dataList, *choosenRecord - 1);
				DeleteListElement(dataList, *choosenRecord - 1);
				MarkChangesOccurrence();
				return pElement;
			}
		}
		else if (command == "c")
		{
			return boost::none;
		}
	}
}

template<typename T>
void CCLIMenu::ShowDataList(std::list<T> const &dataList) const
{
	for (;;)
	{
		ClearScreen();
		PrintList<T>(m_ost, dataList);
		m_ost << endl;
		PrintMenuPrompt("ShowDataList");
		string command = ReadUserCommand();

		if (command == "r")
		{
			return;
		}
	}
}

