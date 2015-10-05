#pragma once
#include <list>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"


void ClearScreen();
std::string Lower(std::string const &str);

std::function<void()> PrintNullMessageFunction();
void PrintMenuMessage(std::ostream &ost, std::string const &menuName, std::function<void()> const &fShowData, std::string const &header = "");
void PrintMenuPrompt(std::ostream &ost, std::string const &menuName);
void PrintGender(std::ostream &ost, Gender gender);

std::string ReadUserCommand(std::istream &ist);
void SkipLine(std::istream &ist);
std::string ReadLine(std::istream &ist);
std::string ReadNonEmptyLine(std::istream &ist);
std::string ReadString(std::ostream &ost, std::istream &ist, std::string const &prompt);
std::string ReadNonEmptyString(std::ostream &ost, std::istream &ist, std::string const &prompt);
bool ReadYesNoAnswer(std::istream &ist);
Gender ReadGender(std::ostream &ost, std::istream &ist, std::string const &prompt);


template <typename Range, typename Pred>
void remove_nonmovable_if(Range &objects, Pred checkFunction);

template <typename T>
bool NameOccupied(std::string const &name, std::list<T> const &dataList);
template<typename NamedObject>
bool ReadNameWithOccupiedCheck(std::ostream &ost, std::istream &ist,
	std::string &name, std::list<NamedObject> objects,
	std::string const &readPrompt, std::string const &occupiedPrompt);
 
template <typename T>
T &GetListElement(std::list<T> &dataList, size_t elementIndex);
template<typename T>
T const &GetListElement(std::list<T> const &dataList, size_t elementIndex);
template<typename T>
T const *GetListElementConstPtr(std::list<T> const &dataList, size_t elementIndex);

template <typename T>
boost::optional<T*> DeleteListElement(std::list<T> &dataList, size_t elementToDeleteIndex);
template <typename T>
void PrintList(std::ostream &ost, std::list<T> const &listToPrint);
template <typename RefType>
void PrintReferenceList(std::ostream &ost, std::list<RefType> const &listToPrint);
 
template <typename T>
boost::optional<T> ReadFromLine(std::string const &line);
template <typename T>
T ReadFromStream(std::ostream &ost, std::istream &ist, std::string const &prompt);
template <typename T>
boost::optional<T> ReadFromStreamWithRestrictions(std::ostream &ost, std::istream &ist, T min, T max, std::string const &mainPrompt, std::string const &errorPrompt);
template <typename T>
T ReadFromStreamWithRestrictionsUntilResultIsGiven(std::ostream &ost, std::istream &ist, T min, T max, std::string const &mainPrompt, std::string const &errorPrompt);

template <typename T>
void SetValueWithRestrictions(std::ostream &ost, std::istream &ist,
	T &value, T minValue, T maxValue,
	std::string const &mainPrompt, std::string const &errorPrompt);



// Template implementation

template <typename Range, typename Pred>
void remove_nonmovable_if(Range &objects, Pred checkFunction)
{
	for (auto it = objects.begin(); it != objects.end();)
	{
		if (checkFunction(*it))
		{
			objects.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

template <typename T>
bool NameOccupied(std::string const &name, std::list<T> const &dataList)
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

template<typename NamedObject>
bool ReadNameWithOccupiedCheck(std::ostream &ost, std::istream &ist, 
	std::string &name, std::list<NamedObject> objects,
	std::string const &readPrompt, std::string const &occupiedPrompt)
{
	string newName;
	for (;;)
	{
		newName = ReadNonEmptyString(ost, ist, readPrompt);
		if (NameOccupied(newName, objects))
		{
			ost << occupiedPrompt << endl;
			if (!ReadYesNoAnswer(ist))
			{
				return false;
			}
		}
		else
		{
			name = newName;
			return true;
		}
	}
}

template<typename T>
T &GetListElement(std::list<T> &dataList, size_t elementIndex)
{
	auto it = dataList.begin();
	advance(it, elementIndex);
	return *it;
}

template<typename T>
T const &GetListElement(std::list<T> const &dataList, size_t elementIndex)
{
	auto it = dataList.begin();
	advance(it, elementIndex);
	return *it;
}

template<typename T>
T const *GetListElementConstPtr(std::list<T> const &dataList, size_t elementIndex)
{
	return &GetListElement<T>(dataList, elementIndex);
}

template<typename T>
boost::optional<T*> DeleteListElement(std::list<T> &dataList, size_t elementToDeleteIndex)
{
	T* pElement = &GetListElement<T>(dataList, elementToDeleteIndex);
	
	auto it = dataList.begin();
	advance(it, elementToDeleteIndex);
	dataList.erase(it);

	return pElement;
}

template <typename T>
void PrintList(std::ostream &ost, std::list<T> const &listToPrint)
{
	size_t i = 0;
	for (auto &element : listToPrint)
	{
		ost << ++i << ". " << element.GetName() << endl;
	}
}

template <typename RefType>
void PrintReferenceList(std::ostream &ost, std::list<RefType> const &listToPrint)
{
	size_t i = 0;
	for (auto &element : listToPrint)
	{
		ost << ++i << ". " << element.get().GetName() << endl;
	}
}

template <typename T>
boost::optional<T> ReadFromLine(std::string const &line)
{
	T result;
	std::istringstream lineStream(line);
	if (lineStream >> result)
	{
		return result;
	}
	return boost::none;
}

template <typename T>
T ReadFromStream(std::ostream &ost, std::istream &ist, std::string const &prompt)
{
	boost::optional<T> result;
	do
	{
		result = ReadFromLine<T>(ReadNonEmptyString(ost, ist, prompt));
	} while (!result);

	return *result;
}

template <typename T>
boost::optional<T> ReadFromStreamWithRestrictions(std::ostream &ost, std::istream &ist, T min, T max, std::string const &mainPrompt, std::string const &errorPrompt)
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
				return boost::none;
			}
		}
		else
		{
			return result;
		}
	}
}

template <typename T>
T ReadFromStreamWithRestrictionsUntilResultIsGiven(std::ostream &ost, std::istream &ist, T min, T max, std::string const &mainPrompt, std::string const &errorPrompt)
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


template <typename T>
void SetValueWithRestrictions(std::ostream &ost, std::istream &ist, 
	T &value, T minValue, T maxValue,
	std::string const &mainPrompt, std::string const &errorPrompt)
{
	if (auto result = ReadFromStreamWithRestrictions<unsigned>(ost, ist,
		minValue, maxValue, mainPrompt, errorPrompt))
	{
		value = *result;
	}
}

