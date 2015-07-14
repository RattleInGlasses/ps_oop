// translator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SaverLoader.h"
#include "UserDialog.h"

#define MSG_USAGE              "USAGE: translator.exe <vocabulary file>\n"
#define MSG_DESCRIPTION        "The program is a translator. To use it you need a vocabulary.\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGS  "The program needs only one argument\n" MSG_USAGE

using namespace std;

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		exit(0);
	}
	if (argc > 2)
	{
		cout << MSG_ERR_TOO_MANY_ARGS;
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	CheckArgc(argc);
	
	map<string, string> vocabulary = GetVocabularyMap(argv[1]);

	bool saveVocabularyRequest;
	UserDialogCicle(vocabulary, saveVocabularyRequest);
	if (saveVocabularyRequest)
	{
		SaveVocabulary(vocabulary);
	}
	cout << "The program is closing\n";

	return 0;
}

