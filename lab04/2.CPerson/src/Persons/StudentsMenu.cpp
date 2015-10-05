#include "stdafx.h"
#include "StudentsMenu.h"
#include "CliFunctions.h"
#include "CliMenus.h"

using namespace std;


namespace
{
	void SetStudentProperties(CStudent &student,
		unsigned age, string const &name, unsigned height, unsigned weight,
		CUniversity const *pUniversity, int studyYear)
	{
		student.SetAge(age);
		student.SetName(name);
		student.SetHeight(height);
		student.SetWeight(weight);
		student.SetUniversity(pUniversity);
		student.SetStudyYear(studyYear);
	}

	list<reference_wrapper<const CStudent>> GetStudentListByUniversity(list<CStudent> const &students, CUniversity const &university)
	{
		list<reference_wrapper<const CStudent>> result;
		for (auto &student : students)
		{
			if (student.GetUniversity()->GetName() == university.GetName())
			{
				result.push_back(student);
			}
		}
		return result;
	}

	void PrintStudentProperties(ostream &ost,
		string const &name, Gender gender, unsigned age, unsigned height,
		unsigned weight, int studyYear, CUniversity const *pUniversity)
	{
		ost << "Name: " << name << endl
			<< "Gender: "; PrintGender(ost, gender); ost << endl
			<< "Age: " << age << endl
			<< "Height: " << height << endl
			<< "Weight: " << weight << endl
			<< "Study year: " << studyYear << endl
			<< "University: " << pUniversity->GetName() << endl;
	}

	void PrintStudentInfo(ostream &ost, CStudent const &student)
	{
		PrintStudentProperties(ost,
			student.GetName(), student.GetGender(), student.GetAge(), student.GetHeight(),
			student.GetWeight(), student.GetStudyYear(), student.GetUniversity());
	}
}


CStudentsMenu::CStudentsMenu(ostream &ost, istream &ist, list<CStudent> &students, std::list<CUniversity> &universities) :
m_ost(ost),
m_ist(ist),
m_students(students),
m_universities(universities)
{
}


bool CStudentsMenu::Start()
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "StudentsMenu", {
		{ "1", bind(&CStudentsMenu::ShowStudents, &*this) },
		{ "2", bind(&CStudentsMenu::AddStudent, &*this) },
		{ "3", bind(&CStudentsMenu::EditStudents, &*this) },
		{ "4", bind(&CStudentsMenu::DeleteStudent, &*this) }
	});
	
	return HaveChangesBeenHappened();
}


// Menu relations functions

void CStudentsMenu::ShowStudents() const
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "ShowStudentsMenu", {
		{ "1", bind(&CStudentsMenu::ShowAllStudents, &*this) },
		{ "2", bind(&CStudentsMenu::ShowStudentsByUniverisity, &*this) },
	});
}


void CStudentsMenu::ShowAllStudents() const
{
	ShowStudentList(m_students, "ShowAllStudentsMenu");
}


void CStudentsMenu::ShowStudentsByUniverisity() const
{
	if (auto university = ChooseOrganizationPtrMenu(m_ost, m_ist, m_universities))
	{
		auto studentsOfUniversity = GetStudentListByUniversity(m_students, **university);
		ShowStudentList(studentsOfUniversity, "ShowStudentsByUniversityMenu");
	}
}


void CStudentsMenu::ShowStudent(CStudent const &student) const
{
	ListChoiseAndReturnWithoutProcessFunctionMenu(m_ost, m_ist,
		bind(PrintStudentInfo, ref(m_ost), student));
}


void CStudentsMenu::AddStudent()
{
	string name = ReadNonEmptyString(m_ost, m_ist, "Enter new student's name");
	Gender gender = ReadGender(m_ost, m_ist, "Is the student male? (Y/N)");
	unsigned age = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "How old is the student?", "The age must be more than 0");
	unsigned height = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the student's height?", "The height must be more than 0");
	unsigned weight = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the student's weight?", "The weight must be more than 0");
	int studyYear = ReadFromStreamWithRestrictionsUntilResultIsGiven<int>(m_ost, m_ist, 1, 5, "What is the student's study year?", "The study year must be in range [1; 5]");
	CUniversity const *pUniversity = ChooseOrganizationPtrWithoutCancelMenu(m_ost, m_ist, m_universities, "Where does the student study?");

	if (EditStudentProperties(gender, name, age, height, weight, studyYear, pUniversity))
	{
		m_students.push_back(CStudent(gender, age, name, height, weight, pUniversity, studyYear));
	}
}


bool CStudentsMenu::EditStudentProperties(Gender &gender, string &name,	unsigned &age,
	unsigned &height, unsigned &weight, int &studyYear, CUniversity const *&pUniversity)
{
	string menuName = "EditStudentPropertiesMenu";

	auto genderCopy = gender;
	auto nameCopy = name;
	auto ageCopy = age;
	auto heightCopy = height;
	auto weightCopy = weight;
	auto studyYearCopy = studyYear;
	auto pUniversityCopy = pUniversity;
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName, 
			bind(PrintStudentProperties, ref(m_ost), nameCopy, genderCopy, ageCopy, heightCopy, weightCopy, studyYearCopy, pUniversityCopy));
		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetStudentName(nameCopy);
		}
		if (command == "2")
		{
			SetStudentGender(genderCopy);
		}
		if (command == "3")
		{
			SetStudentAge(ageCopy);
		}
		if (command == "4")
		{
			SetStudentHeight(heightCopy);
		}
		if (command == "5")
		{
			SetStudentWeight(weightCopy);
		}
		if (command == "6")
		{
			SetStudentStudyYear(studyYearCopy);
		}
		if (command == "7")
		{
			SetStudentUniversity(pUniversityCopy);
		}
		else if (command == "a")
		{
			gender = genderCopy;
			name = nameCopy;
			age = ageCopy;
			height = heightCopy;
			weight = weightCopy;
			studyYear = studyYearCopy;
			pUniversity = pUniversityCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


void CStudentsMenu::EditStudents()
{
	ListChoiseAndReturnWithProcessFunctionMenu(m_ost, m_ist, "EditStudentsMenu", m_students,
		bind(&CStudentsMenu::EditStudent, &*this, std::placeholders::_1));
}


void CStudentsMenu::EditStudent(CStudent &student)
{
	string menuName = "EditStudentMenu";

	auto name = student.GetName();
	auto age = student.GetAge();
	auto height = student.GetHeight();
	auto weight = student.GetWeight();
	auto studyYear = student.GetStudyYear();
	auto pUniversity = student.GetUniversity();
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName, 
			bind(PrintStudentProperties, ref(m_ost), name, student.GetGender(), age, height, weight, studyYear, pUniversity));
		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetStudentName(name);
		}
		if (command == "2")
		{
			SetStudentAge(age, student.GetAge());
		}
		if (command == "3")
		{
			SetStudentHeight(height, student.GetHeight());
		}
		if (command == "4")
		{
			SetStudentWeight(weight);
		}
		if (command == "5")
		{
			SetStudentStudyYear(studyYear, student.GetStudyYear());
		}
		if (command == "6")
		{
			SetStudentUniversity(pUniversity);
		}
		else if (command == "a")
		{
			SetStudentProperties(student, age, name, height, weight, pUniversity, studyYear);
			MarkChangesOccurrence();
			return;
		}
		else if (command == "c")
		{
			return;
		}
	}
}


void CStudentsMenu::DeleteStudent()
{
	if (m_students.size() > 0)
	{
		if (DeleteListElementMenu<CStudent>(m_ost, m_ist, m_students, "DeleteStudentMenu"))
		{
			MarkChangesOccurrence();
		}
	}
}


// Work with data functions

void CStudentsMenu::SetStudentName(std::string &name) const
{
	name = ReadNonEmptyString(m_ost, m_ist, "Enter new name for the student");
}


void CStudentsMenu::SetStudentGender(Gender &gender) const
{
	gender = ReadGender(m_ost, m_ist, "Is the student male? (Y/N)");
}


void CStudentsMenu::SetStudentAge(unsigned &age, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, age, min, UINT_MAX,
		"Enter new age for the student",
		"Can't set the age. The new age must be more than previous and more than 0");
}


void CStudentsMenu::SetStudentHeight(unsigned &height, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, height, min, UINT_MAX,
		"Enter new height for the student",
		"Can't set the height. The new height must be more than previous and more than 0");
}


void CStudentsMenu::SetStudentWeight(unsigned &weight) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, weight, 1u, UINT_MAX,
		"Enter new weight for the student",
		"The weight must be more than 0");
}


void CStudentsMenu::SetStudentStudyYear(int &studyYear, int min /*= 1*/) const
{
	SetValueWithRestrictions<int>(m_ost, m_ist, studyYear, min, 5,
		"Enter new study year for the student",
		"The study year must be in range [1; 5] and more than previous");
}


void CStudentsMenu::SetStudentUniversity(CUniversity const *&pUniversity) const
{
	if (auto university = ChooseOrganizationPtrMenu<CUniversity>(m_ost, m_ist, m_universities))
	{
		pUniversity = *university;
	}
}

