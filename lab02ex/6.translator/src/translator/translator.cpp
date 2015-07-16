// translator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SaverLoader.h"
#include "UserDialog.h"

#define MSG_USAGE              "USAGE: translator.exe <vocabulary file>\n"
#define MSG_DESCRIPTION        "The program is a translator. To use it you need a vocabulary.\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGS  "The program needs only one argument\n" MSG_USAGE

using namespace std;

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		return false;
	}
	if (argc > 2)
	{
		cout << MSG_ERR_TOO_MANY_ARGS;
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
	
	map<string, string> vocabulary;
	if (GetVocabularyMap(argv[1], vocabulary))
	{
		bool saveVocabularyRequest;
		UserDialogCicle(vocabulary, saveVocabularyRequest);
		if (saveVocabularyRequest)
		{
			if (!SaveVocabulary(vocabulary, argv[1]))
			{
				return 1;
			}
		}
	}
	else
	{
		return 1;
	}

	cout << "The program is closing\n";

	return 0;
}

