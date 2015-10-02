// Persons.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"
#include "CLIMenu.h"
#include "SaverLoader.h"

using namespace std;

string DEFAULT_DATAFILE_NAME = "data.txt";


bool ReadAnswer(istream &ost)
{
	string answer;
	for (;;)
	{
		ost >> answer;
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

bool SaveToFilePrompt(istream &ist, ostream &ost)
{
	ost << "Do you want to save changes? (Y/N) ";
	return ReadAnswer(ist);
}

void LoadFromFile(ostream &ost, string &datafileName, list<CStudent> &students, list<CUniversity> &universities, list<CWorker> &workers, list<CCompany> &companies)
{
	if (!LoadData(datafileName, students, universities, workers, companies))
	{
		if (datafileName != DEFAULT_DATAFILE_NAME)
		{
			ost << "Warning: Error opening given file. Switching to default file." << endl;
			datafileName = DEFAULT_DATAFILE_NAME;
			if (!LoadData(datafileName, students, universities, workers, companies))
			{
				ost << "Warning: Error opening default file. The database is empty." << endl;
				ost << "Warning: At closing the DBMS will attempt to save data to default location" << endl;
			}
		}
		else
		{
			ost << "Warning: Error opening default file. The database is empty." << endl;
			ost << "Warning: At closing the DBMS will attempt to save data to default location" << endl;
		}
	}
}

string GetDataFilename(int argc, char *argv[])
{
	if (argc == 1)
	{
		return DEFAULT_DATAFILE_NAME;
	}
	return argv[1];
}

bool CheckArgc(int argc)
{
	if (argc > 2)
	{
		cout << "Too many arguments" << endl;
		cout << "The program is a DBMS for a DB of persons and organizations" << endl;
		cout << "USAGE: persons <data file>" << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!CheckArgc(argc))
	{
		return 1;
	}
	string datafileName = GetDataFilename(argc, argv);
	
	list<CStudent> students;
	list<CUniversity> universities;
	list<CWorker> workers;
	list<CCompany> companies;
	CCLIMenu menu(cout, cin);

	LoadFromFile(cout, datafileName, students, universities, workers, companies);	
	if (menu.Start(students, universities, workers, companies))
	{
		if (SaveToFilePrompt(cin, cout))
		{
			SaveData(datafileName, students, universities, workers, companies);
		}
	}

	return 0;
}

