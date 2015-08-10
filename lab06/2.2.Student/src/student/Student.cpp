#include "stdafx.h"
#include "Student.h"
#include <string>
#include <boost/algorithm/string/trim.hpp>

using namespace std;


CStudent::CStudent(std::string const &name, std::string const &surname, std::string const &patronymic, int age)
{
	Rename(name, surname, patronymic);
	SetAge(age);
}


std::string CStudent::GetName() const
{
	return m_name;
}


std::string CStudent::GetSurname() const
{
	return m_surname;
}


std::string CStudent::GetPatronymic() const
{
	return m_patronymic;
}


int CStudent::GetAge() const
{
	return m_age;
}


void CStudent::Rename(std::string name, std::string surname, std::string patronymic)
{
	boost::algorithm::trim(name);
	boost::algorithm::trim(surname);
	boost::algorithm::trim(patronymic);

	if (name.empty())
	{
		throw invalid_argument("name must not be empty");
	}
	if (surname.empty())
	{
		throw invalid_argument("surname must not be empty");
	}
	
	swap(m_name, name);
	swap(m_surname, surname);
	swap(m_patronymic, patronymic);
}


void CStudent::SetAge(int age)
{
	if ((age < 14) || (age > 60))
	{
		throw out_of_range("age must be in a range [14; 60]");
	}

	if (age < m_age)
	{
		throw domain_error("age cannot decrease");
	}

	m_age = age;
}
