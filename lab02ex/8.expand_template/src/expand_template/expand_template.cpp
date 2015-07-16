// expand_template.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "template.h"

#define MSG_USAGE                      "USAGE: expand_template.exe <input file> <output file> [<param> <value> [<param> <value> ...]]\n"
#define MSG_DESCRIPTION_1              "The program replaces substrings of a file by other strings\n"
#define MSG_DESCRIPTION_2              "(<param> is beeing replaced by <value>) and stores the result in specified file\n"
#define MSG_DESCRIPTION                MSG_DESCRIPTION_1 MSG_DESCRIPTION_2 MSG_USAGE
#define MSG_ERR_NOT_ENOUGH_ARGUMENTS   "The program needs at least 2 argumnets. You need to specify output file.\n" MSG_USAGE
#define MSG_ERR_PARAM_WITHOUT_VALUE    "Every param needs an associated value.\n"
#define MSG_ERR_NO_INPUT               "Error opening input file.\nMake sure you have enough rights and the file really exists.\n"
#define MSG_ERR_NO_OUTPUT              "Error opening output file.\nMake sure you have enough rights.\n"

using namespace std;

void PrintEndMessage(char *inFileName, char *outFileName)
{
	cout << "File " << outFileName << " successfully created from file " << inFileName << endl;
}

bool StreamExpandTemplate(char *pInFileName, char *pOutFileName, map<string, string> params)
{
	ifstream inFileStream(pInFileName, ifstream::in);
	if (!inFileStream.is_open())
	{
		cout << MSG_ERR_NO_INPUT;
		return false;
	}
	ofstream outFileStream(pOutFileName, ofstream::out);
	if (!outFileStream.is_open())
	{
		cout << MSG_ERR_NO_OUTPUT;
		return false;
	}		
	
	string line;
	while (getline(inFileStream, line))
	{
		outFileStream << ExpandTemplate(line, params);
		inFileStream.unget();
		if (inFileStream.get() == '\n')
		{
			outFileStream << endl;
		}
	}

	return true;
}

map<string, string> GetParams(int argc, char* argv[])
{
	map<string, string> params;
	for (int i = 3; i < argc; i += 2)
	{
		params[argv[i]] = argv[i + 1];
	}
	return params;
}

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		return false;
	}
	if (argc < 3)
	{
		cout << MSG_ERR_NOT_ENOUGH_ARGUMENTS;
		return false;
	}
	if ((argc > 3) && ((argc % 2) != 1))
	{
		cout << MSG_ERR_PARAM_WITHOUT_VALUE;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	//TestExpandTemplate();
	
	if (!CheckArgc(argc))
	{
		return 1;
	}

	map<string, string> params = GetParams(argc, argv);
	
	if (StreamExpandTemplate(argv[1], argv[2], params))
	{
		PrintEndMessage(argv[1], argv[2]);
	}
	else
	{
		return 1;
	}	

	return 0;
}

