#include "stdafx.h"
#include "CliFunctions.h"
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"

using namespace std;
using namespace boost;

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
		"EditCompanyPropertiesMenu",
		{
			{ "1. Edit name" },
			{ "2. Edit website" },
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
			{ "<id>. Show worker" },
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

std::string ReadUserCommand(istream &ist)
{
	string command;
	ist >> command;
	to_lower(command);
	return command;
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
		trim(line);
	}
	return line;
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

function<void()> PrintNullMessageFunction()
{
	return function<void(void)>(nullptr);
}

void PrintMenuMessage(ostream &ost, string const &menuName, function<void()> const &fShowData, string const &header)
{
	ClearScreen();
	if (!header.empty())
	{
		ost << header << endl;
	}
	if (fShowData)
	{
		fShowData();
		ost << endl;
	}
	PrintMenuPrompt(ost, menuName);
}

string Lower(string const &str)
{
	string result(str);
	to_lower(result, locale(".866"));
	return result;
}

void PrintMenuPrompt(ostream &ost, string const &menuName)
{
	for (auto &line : MENU_PROMPT.at(menuName))
	{
		ost << line << endl;
	}
}
