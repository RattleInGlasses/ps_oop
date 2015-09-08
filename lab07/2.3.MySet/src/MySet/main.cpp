// MySet.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MySet.h"

using namespace std;


struct Student
{
	int id;
	string name;
	bool operator ==(Student const &st2) const
	{
		return id == st2.id;
	}
};
typedef CMySet<Student> StudentsSet;


void PrintStudentsSet(ostream &output, StudentsSet const &set)
{
	for (size_t i = 0; i < set.GetSize(); ++i)
	{
		cout << set[i].name << endl;
	}
}


void PrintResult(StudentsSet const &set1, StudentsSet const &set2, StudentsSet const &set3)
{
	cout << "group 1, not winners:" << endl;
	PrintStudentsSet(cout, set1);
	cout << endl << "group 2, not winners:" << endl;
	PrintStudentsSet(cout, set2);
	cout << endl << "group 3, not winners:" << endl;
	PrintStudentsSet(cout, set3);
}


void Randomize()
{
	srand(time(nullptr));
}


int IntRandom(int min, int max)
{
	return rand() % (max + 1) + min;
}


CMySet<int> RandomIntSet(int min, int max, size_t n)
{
	CMySet<int> result;
	Randomize();
	while (n > 0)
	{
		int rndInt = IntRandom(min, max);
		if (!result.Contains(rndInt))
		{
			result.Add(rndInt);
			--n;
		}
	}

	return result;
}


StudentsSet MakeStudentsSubsetByIndexes(StudentsSet const &students, CMySet<int> indexes)
{
	StudentsSet result;
	for (int i = 0; i < indexes.GetSize(); ++i)
	{
		result.Add(students[indexes[i]]);
	}
	return result;
}


StudentsSet GetNStudents(StudentsSet students, int n)
{
	n = (n > students.GetSize()) ? students.GetSize() : n;
	return MakeStudentsSubsetByIndexes(students, RandomIntSet(0, (students.GetSize() - 1), n));
}


void FindNonWinners(StudentsSet const &group1, StudentsSet const &group2, StudentsSet const &group3,
	StudentsSet &loosers1, StudentsSet &loosers2, StudentsSet &loosers3)
{
	StudentsSet olymp1 = GetNStudents(group1, 5);
	StudentsSet olymp2 = GetNStudents(group2, 5);
	StudentsSet olymp3 = GetNStudents(group3, 5);

	StudentsSet olympAll;
	olympAll.Unite(olymp1);
	olympAll.Unite(olymp2);
	olympAll.Unite(olymp3);

	StudentsSet winners = GetNStudents(olympAll, 3);

	loosers1 = olymp1;
	loosers2 = olymp2;
	loosers3 = olymp3;
	loosers1.Difference(winners);
	loosers2.Difference(winners);
	loosers3.Difference(winners);
}


void GetData(StudentsSet &group1, StudentsSet &group2, StudentsSet &group3)
{
	group1 = 
	{
		{ 1, "name1" },
		{ 2, "name2" },
		{ 3, "name3" },
		{ 4, "name4" },
		{ 5, "name5" },
		{ 6, "name6" },
		{ 7, "name7" },
		{ 8, "name8" },
		{ 9, "name9" },
		{ 10, "name10" },
		{ 11, "name11" },
		{ 12, "name12" },
		{ 13, "name13" },
		{ 14, "name14" },
		{ 15, "name15" },
		{ 16, "name16" }
	};
	group2 =
	{
		{ 21, "name21" },
		{ 22, "name22" },
		{ 23, "name23" },
		{ 24, "name24" },
		{ 25, "name25" },
		{ 26, "name26" },
		{ 27, "name27" },
		{ 28, "name28" },
		{ 29, "name29" },
		{ 30, "name30" },
		{ 31, "name31" },
		{ 32, "name32" },
		{ 33, "name33" },
		{ 34, "name34" },
		{ 35, "name35" },
		{ 36, "name36" }
	};
	group3 =
	{
		{ 41, "name41" },
		{ 42, "name42" },
		{ 43, "name43" },
		{ 44, "name44" },
		{ 45, "name45" },
		{ 46, "name46" },
		{ 47, "name47" },
		{ 48, "name48" },
		{ 49, "name49" },
		{ 50, "name50" },
		{ 51, "name51" },
		{ 52, "name52" },
		{ 53, "name53" },
		{ 54, "name54" },
		{ 55, "name55" },
		{ 56, "name56" }
	};
}


int main(int argc, char* argv[])
{
	StudentsSet group1, group2, group3;
	GetData(group1, group2, group3);

	StudentsSet loosers1, loosers2, loosers3;
	FindNonWinners(group1, group2, group3, loosers1, loosers2, loosers3);

	PrintResult(loosers1, loosers2, loosers3);

	return 0;
}
