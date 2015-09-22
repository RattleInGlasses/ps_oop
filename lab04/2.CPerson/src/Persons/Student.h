#pragma once
#include "Person.h"
#include "University.h"
class CStudent :
	public CPerson
{
public:
	CStudent(Gender gender, unsigned age, std::string const &name, unsigned height,
		unsigned weight, CUniversity const *pUniversity, int studyYear = 1);
	virtual ~CStudent() override final {};
public:
	CUniversity const *GetUniversity() const;
	int GetStudyYear() const;
	void SetUniversity(CUniversity const *value);
	void SetStudyYear(int value);
private:
	CUniversity const *m_pUniversity;
	int m_studyYear;
};

