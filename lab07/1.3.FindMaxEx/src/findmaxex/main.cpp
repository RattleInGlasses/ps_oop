// findmaxex.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

struct SprortsmanRecord
{
	string name;
	string surname;
	string patronymic;
	double height;
	double mass;
};


ostream& operator << (ostream &output, SprortsmanRecord const &record)
{
	output << "surname:    " << record.surname << endl;
	output << "name:       " << record.name << endl;
	output << "patronymic: " << record.patronymic << endl;
	output << "height:     " << record.height << endl;
	output << "mass:       " << record.mass << endl;
	return output;
}


bool Lighter(SprortsmanRecord const &record1, SprortsmanRecord const &record2)
{
	return record1.mass < record2.mass;
}


bool Shorter(SprortsmanRecord const &record1, SprortsmanRecord const &record2)
{
	return record1.height < record2.height;
}


template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const &arr, T &maxValue, Less const &less)
{
	if (arr.size() == 0)
	{
		return false;
	}

	auto pMaxValue = arr.begin();
	for (auto it = pMaxValue; it != arr.end(); ++it)
	{
		if (less(*pMaxValue, *it))
		{
			pMaxValue = it;
		}
	}

	T tmp = *pMaxValue;
	maxValue = move(tmp);
	return true;
}


typedef  function<bool(SprortsmanRecord const&, SprortsmanRecord const&)>  LessCompare;

void PrintFindMax(vector<SprortsmanRecord> const &sportsmen, LessCompare const &less, ostream &output)
{
	SprortsmanRecord record;
	if (FindMaxEx<SprortsmanRecord>(sportsmen, record, less))
	{
		output << record << endl;
	}
	else
	{
		output << "There is no sportsmen" << endl;
	}
}


template <typename T>
T ReadFromStream(istream &inputStream)
{
	T result;
	string line;
	istringstream lineStream;

	do
	{
		getline(inputStream, line);
		lineStream.clear();
		lineStream.str(line);
	} while (!(lineStream >> result));

	return result;
}


bool Choise(istream &input, ostream &output)
{
	string answer;
	
	while (true)
	{
		output << "One more sportsman record? (y/n) ";
		input >> answer;
		if ((answer == "y") || (answer == "Y"))
		{
			return true;
		}
		else if ((answer == "N") || (answer == "n"))
		{
			return false;
		}
	}
}


boost::optional<SprortsmanRecord> ReadRecord(istream &input, ostream &output)
{
	if (!Choise(input, output))
	{
		return boost::none;
	}
	
	SprortsmanRecord record;
	
	output << "name: ";
	record.name = ReadFromStream<string>(input);

	output << "surname: ";
	record.surname = ReadFromStream<string>(input);

	output << "patronymic: ";
	record.patronymic = ReadFromStream<string>(input);
	
	output << "height: ";
	record.height = ReadFromStream<double>(input);
	record.height = (record.height < 0) ? 0 : record.height;

	output << "mass: ";
	record.mass = ReadFromStream<double>(input);
	record.mass = (record.mass < 0) ? 0 : record.mass;
	
	return record;
}


vector<SprortsmanRecord> ReadRecords(istream &input, ostream &output)
{
	vector<SprortsmanRecord> sportsmen;
	while (auto record = ReadRecord(input, output))
	{
		sportsmen.push_back(*record);
	}

	return sportsmen;
}


int main()
{
	cout << "Enter info about sportsmen" << endl;
	vector<SprortsmanRecord> sportsmen = ReadRecords(cin, cout);

	cout << endl << "The tallest sportsman:" << endl;
	PrintFindMax(sportsmen, Shorter, cout);

	cout << endl << "The heaviest sportsman:" << endl;
	PrintFindMax(sportsmen, Lighter, cout);
	
	return 0;
}

