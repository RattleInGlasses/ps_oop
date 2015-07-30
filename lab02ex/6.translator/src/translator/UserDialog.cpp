#include "stdafx.h"
#include "RemoveExtraSpaces.h"

using namespace std;

string const USER_COMMAND_WORK_END =     "...";
string const USER_COMMAND_DO_NOT_SAVE =  "";
string const USER_COMMAND_MARK =         "> ";
string const UNALLOWED_SYMBOLS =         "[]";

string const MSG_COMMAND_PROMPT =        "Enter word to translate or \"...\" for exit\n";
string const MSG_SAVE_PROMPT =           "To save changes in dictionary file enter Y or y\n";
string const MSG_WILL_NOT_SAVE =         "Changes will not be saved\n";
string const MSG_ERR_UNALLOWED_SYMBOLS = "The word must not contain symbol \"[\" or \"]\"\n";

bool AskAboutSaving()
{
	cout << MSG_SAVE_PROMPT;
	cout << USER_COMMAND_MARK;
	char ch;
	cin.get(ch);
	if ((ch == 'Y') || (ch == 'y'))
	{
		return true;
	}
	cout << MSG_WILL_NOT_SAVE;
	return false;
}

bool HasForbiddenSymbols(string str)
{
	for (size_t i = 0; i < UNALLOWED_SYMBOLS.length(); i++)
	{
		if (str.find(UNALLOWED_SYMBOLS[i]) != string::npos)
		{
			return true;
		}
	}
	return false;
}

string ToLowerCase(string const &str)
{
	string result;
	locale rusLoc(".866");
	for (string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		result += tolower(*it, rusLoc);
	}
	return result;
}

string GetCommand(string const &userRequest)
{
	return ToLowerCase(RemoveExtraSpaces(userRequest));
}

// return true if the word was added
// return false if the word was ignored
bool AddNewWord(string const &word, map<string, string> &vocabulary)
{
	cout << "There is no word \"" << word << "\". Enter translation to save or empty string to skip\n";
	cout << USER_COMMAND_MARK;
	string userRequest;
	getline(cin, userRequest);
	string userCommand = GetCommand(userRequest);
	if (userCommand != USER_COMMAND_DO_NOT_SAVE)
	{
		vocabulary[word] = userCommand;
		cout << "The word \"" << word << "\" has been added to the vocabulary with a translation \"" << userCommand << "\"\n";
		return true;
	}
	else
	{
		cout << "The word \"" << word << "\" hasn't been added\n";
		return false;
	}
}

bool WordExists(string const &word, map<string, string> const &vocabulary)
{
	return (vocabulary.find(word) != vocabulary.end());
}

// returns true if vocabulary has been changed and user desided to save it
bool UserDialogLoop(map<string, string> &vocabulary)
{
	bool vocabularyChanged = false;
	bool exitCommand = false;
	string userRequest; // line user sends to program
	string userCommand; // extracted command from user-sended line
	while (!exitCommand)
	{
		cout << MSG_COMMAND_PROMPT;
		cout << USER_COMMAND_MARK;
		getline(cin, userRequest);
		cin.clear();                             // restore after "keyboard-EOF"
		userCommand = GetCommand(userRequest);
		if (userCommand == USER_COMMAND_WORK_END)
		{
			exitCommand = true;
		}
		else
		{
			if (HasForbiddenSymbols(userCommand))
			{
				cout << MSG_ERR_UNALLOWED_SYMBOLS;
			}			
			else if (WordExists(userCommand, vocabulary))
			{
				cout << vocabulary[userCommand] << endl;
			}
			else if (userCommand != "")
			{
				bool newWordAdded =	AddNewWord(userCommand, vocabulary);
				if (!vocabularyChanged)
				{
					vocabularyChanged = newWordAdded;
				}
			}
		}
	}

	if (vocabularyChanged)
	{
		return AskAboutSaving();
	}
	return false;
}
