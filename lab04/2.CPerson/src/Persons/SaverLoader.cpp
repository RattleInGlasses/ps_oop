#include "stdafx.h"
#include "SaverLoader.h"

using namespace std;
using namespace boost;


// LoadData functions

vector<string> SplitDataLine(string const &line)
{
	tokenizer<escaped_list_separator<char>> tok(line);
	vector<string> splitted;
	copy(tok.begin(), tok.end(), back_inserter(splitted));
	return splitted;
}

template <typename Organization>
Organization const *StringToOrganizationPtr(string const &str, list<Organization> const &organizations)
{
	for (auto &org : organizations)
	{
		if (str == org.GetName())
		{
			return &org;
		}
	}
	return nullptr;
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

optional<Gender> StringToGender(string const &str)
{
	if (str == "m")
	{
		return Gender::MALE;
	}
	if (str == "f")
	{
		return Gender::FEMALE;
	}
	return none;
}

optional<CWorker> ConstructWorkerFromLine(string const &line, list<CCompany> const &companies)
{
	auto lineParts = SplitDataLine(line);
	if (lineParts.size() == 7)
	{
		auto gender = StringToGender(lineParts.at(0));
		string name = lineParts.at(1);
		auto age = ReadFromLine<unsigned>(lineParts.at(2));
		auto height = ReadFromLine<unsigned>(lineParts.at(3));
		auto weight = ReadFromLine<unsigned>(lineParts.at(4));
		string post = lineParts.at(5);
		auto pCompany = StringToOrganizationPtr<CCompany>(lineParts.at(6), companies);

		if ((gender) && (age) && (height) && (weight) && (pCompany != nullptr))
		{
			try
			{
				return CWorker(*gender, *age, name, *height, *weight, pCompany, post);
			}
			catch (invalid_argument &)
			{
				return none;
			}
		}
	}
	return none;
}

optional<CCompany> ConstructCompanyFromLine(string const &line)
{
	auto lineParts = SplitDataLine(line);
	if (lineParts.size() == 2)
	{
		try
		{
			return CCompany(lineParts.at(0), lineParts.at(1));
		}
		catch (invalid_argument &)
		{
			return none;
		}
	}
	return none;
}

optional<CStudent> ConstructStudentFromLine(string const &line, list<CUniversity> const &univesities)
{
	auto lineParts = SplitDataLine(line);
	if (lineParts.size() == 7)
	{
		auto gender = StringToGender(lineParts.at(0));
		string name = lineParts.at(1);
		auto age = ReadFromLine<unsigned>(lineParts.at(2));
		auto height = ReadFromLine<unsigned>(lineParts.at(3));
		auto weight = ReadFromLine<unsigned>(lineParts.at(4));
		auto studyYear = ReadFromLine<unsigned>(lineParts.at(5));
		auto pUniversity = StringToOrganizationPtr<CUniversity>(lineParts.at(6), univesities);

		if ((gender) && (age) && (height) && (weight) && (studyYear) && (pUniversity != nullptr))
		{
			try
			{
				return CStudent(*gender, *age, name, *height, *weight, pUniversity, *studyYear);
			}
			catch (invalid_argument &)
			{
				return none;
			}
		}
	}
	return none;
}

optional<CUniversity> ConstructUnivesityFromLine(string const &line)
{
	auto lineParts = SplitDataLine(line);
	if (lineParts.size() == 1)
	{
		try
		{
			return CUniversity(lineParts.at(0));
		}
		catch (invalid_argument &)
		{
			return none;
		}
	}
	return none;
}

bool ReadWorkers(ifstream &ifs, list<CWorker> &workers, list<CCompany> const &companies)
{
	string line;
	while (getline(ifs, line))
	{
		if (auto worker = ConstructWorkerFromLine(line, companies))
		{
			workers.push_back(*worker);
		}
	}

	return true;
}

bool ReadCompanies(ifstream &ifs, list<CCompany> &companies)
{
	string line;
	while ((getline(ifs, line)) && (line != "\"workers\""))
	{
		if (auto company = ConstructCompanyFromLine(line))
		{
			companies.push_back(*company);
		}
	}

	if (line == "\"workers\"")
	{
		return true;
	}
	return false;
}

bool ReadStudents(ifstream &ifs, list<CStudent> &students, list<CUniversity> const &universities)
{
	string line;
	while ((getline(ifs, line)) && (line != "\"companies\""))
	{
		if (auto student = ConstructStudentFromLine(line, universities))
		{
			students.push_back(*student);
		}
	}

	if (line == "\"companies\"")
	{
		return true;
	}
	return false;
}

bool ReadUniversities(istream &is, list<CUniversity> &universities)
{
	string line;
	getline(is, line);
	if (line == "\"universities\"")
	{
		while ((getline(is, line)) && (line != "\"students\""))
		{
			if (auto university = ConstructUnivesityFromLine(line))
			{
				universities.push_back(*university);
			}
		}
	}

	if (line == "\"students\"")
	{
		return true;
	}
	return false;
}

bool LoadData(string const &filename,
	list<CStudent> &students,
	list<CUniversity> &universities,
	list<CWorker> &workers,
	list<CCompany> &companies)
{
	ifstream ifs(filename);
	if (ifs.is_open())
	{
		if ((ReadUniversities(ifs, universities))
			&& (ReadStudents(ifs, students, universities))
			&& (ReadCompanies(ifs, companies))
			&& (ReadWorkers(ifs, workers, companies)))
		{
		}
		return true;
	}
	return false;
}


// SaveData functions

string EscapeString(string const &str)
{
	string escapedString;
	for (auto ch : str)
	{
		if (ch == '\"')
		{
			escapedString += "\\\"";
		}
		else if (ch == ',')
		{
			((escapedString += "\"") += ch) += "\"";
		}
		else
		{
			escapedString += ch;
		}
	}
	return escapedString;
}

void WriteGender(ostream &ost, Gender gender)
{
	if (gender == Gender::MALE)
	{
		ost << "m";
	}
	if (gender == Gender::FEMALE)
	{
		ost << "f";
	}
}

void SaveWorkers(ostream &ost, list<CWorker> const &workers)
{
	ost << "\"workers\"" << endl;
	for (auto &worker : workers)
	{
		WriteGender(ost, worker.GetGender());
		ost << "," << EscapeString(worker.GetName());
		ost << "," << worker.GetAge();
		ost << "," << worker.GetHeight();
		ost << "," << worker.GetWeight();
		ost << "," << EscapeString(worker.GetPost());
		ost << "," << EscapeString(worker.GetCompany()->GetName());
		ost << endl;
	}
}

void SaveCompanies(ostream &ost, list<CCompany> const &companies)
{
	ost << "\"companies\"" << endl;
	for (auto &company : companies)
	{
		ost << EscapeString(company.GetName()) << ",";
		ost << EscapeString(company.GetWebsite()) << endl;
	}
}

void SaveStudents(ostream &ost, list<CStudent> const &students)
{
	ost << "\"students\"" << endl;
	for (auto &student : students)
	{
		WriteGender(ost, student.GetGender());
		ost << "," << EscapeString(student.GetName());
		ost << "," << student.GetAge();
		ost << "," << student.GetHeight();
		ost << "," << student.GetWeight();
		ost << "," << student.GetStudyYear();
		ost << "," << EscapeString(student.GetUniversity()->GetName());
		ost << endl;
	}
}

void SaveUniversities(ostream &ost, list<CUniversity> const &universities)
{
	ost << "\"universities\"" << endl;
	for (auto &university : universities)
	{
		ost << EscapeString(university.GetName()) << endl;
	}
}

bool SaveData(string const &filename,
	list<CStudent> const &students,
	list<CUniversity> const &universities,
	list<CWorker> const &workers,
	list<CCompany> const &companies)
{
	ofstream ofs(filename);
	if (ofs.is_open())
	{
		SaveUniversities(ofs, universities);
		SaveStudents(ofs, students);
		SaveCompanies(ofs, companies);
		SaveWorkers(ofs, workers);
		return true;
	}
	return false;
}
