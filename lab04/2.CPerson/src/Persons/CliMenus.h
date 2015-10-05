#pragma once
#include <list>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
#include <xrefwrap>
#include <boost/optional.hpp>
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"
#include "CliFunctions.h"


bool IsIndexInRange(boost::optional<size_t> const &index, size_t objCount);

void PredefinedChoiseAndReturnMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::map<std::string, std::function<void()>> const &menuFunctions);
void ListChoiseAndReturnWithoutProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::function<void()> const &fShowData);

template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<T> &objectsToChoose, F fProcessChoosenElement);
template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<T> const &objectsToChoose, F fProcessChoosenElement);
template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<std::reference_wrapper<T>> const &objectsToChoose, F fProcessChoosenElement);

template <typename ReturnType, typename ObjectType, typename FunctionType>
boost::optional<ReturnType> ListChoiceAndCancelMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<ObjectType> &objectsToChooseFrom, FunctionType fProcessObjectByIndexFunction);
template <typename ReturnType, typename ObjectType, typename FunctionType>
boost::optional<ReturnType> ListChoiceAndCancelMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<ObjectType> const &objectsToChooseFrom, FunctionType fProcessObjectByIndexFunction);

template <typename Organization>
boost::optional<Organization const*> ChooseOrganizationPtrMenu(std::ostream &ost, std::istream &ist,
	std::list<Organization> const &organizations);
template <typename Organization>
Organization const *ChooseOrganizationPtrWithoutCancelMenu(std::ostream &ost, std::istream &ist,
	std::list<Organization> const &organizations, std::string const &prompt);
template <typename T>
boost::optional<T*> DeleteListElementMenu(std::ostream &ost, std::istream &ist,
	std::list<T> &dataList, std::string const &menuName);


// Template implementation

template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<T> &objectsToChoose, F fProcessChoosenElement)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, std::bind(PrintList<T>, ref(ost), objectsToChoose));
		std::string command = ReadUserCommand(ist);

		auto choosenRecord = ReadFromLine<size_t>(command);
		if (choosenRecord && IsIndexInRange(choosenRecord, objectsToChoose.size()))
		{
			fProcessChoosenElement(GetListElement(objectsToChoose, *choosenRecord - 1));
		}
		else if (command == "r")
		{
			return;
		}
	}
}


template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<T> const &objectsToChoose, F fProcessChoosenElement)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, std::bind(PrintList<T>, ref(ost), objectsToChoose));
		std::string command = ReadUserCommand(ist);

		auto choosenRecord = ReadFromLine<size_t>(command);
		if (choosenRecord && IsIndexInRange(choosenRecord, objectsToChoose.size()))
		{
			fProcessChoosenElement(GetListElement(objectsToChoose, *choosenRecord - 1));
		}
		else if (command == "r")
		{
			return;
		}
	}
}


template <typename T, typename F>
void ListChoiseAndReturnWithProcessFunctionMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<std::reference_wrapper<T>> const &objectsToChoose, F fProcessChoosenElement)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, bind(PrintReferenceList<reference_wrapper<T>>, ref(ost), objectsToChoose));
		std::string command = ReadUserCommand(ist);

		auto choosenRecord = ReadFromLine<size_t>(command);
		if (choosenRecord && IsIndexInRange(choosenRecord, objectsToChoose.size()))
		{
			fProcessChoosenElement(GetListElement(objectsToChoose, *choosenRecord - 1));
		}
		else if (command == "r")
		{
			return;
		}
	}
}


template <typename ReturnType, typename ObjectType, typename FunctionType>
boost::optional<ReturnType> ListChoiceAndCancelMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<ObjectType> &objectsToChooseFrom,	FunctionType fProcessObjectByIndexFunction)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, bind(PrintList<ObjectType>, ref(ost), objectsToChooseFrom));

		string command = ReadUserCommand(ist);
		auto choosenObject = ReadFromLine<size_t>(command);
		if ((choosenObject) && IsIndexInRange(choosenObject, objectsToChooseFrom.size()))
		{
			return fProcessObjectByIndexFunction(objectsToChooseFrom, *choosenObject - 1);
		}
		else if (command == "c")
		{
			return boost::none;
		}
	}
}


template <typename ReturnType, typename ObjectType, typename FunctionType>
boost::optional<ReturnType> ListChoiceAndCancelMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<ObjectType> const &objectsToChooseFrom, FunctionType fProcessObjectByIndexFunction)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, bind(PrintList<ObjectType>, ref(ost), objectsToChooseFrom));

		string command = ReadUserCommand(ist);
		auto choosenObject = ReadFromLine<size_t>(command);
		if ((choosenObject) && IsIndexInRange(choosenObject, objectsToChooseFrom.size()))
		{
			return fProcessObjectByIndexFunction(objectsToChooseFrom, *choosenObject - 1);
		}
		else if (command == "c")
		{
			return boost::none;
		}
	}
}


template <typename ReturnType, typename ObjectType, typename FunctionType>
ReturnType ListChoiceWithoutCancelMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::list<ObjectType> const &objectsToChooseFrom,
	FunctionType fProcessObjectByIndexFunction,
	std::string const &prompt = "")
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, bind(PrintList<ObjectType>, ref(ost), objectsToChooseFrom), prompt);

		string command = ReadUserCommand(ist);
		auto choosenObject = ReadFromLine<size_t>(command);
		if ((choosenObject) && IsIndexInRange(choosenObject, objectsToChooseFrom.size()))
		{
			return fProcessObjectByIndexFunction(objectsToChooseFrom, *choosenObject - 1);
		}
	}
}


template<typename Organization>
boost::optional<Organization const*> ChooseOrganizationPtrMenu(std::ostream &ost, std::istream &ist,
	std::list<Organization> const &organizations)
{
	return ListChoiceAndCancelMenu<Organization const *>(ost, ist, "ChooseOrganizationMenu",
		organizations, GetListElementConstPtr<Organization>);
}


template<typename Organization>
Organization const *ChooseOrganizationPtrWithoutCancelMenu(std::ostream &ost, std::istream &ist,
	std::list<Organization> const &organizations, std::string const &prompt)
{
	return ListChoiceWithoutCancelMenu<Organization const *>(ost, ist, "ChooseOrganizationWithPromptMenu", 
		organizations, GetListElementConstPtr<Organization>, prompt);
}


template <typename T>
boost::optional<T*> DeleteListElementMenu(std::ostream &ost, std::istream &ist,
	std::list<T> &dataList, std::string const &menuName)
{
	return ListChoiceAndCancelMenu<T*>(ost, ist, menuName, dataList, DeleteListElement<T>);
}

