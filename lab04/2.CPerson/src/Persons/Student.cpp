#include "stdafx.h"
#include "Student.h"

using namespace std;

namespace
{
	void CheckUniversityPtrThrow(CUniversity const *pUniversity)
	{
		if (pUniversity == nullptr)
		{
			throw invalid_argument("A student must be a university");
		}
	}

	void CheckStudyYearRangeThrow(int studyYear)
	{
		if ((studyYear < 1) || (studyYear > 5))
		{
			throw invalid_argument("The study year must be in range [1;5]");
		}
	}

	void CheckStudyYearIncreaseThrow(int newStudyYear, int prevStudyYear)
	{
		if (newStudyYear < prevStudyYear)
		{
			throw invalid_argument("The study year can only increase");
		}
	}
}


CStudent::CStudent(Gender gender, unsigned age, std::string const &name, unsigned height, unsigned weight,
	CUniversity const *pUniversity, int studyYear /* = 1 */) :
	CPerson(gender, age, name, height, weight),
	m_pUniversity(pUniversity),
	m_studyYear(studyYear)
{
	CheckUniversityPtrThrow(m_pUniversity);
	CheckStudyYearRangeThrow(m_studyYear);
}


CUniversity const *CStudent::GetUniversity() const
{
	return m_pUniversity;
}


int CStudent::GetStudyYear() const
{
	return m_studyYear;
}


void CStudent::SetUniversity(CUniversity const *value)
{
	CheckUniversityPtrThrow(value);
	m_pUniversity = value;
}


void CStudent::SetStudyYear(int value)
{
	CheckStudyYearIncreaseThrow(value, m_studyYear);
	CheckStudyYearRangeThrow(value);
	m_studyYear = value;
}


/*
CStudent &CStudent::operator =(CStudent const &student2)
{
	if (GetGender() == student2.GetGender())
	{
		m_pUniversity = student2.m_pUniversity;
		m_studyYear = student2.m_studyYear;
		SetName(student2.GetName());
		SetAge(student2.GetAge());
		SetHeight(student2.GetHeight());
		SetWeight(student2.GetWeight());
	}
	
	return *this;
}*/

