#include "stdafx.h"
#include "CLIMenu.h"

using namespace std;
using namespace boost;

namespace
{
	map<string, vector<string>> const MENU_PROMPT =
	{
		{
			"MainMenu",
			{
				{ "What do you want to work with?" },
				{ "1. Universities" },
				{ "2. Students" },
				{ "3. Companies" },
				{ "4. Workers" },
				{ "Q. Nothing (Exit the program)" }
			}
		},
		{
			"UniversitiesMenu",
			{
				{ "1. Show all universities" },
				{ "2. Add university" },
				{ "3. Edit university" },
				{ "4. Delete university" },
				{ "R. Return to main menu" }
			}
		},
		{
			"EditUniversitiesMenu",
			{
				{ "<id>. Edit university" },
				{ "R. Return" }
			}
		},
		{
			"EditUniversityMenu",
			{
				{ "1. Change name" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteUniversityMenu",
			{
				{ "<id>. Delete university" },
				{ "C. Cancel" }
			}
		},
		{
			"StudentsMenu",
			{
				{ "1. Show students" },
				{ "2. Add student" },
				{ "3. Edit students" },
				{ "4. Delete student" },
				{ "R. Return to main menu" }
			}
		},
		{
			"ShowStudentsMenu",
			{
				{ "1. Show all students" },
				{ "2. Show students of a university" },
				{ "R. Return" }
			}
		},
		{
			"ShowAllStudentsMenu",
			{
				{ "<id>. Show student" },
				{ "R. Return" }
			}
		},
		{
			"ShowStudentsByUniversityMenu",
			{
				{ "<id>. Show student" },
				{ "R. Return" }
			}
		},
		{
			"ShowStudentMenu",
			{
				{ "R. Return" }
			}
		},
		
		{
			"EditStudentsMenu",
			{
				{ "<id>. Edit student" },
				{ "R. Return" }
			}
		},
		{
			"EditStudentMenu",
			{
				{ "1. Change name" },
				{ "2. Change age" },
				{ "3. Change height" },
				{ "4. Change weight" },
				{ "5. Change study year" },
				{ "6. Change university" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditStudentPropertiesMenu",
			{
				{ "1. Change name" },
				{ "2. Change gender" },
				{ "3. Change age" },
				{ "4. Change height" },
				{ "5. Change weight" },
				{ "6. Change study year" },
				{ "7. Change university" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteStudentMenu",
			{
				{ "<id>. Delete student" },
				{ "C. Cancel" }
			}
		},
		{
			"CompaniesMenu",
			{
				{ "1. Show all companies" },
				{ "2. Add company" },
				{ "3. Edit company" },
				{ "4. Delete company" },
				{ "R. Return to main menu" }
			}
		},
		{
			"ShowCompaniesMenu",
			{
				{ "<id>. Show company" },
				{ "R. Return" }
			}
		},
		{
			"ShowCompanyMenu",
			{
				{ "R. Return" }
			}
		},
		{
			"EditCompaniesMenu",
			{
				{ "<id>. Edit company" },
				{ "R. Return" }
			}
		},
		{
			"EditCompanyMenu",
			{
				{ "1. Change name" },
				{ "2. Change website" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteCompanyMenu",
			{
				{ "<id>. Delete company" },
				{ "C. Cancel" }
			}
		},
		{
			"WorkersMenu",
			{
				{ "1. Show workers" },
				{ "2. Add worker" },
				{ "3. Edit workers" },
				{ "4. Delete worker" },
				{ "R. Return to main menu" }
			}
		},
		{
			"ShowWorkersMenu",
			{
				{ "1. Show all workers" },
				{ "2. Show workers of a company" },
				{ "R. Return" }
			}
		},
		{
			"ShowAllWorkersMenu",
			{
				{ "<id>. Show worker" },
				{ "R. Return" }
			}
		},
		{
			"ShowWorkersByCompanyMenu",
			{
				{ "<id>. Show student" },
				{ "R. Return" }
			}
		},
		{
			"ShowWorkerMenu",
			{
				{ "R. Return" }
			}
		},
		{
			"EditWorkersMenu",
			{
				{ "<id>. Edit workers" },
				{ "R. Return" }
			}
		},
		{
			"EditWorkerMenu",
			{
				{ "1. Change name" },
				{ "2. Change age" },
				{ "3. Change height" },
				{ "4. Change weight" },
				{ "5. Change post" },
				{ "6. Change company" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"EditWorkerPropertiesMenu",
			{
				{ "1. Change name" },
				{ "2. Change gender" },
				{ "3. Change age" },
				{ "4. Change height" },
				{ "5. Change weight" },
				{ "6. Change post" },
				{ "7. Change company" },
				{ "A. Accept" },
				{ "C. Cancel" }
			}
		},
		{
			"DeleteWorkerMenu",
			{
				{ "<id>. Delete worker" },
				{ "C. Cancel" }
			}
		},
		{
			"ShowDataList",
			{
				{ "R. Return" }
			}
		},
		{
			"ChooseOrganizationMenu",
			{
				{ "<id>. Choose" },
				{ "C. Cancel" }
			}
		},
		{
			"ChooseOrganizationWithPromptMenu",
			{
				{ "<id>. Choose" }
			}
		}
	};

	void ClearScreen()
	{
		system("cls");
	}

	void SetWorkerProperties(CWorker &worker,
		unsigned age, string const &name, unsigned height, unsigned weight,
		CCompany const *pCompany, string const &post)
	{
		worker.SetAge(age);
		worker.SetName(name);
		worker.SetHeight(height);
		worker.SetWeight(weight);
		worker.SetCompany(pCompany);
		worker.SetPost(post);
	}

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

	void DeleteWorkersByCompanyPtr(CCompany *pCompany, list<CWorker> &workers)
	{
		for (auto it = workers.begin(); it != workers.end();)
		{
			if (it->GetCompany() == pCompany)
			{
				workers.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

	void DeleteStudentsByUniversityPtr(CUniversity *pUniversity, list<CStudent> &students)
	{
		for (auto it = students.begin(); it != students.end();)
		{
			if (it->GetUniversity() == pUniversity)
			{
				students.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

	template <typename T>
	bool NameOccupied(string const &name, list<T> const &dataList)
	{
		for (auto &elem : dataList)
		{
			if (Lower(elem.GetName()) == Lower(name))
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	T &GetListElement(list<T> &dataList, size_t elementIndex)
	{
		auto it = dataList.begin();
		advance(it, elementIndex);
		return *it;
	}

	template<typename T>
	T const &GetListElement(list<T> const &dataList, size_t elementIndex)
	{
		auto it = dataList.begin();
		advance(it, elementIndex);
		return *it;
	}

	template<typename T>
	void DeleteListElement(list<T> &dataList, size_t elementToDeleteIndex)
	{
		auto it = dataList.begin();
		advance(it, elementToDeleteIndex);
		dataList.erase(it);
	}

	template <typename T>
	void PrintList(ostream &ost, list<T> const &listToPrint)
	{
		size_t i = 0;
		for (auto &element : listToPrint)
		{
			ost << ++i << ". " << element.GetName() << endl;
		}
	}

	template <typename RefType>
	void PrintReferenceList(ostream &ost, list<RefType> const &listToPrint)
	{
		size_t i = 0;
		for (auto &element : listToPrint)
		{
			ost << ++i << ". " << element.get().GetName() << endl;
		}
	}

	list<reference_wrapper<const CWorker>> GetWorkerListByCompany(list<CWorker> const &workers, CCompany const &company)
	{
		list<reference_wrapper<const CWorker>> result;
		for (auto &worker : workers)
		{
			if (worker.GetCompany() == &company)
			{
				result.push_back(worker);
			}
		}
		return result;
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

	void PrintGender(ostream &ost, Gender gender)
	{
		if (gender == Gender::FEMALE)
		{
			ost << "f";
		}
		else if (gender == Gender::MALE)
		{
			ost << "m";
		}
	}

	void PrintWorkerInfo(ostream &ost,
		string const &name, Gender gender, unsigned age, unsigned height,
		unsigned weight, string const &post, CCompany const *pCompany)
	{
		ost << "Name: " << name << endl
			<< "Gender: "; PrintGender(ost, gender); ost << endl
			<< "Age: " << age << endl
			<< "Height: " << height << endl
			<< "Weight: " << weight << endl
			<< "Post: " << post << endl
			<< "Company: " << pCompany->GetName() << endl;
	}

	void PrintWorkerInfo(ostream &ost, CWorker const &worker)
	{
		PrintWorkerInfo(ost,
			worker.GetName(), worker.GetGender(), worker.GetAge(), worker.GetHeight(),
			worker.GetWeight(), worker.GetPost(), worker.GetCompany());
	}

	void PrintCompanyInfo(ostream &ost, CCompany const &company)
	{
		ost << "Name: " << company.GetName() << endl
			<< "Website: " << company.GetWebsite() << endl;
	}

	void PrintStudentInfo(ostream &ost,
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
		PrintStudentInfo(ost,
			student.GetName(), student.GetGender(), student.GetAge(), student.GetHeight(),
			student.GetWeight(), student.GetStudyYear(), student.GetUniversity());
	}

	void PrintUniversityInfo(ostream &ost, CUniversity const &university)
	{
		ost << "University" << endl;
		ost << "Name: " << university.GetName() << endl;
	}

	string ReadLine(istream &ist)
	{
		string line;
		getline(ist, line);
		return line;
	}

	string ReadNonEmptyLine(istream &ist)
	{
		string line;
		while (line == "")
		{
			getline(ist, line);
		}
		return line;
	}

	template <typename T>
	optional<T> ReadFromLine(string const &line)
	{
		T result;
		istringstream lineStream(line);
		if (lineStream >> result)
		{
			return result;
		}
		return none;
	}

	void SkipLine(istream &ist)
	{
		string s;
		getline(ist, s);
	}

	string ReadString(ostream &ost, istream &ist, string const &prompt)
	{
		ClearScreen();
		ost << prompt << endl;
		return ReadLine(ist);
	}

	string ReadNonEmptyString(ostream &ost, istream &ist, string const &prompt)
	{
		ClearScreen();
		ost << prompt << endl;
		return ReadNonEmptyLine(ist);
	}

	template <typename T>
	T ReadFromStream(ostream &ost, istream &ist, string const &prompt)
	{
		optional<T> result;
		do 
		{
			result = ReadFromLine<T>(ReadNonEmptyString(ost, ist, prompt));
		} while (!result);
		
		return *result;
	}

	template <typename T>
	optional<T> ReadFromStreamWithRestrictions(ostream &ost, istream &ist, T min, T max, string const &mainPrompt, string const &errorPrompt)
	{
		T result = ReadFromStream<T>(ost, ist, mainPrompt);
		
		for (;;)
		{
			if ((result < min) || (result > max))
			{
				ost << errorPrompt << endl;
				ost << "Do you want to enter another number? (Y/N)" << endl;
				if (ReadYesNoAnswer(ist))
				{
					result = ReadFromStream<T>(ost, ist, mainPrompt);
				}
				else
				{
					return none;
				}
			}
			else
			{
				return result;
			}
		}
	}

	template <typename T>
	T ReadFromStreamWithRestrictionsUntilResultIsGiven(ostream &ost, istream &ist, T min, T max, string const &mainPrompt, string const &errorPrompt)
	{
		T result = ReadFromStream<T>(ost, ist, mainPrompt);
		for (;;)
		{
			if ((result < min) || (result > max))
			{
				result = ReadFromStream<T>(ost, ist, errorPrompt + "\n" + mainPrompt);
			}
			else
			{
				return result;
			}
		}
	}

	bool ReadYesNoAnswer(istream &ist)
	{
		for (;;)
		{
			string answer = ReadNonEmptyLine(ist);
			if ((answer == "Y") || (answer == "y"))
			{
				return true;
			}
			if ((answer == "N") || (answer == "n"))
			{
				return false;
			}
		}
	}

	Gender ReadGender(ostream &ost, istream &ist, string const &prompt)
	{
		ClearScreen();
		ost << prompt << endl;
		if (ReadYesNoAnswer(ist))
		{
			return Gender::MALE;
		}
		return Gender::FEMALE;
	}

	string Lower(string const &str)
	{
		string result(str);
		to_lower(result, locale(".866"));
		return result;
	}
}


//////////////////////////////////////////////////////////////////////////

CCLIMenu::CCLIMenu(std::ostream &ost, std::istream &ist) :
m_ost(ost),
m_ist(ist)
{
}

void CCLIMenu::PrintMenuPrompt(string const &menuName) const
{
	for (auto &line : MENU_PROMPT.at(menuName))
	{
		m_ost << line << endl;
	}
}

string CCLIMenu::ReadUserCommand() const
{
	string command;
	m_ist >> command;
	to_lower(command);
	return command;
}


// menu relations functions
// TODO Menu
bool CCLIMenu::Start(list<CStudent> &students,
	list<CUniversity> &universities,
	list<CWorker> &workers,
	list<CCompany> &companies)
{
	MainMenu(students, universities, workers, companies);
	return m_dataChanged;
}

void CCLIMenu::MainMenu(list<CStudent> &students,
	list<CUniversity> &universities,
	list<CWorker> &workers,
	list<CCompany> &companies)
{
	string menuName = "MainMenu";

	for (;;)
	{
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			UniversitiesMenu(universities, students);
		}
		else if (command == "2")
		{
			StudentsMenu(students, universities);
		}
		else if (command == "3")
		{
			CompaniesMenu(companies, workers);
		}
		else if (command == "4")
		{
			WorkersMenu(workers, companies);
		}
		else if (command == "q")
		{
			return;
		}
		ClearScreen();
	}
}

void CCLIMenu::UniversitiesMenu(list<CUniversity> &universities, list<CStudent> &students)
{
	string menuName = "UniversitiesMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowDataList<CUniversity>(universities);
		}
		else if (command == "2")
		{
			AddUniversity(universities);
		}
		else if (command == "3")
		{
			EditUniversities(universities);
		}
		else if (command == "4")
		{
			DeleteUniversity(universities, students);
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::StudentsMenu(std::list<CStudent> &students, std::list<CUniversity> const &universities)
{
	string menuName = "StudentsMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowStudents(students, universities);
		}
		else if (command == "2")
		{
			AddStudent(students, universities);
		}
		else if (command == "3")
		{
			EditStudents(students, universities);
		}
		else if (command == "4")
		{
			DeleteStudent(students);
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowStudents(list<CStudent> const &students, list<CUniversity> const &universities) const
{
	string menuName = "ShowStudentsMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowAllStudents(students);
		}
		else if (command == "2")
		{
			if (auto university = ChooseOrganizationPtr(universities))
			{
				ShowStudentsByUniversity(students, **university);
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::CompaniesMenu(std::list<CCompany> &companies, std::list<CWorker> &workers)
{
	string menuName = "CompaniesMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowCompanies(companies);
		}
		else if (command == "2")
		{
			AddCompany(companies);
		}
		else if (command == "3")
		{
			EditCompanies(companies);
		}
		else if (command == "4")
		{
			DeleteCompany(companies, workers);
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::WorkersMenu(std::list<CWorker> &workers, std::list<CCompany> const &companies)
{
	string menuName = "WorkersMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowWorkers(workers, companies);
		}
		else if (command == "2")
		{
			AddWorker(workers, companies);
		}
		else if (command == "3")
		{
			EditWorkers(workers, companies);
		}
		else if (command == "4")
		{
			DeleteWorker(workers);
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowWorkers(std::list<CWorker> const &workers, std::list<CCompany> const &companies) const
{
	string menuName = "ShowWorkersMenu";

	for (;;)
	{
		ClearScreen();
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		if (command == "1")
		{
			ShowAllWorkers(workers);
		}
		else if (command == "2")
		{
			if (auto company = ChooseOrganizationPtr(companies))
			{
				ShowWorkersByCompany(workers, **company);
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


// Show functions
// TODO Show
void CCLIMenu::ShowAllStudents(std::list<CStudent> const &students) const
{
	string menuName = "ShowAllStudentsMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, students);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= students.size())
			{
				ShowStudent(GetListElement(students, *choosenRecord - 1));
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowStudentsByUniversity(std::list<CStudent> const &students, CUniversity const &university) const
{
	string menuName = "ShowStudentsByUniversityMenu";

	auto studentsOfUniversity = GetStudentListByUniversity(students, university);
	for (;;)
	{
		ClearScreen();
		PrintReferenceList(m_ost, studentsOfUniversity);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= studentsOfUniversity.size())
			{
				ShowStudent(GetListElement(studentsOfUniversity, *choosenRecord - 1));
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowStudent(CStudent const &student) const
{
	string menuName = "ShowStudentMenu";

	for (;;)
	{
		ClearScreen();
		PrintStudentInfo(m_ost, student);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowCompanies(list<CCompany> const &companies) const
{
	string menuName = "ShowCompaniesMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, companies);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= companies.size())
			{
				ShowCompany(GetListElement(companies, *choosenRecord - 1));
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowCompany(CCompany const &company) const
{
	string menuName = "ShowCompanyMenu";

	for (;;)
	{
		ClearScreen();
		PrintCompanyInfo(m_ost, company);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowAllWorkers(std::list<CWorker> const &workers) const
{
	string menuName = "ShowAllWorkersMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, workers);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= workers.size())
			{
				ShowWorker(GetListElement(workers, *choosenRecord - 1));
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowWorkersByCompany(std::list<CWorker> const &workers, CCompany const &company) const
{
	string menuName = "ShowWorkersByCompanyMenu";

	auto workersOfCompany = GetWorkerListByCompany(workers, company);
	for (;;)
	{
		ClearScreen();
		PrintReferenceList(m_ost, workersOfCompany);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= workersOfCompany.size())
			{
				ShowWorker(GetListElement(workersOfCompany, *choosenRecord - 1));
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::ShowWorker(CWorker const &worker) const
{
	string menuName = "ShowWorkerMenu";

	for (;;)
	{
		ClearScreen();
		PrintWorkerInfo(m_ost, worker);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "r")
		{
			return;
		}
	}
}


// Add functions
// TODO Add
void CCLIMenu::AddUniversity(list<CUniversity> &universities) 
{
	CUniversity university("nothing");
	if (SetUniversityName(university, universities))
	{
		universities.push_back(university);
		MarkChangesOccurrence();
	}
}


void CCLIMenu::AddStudent(list<CStudent> &students, list<CUniversity> const &universities)
{
	string name = ReadNonEmptyString(m_ost, m_ist, "Enter new student's name");
	Gender gender = ReadGender(m_ost, m_ist, "Is the student male? (Y/N)");
	unsigned age = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "How old is the student?", "The age must be more than 0");
	unsigned height = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the student's height?", "The height must be more than 0");
	unsigned weight = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the student's weight?", "The weight must be more than 0");
	int studyYear = ReadFromStreamWithRestrictionsUntilResultIsGiven<int>(m_ost, m_ist, 1, 5, "What is the student's study year?", "The study year must be in range [1; 5]");
	CUniversity const *pUniversity = ChooseOrganizationPtrWithPrompt(universities, "Where does the student study?");

	if (EditStudentProperties(gender, name, age, height, weight, studyYear, pUniversity, universities))
	{
		students.push_back(CStudent(gender, age, name, height, weight, pUniversity, studyYear));
	}
}


void CCLIMenu::AddCompany(list<CCompany> &companies)
{
	CCompany newCompany("nothing");
	if (!SetCompanyName(newCompany, companies))
	{
		return;
	}
	newCompany.SetWebsite(ReadString(m_ost, m_ist, "Enter new company's website"));

	if (EditCompany(newCompany, companies))
	{
		companies.push_back(newCompany);
		MarkChangesOccurrence();
	}
}


void CCLIMenu::AddWorker(std::list<CWorker> &workers, std::list<CCompany> const &companies)
{
	string name = ReadNonEmptyString(m_ost, m_ist, "Enter new worker's name");
	Gender gender = ReadGender(m_ost, m_ist, "Is the worker male? (Y/N)");
	unsigned age = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "How old is the worker?", "The age must be more than 0");
	unsigned height = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the worker's height?", "The height must be more than 0");
	unsigned weight = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the worker's weight?", "The weight must be more than 0");
	string post = ReadNonEmptyString(m_ost, m_ist, "Enter new worker's post");
	CCompany const *pCompany = ChooseOrganizationPtrWithPrompt(companies, "Where does the worker has a job?");

	if (EditWorkerProperties(gender, name, age, height, weight, post, pCompany, companies))
	{
		workers.push_back(CWorker(gender, age, name, height, weight, pCompany, post));
	}
}


// Edit functions
// TODO Edit
void CCLIMenu::EditUniversities(list<CUniversity> &universities)
{
	string menuName = "EditUniversitiesMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, universities);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();
		
		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= universities.size())
			{
				EditUniversity(GetListElement(universities, *choosenRecord - 1), universities);
			}
		}		
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::EditUniversity(CUniversity &university, list<CUniversity> const &universities)
{
	string menuName = "EditUniversityMenu";

	CUniversity universityCopy = university;
	for (;;)
	{
		ClearScreen();
		PrintUniversityInfo(m_ost, universityCopy);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			SetUniversityName(universityCopy, universities);
		}
		else if (command == "a")
		{
			university = universityCopy;
			MarkChangesOccurrence();
			return;
		}
		else if (command == "c")
		{
			return;
		}
	}
}


void CCLIMenu::EditStudents(list<CStudent> &students, list<CUniversity> const &universities)
{
	string menuName = "EditStudentsMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, students);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= students.size())
			{
				EditStudent(GetListElement(students, *choosenRecord - 1), universities);
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::EditStudent(CStudent &student, list<CUniversity> const &universities)
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
		ClearScreen();
		PrintStudentInfo(m_ost, name, student.GetGender(), age, height, weight, studyYear, pUniversity);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

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
			SetStudentUniversity(pUniversity, universities);
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


bool CCLIMenu::EditStudentProperties(Gender &gender, string &name, unsigned &age,
	unsigned &height, unsigned &weight, int &studyYear, CUniversity const *&pUniversity,
	list<CUniversity> const &universities)
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
		ClearScreen();
		PrintStudentInfo(m_ost, nameCopy, genderCopy, ageCopy, heightCopy, weightCopy, studyYearCopy, pUniversityCopy);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

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
			SetStudentUniversity(pUniversityCopy, universities);
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


void CCLIMenu::EditCompanies(list<CCompany> &companies)
{
	string menuName = "EditCompaniesMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, companies);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= companies.size())
			{
				EditCompany(GetListElement(companies, *choosenRecord - 1), companies);
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


bool CCLIMenu::EditCompany(CCompany &company, std::list<CCompany> const &companies)
{
	string menuName = "EditCompanyMenu";

	auto companyCopy = company;
	for (;;)
	{
		ClearScreen();
		PrintCompanyInfo(m_ost, companyCopy);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			SetCompanyName(companyCopy, companies);
		}
		else if (command == "2")
		{
			SetCompanyWebsite(companyCopy);
		}
		else if (command == "a")
		{
			company = companyCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


void CCLIMenu::EditWorkers(std::list<CWorker> &workers, std::list<CCompany> const &companies)
{
	string menuName = "EditWorkersMenu";

	for (;;)
	{
		ClearScreen();
		PrintList(m_ost, workers);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (auto choosenRecord = ReadFromLine<size_t>(command))
		{
			if (*choosenRecord <= workers.size())
			{
				EditWorker(GetListElement(workers, *choosenRecord - 1), companies);
			}
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void CCLIMenu::EditWorker(CWorker &worker, std::list<CCompany> const &companies)
{
	string menuName = "EditWorkerMenu";

	auto name = worker.GetName();
	auto age = worker.GetAge();
	auto height = worker.GetHeight();
	auto weight = worker.GetWeight();
	auto post = worker.GetPost();
	auto pCompany = worker.GetCompany();
	for (;;)
	{
		ClearScreen();
		PrintWorkerInfo(m_ost, name, worker.GetGender(), age, height, weight, post, pCompany);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			SetWorkerName(name);
		}
		if (command == "2")
		{
			SetWorkerAge(age, worker.GetAge());
		}
		if (command == "3")
		{
			SetWorkerHeight(height, worker.GetHeight());
		}
		if (command == "4")
		{
			SetWorkerWeight(weight);
		}
		if (command == "5")
		{
			SetWorkerPost(post);
		}
		if (command == "6")
		{
			SetWorkerCompany(pCompany, companies);
		}
		else if (command == "a")
		{
			SetWorkerProperties(worker, age, name, height, weight, pCompany, post);
			MarkChangesOccurrence();
			return;
		}
		else if (command == "c")
		{
			return;
		}
	}
}


bool CCLIMenu::EditWorkerProperties(Gender &gender, std::string &name, unsigned &age, unsigned &height,
	unsigned &weight, std::string &post, CCompany const *&pCompany, std::list<CCompany> const &companies)
{
	string menuName = "EditWorkerPropertiesMenu";

	auto genderCopy = gender;
	auto nameCopy = name;
	auto ageCopy = age;
	auto heightCopy = height;
	auto weightCopy = weight;
	auto postCopy = post;
	auto pCompanyCopy = pCompany;
	for (;;)
	{
		ClearScreen();
		PrintWorkerInfo(m_ost, nameCopy, genderCopy, ageCopy, heightCopy, weightCopy, postCopy, pCompanyCopy);
		m_ost << endl;
		PrintMenuPrompt(menuName);
		string command = ReadUserCommand();

		if (command == "1")
		{
			SetWorkerName(nameCopy);
		}
		if (command == "2")
		{
			SetWorkerGender(genderCopy);
		}
		if (command == "3")
		{
			SetWorkerAge(ageCopy);
		}
		if (command == "4")
		{
			SetWorkerHeight(heightCopy);
		}
		if (command == "5")
		{
			SetWorkerWeight(weightCopy);
		}
		if (command == "6")
		{
			SetWorkerPost(postCopy);
		}
		if (command == "7")
		{
			SetWorkerCompany(pCompanyCopy, companies);
		}
		else if (command == "a")
		{
			gender = genderCopy;
			name = nameCopy;
			age = ageCopy;
			height = heightCopy;
			weight = weightCopy;
			post = postCopy;
			pCompany = pCompanyCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


// Update functions
// TODO Update
string CCLIMenu::GetNewUniversityName() const
{
	return ReadNonEmptyString(m_ost, m_ist, "Enter new name for the university");
}


bool CCLIMenu::SetUniversityName(CUniversity &university, list<CUniversity> const &universities) const
{
	string name;
	for (;;)
	{
		name = ReadNonEmptyString(m_ost, m_ist, "Enter university's name");
		if (NameOccupied(name, universities))
		{
			m_ost << "There already is a university with such name.\nDo you want enter something else? (Y/N)" << endl;
			if (!ReadYesNoAnswer(m_ist))
			{
				return false;;
			}
		}
		else
		{
			university.SetName(name);
			return true;
		}
	}
}


void CCLIMenu::SetStudentName(string &name) const
{
	name = ReadNonEmptyString(m_ost, m_ist, "Enter new name for the student");
}


void CCLIMenu::SetStudentGender(Gender &gender) const
{
	gender = ReadGender(m_ost, m_ist, "Is the student male? (Y/N)");
}

void CCLIMenu::SetStudentAge(unsigned &age, unsigned min) const
{
	SetValueWithRestrictions<unsigned>(age, min, UINT_MAX,
		"Enter new age for the student",
		"Can't set the age. The new age must be more than previous and more than 0");
}


void CCLIMenu::SetStudentHeight(unsigned &height, unsigned min) const
{
	SetValueWithRestrictions<unsigned>(height, min, UINT_MAX,
		"Enter new height for the student",
		"Can't set the height. The new height must be more than previous and more than 0");
}


void CCLIMenu::SetStudentWeight(unsigned &weight) const
{
	SetValueWithRestrictions<unsigned>(weight, 1u, UINT_MAX,
		"Enter new weight for the student",
		"The weight must be more than 0");
}


void CCLIMenu::SetStudentStudyYear(int &studyYear, int min) const
{
	SetValueWithRestrictions<int>(studyYear, min, 5,
		"Enter new study year for the student",
		"The study year must be in range [1; 5] and more than previous");
}


void CCLIMenu::SetStudentUniversity(CUniversity const *&pUniversity, list<CUniversity> const &universities) const
{
	if (auto university = ChooseOrganizationPtr<CUniversity>(universities))
	{
		pUniversity = *university;
	}
}


bool CCLIMenu::SetCompanyName(CCompany &company, std::list<CCompany> const &companies) const
{
	string newName;
	for (;;)
	{
		newName = ReadNonEmptyString(m_ost, m_ist, "Enter company's name");
		if (NameOccupied(newName, companies))
		{
			m_ost << "There already is a company with such name.\nDo you want enter something else? (Y/N)" << endl;
			if (!ReadYesNoAnswer(m_ist))
			{
				return false;;
			}
		}
		else
		{
			company.SetName(newName);
			return true;
		}
	}
}



void CCLIMenu::SetCompanyWebsite(CCompany &company) const
{
	SkipLine(m_ist);
	company.SetWebsite(ReadString(m_ost, m_ist, "Enter company's website"));
}


void CCLIMenu::SetWorkerName(string &name) const
{
	name = ReadNonEmptyString(m_ost, m_ist, "Enter new name for the worker");
}


void CCLIMenu::SetWorkerGender(Gender &gender) const
{
	gender = ReadGender(m_ost, m_ist, "Is the worker male? (Y/N)");
}


void CCLIMenu::SetWorkerAge(unsigned &age, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(age, min, UINT_MAX,
		"Enter new age for the worker",
		"Can't set the age. The new age must be more than previous and more than 0");
}


void CCLIMenu::SetWorkerHeight(unsigned &height, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(height, min, UINT_MAX,
		"Enter new height for the worker",
		"Can't set the height. The new height must be more than previous and more than 0");
}


void CCLIMenu::SetWorkerWeight(unsigned &weight) const
{
	SetValueWithRestrictions<unsigned>(weight, 1u, UINT_MAX,
		"Enter new weight for the worker",
		"The weight must be more than 0");
}

void CCLIMenu::SetWorkerPost(string &post) const
{
	post = ReadNonEmptyString(m_ost, m_ist, "Enter new post for the worker");
}


void CCLIMenu::SetWorkerCompany(CCompany const *&pCompany, list<CCompany> const &companies) const
{
	if (auto company = ChooseOrganizationPtr(companies))
	{
		pCompany = *company;
	}
}


// Delete functions
// TODO Delete
void CCLIMenu::DeleteUniversity(list<CUniversity> &universities, list<CStudent> &students)
{
	if (universities.size() > 0)
	{
		if (auto pDeletedUniversity = DeleteDataListElement<CUniversity>(universities, "DeleteUniversityMenu"))
		{
			DeleteStudentsByUniversityPtr(*pDeletedUniversity, students);
		}
	}
}


void CCLIMenu::DeleteStudent(list<CStudent> &students)
{
	DeleteDataListElement<CStudent>(students, "DeleteStudentMenu");
}


void CCLIMenu::DeleteCompany(list<CCompany> &companies, list<CWorker> &workers)
{
	if (companies.size() > 0)
	{
		if (auto pDeletedCompany = DeleteDataListElement<CCompany>(companies, "DeleteCompanyMenu"))
		{
			DeleteWorkersByCompanyPtr(*pDeletedCompany, workers);
		}
	}
}


void CCLIMenu::DeleteWorker(list<CWorker> &workers)
{
	if (workers.size() > 0)
	{
		DeleteDataListElement<CWorker>(workers, "DeleteWorkerMenu");
	}
}


// other functions

void CCLIMenu::MarkChangesOccurrence()
{
	if (!m_dataChanged)
	{
		m_dataChanged = true;
	}
}

