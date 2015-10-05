#include "stdafx.h"
#include "CliMenus.h"

using namespace std;
using namespace boost;


bool IsIndexInRange(optional<size_t> const &index, size_t objCount)
{
	return (*index - 1) <= (objCount - 1);
}


void PredefinedChoiseAndReturnMenu(std::ostream &ost, std::istream &ist, std::string const &menuName,
	std::map<std::string, std::function<void()>> const &menuFunctions)
{
	for (;;)
	{
		PrintMenuMessage(ost, menuName, PrintNullMessageFunction());
		std::string command = ReadUserCommand(ist);

		if (menuFunctions.find(command) != menuFunctions.end())
		{
			menuFunctions.at(command)();
		}
		else if (command == "r")
		{
			return;
		}
	}
}


void ListChoiseAndReturnWithoutProcessFunctionMenu(ostream &ost, istream &ist, function<void()> const &fShowData)
{
	for (;;)
	{
		PrintMenuMessage(ost, "ShowDataList", fShowData);

		string command = ReadUserCommand(ist);
		if (command == "r")
		{
			return;
		}
	}
}

