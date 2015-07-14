#include "stdafx.h"
#include "RemoveExtraSpaces.h"

#define USER_COMMAND_WORK_END     "..."
#define USER_COMMAND_DO_NOT_SAVE  ""
#define USER_COMMAND_MARK         "> "
#define UNALLOWED_SYMBOLS         "[]"

#define MSG_COMMAND_PROMPT        "Enter word to translate or \"...\" for exit\n"
#define MSG_SAVE_PROMPT           "To save changes in dictionary file enter Y or y\n";
#define MSG_WILL_NOT_SAVE         "Changes will not be saved\n"
#define MSG_ERR_UNALLOWED_SYMBOLS "The word must not contain symbol \"[\" or \"]\"\n"


using namespace std;

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
	string unallowedSymbols = UNALLOWED_SYMBOLS;
	for (int i = 0; i < unallowedSymbols.length(); i++)
	{
		if (str.find(unallowedSymbols[i]) != string::npos)
		{
			return true;
		}
	}
	return false;
}

string GetCommand(string const &userRequest)
{
	string command = RemoveExtraSpaces(userRequest);
	return command;
}

void AddNewWord(string const &word, map<string, string> &vocabulary, bool &newWordAdded)
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
		newWordAdded = true;
	}
	else
	{
		cout << "The word \"" << word << "\" hasn't been added\n";
		newWordAdded = false;
	}
}

bool WordExists(string const &word, map<string, string> const &vocabulary)
{
	return (vocabulary.find(word) != vocabulary.end());
}

void UserDialogCicle(map<string, string> &vocabulary, bool &saveChanges)
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
				bool newWordAdded = false;
				AddNewWord(userCommand, vocabulary, newWordAdded);
				if (!vocabularyChanged)
				{
					vocabularyChanged = newWordAdded;
				}
			}
		}
	}

	saveChanges = false;
	if (vocabularyChanged)
	{
		saveChanges = AskAboutSaving();
	}
}
