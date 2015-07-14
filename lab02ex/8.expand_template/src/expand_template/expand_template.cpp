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

void StreamExpandTemplate(istream &inStream, ostream &outStream, map<string, string> params)
{
	string line;
	while (getline(inStream, line))
	{
		outStream << ExpandTemplate(line, params);
		inStream.unget();
		if (inStream.get() == '\n')
		{
			outStream << endl;
		}
	}
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

fstream OpenFile(char *fileName, ios_base::openmode mode, char *errMsg)
{
	fstream fileStream(fileName, mode);
	if (!fileStream.is_open())
	{
		cout << errMsg;
		exit(1);
	}
	return fileStream;
}

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		exit(0);
	}
	if (argc < 3)
	{
		cout << MSG_ERR_NOT_ENOUGH_ARGUMENTS;
		exit(1);
	}
	if ((argc > 3) && ((argc % 2) != 1))
	{
		cout << MSG_ERR_PARAM_WITHOUT_VALUE;
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	//TestExpandTemplate();
	
	CheckArgc(argc);
	istream &inFile  = OpenFile(argv[1], istream::in, MSG_ERR_NO_INPUT);
	ostream &outFile = OpenFile(argv[2], ostream::out, MSG_ERR_NO_OUTPUT);
	map<string, string> params = GetParams(argc, argv);
	
	StreamExpandTemplate(inFile, outFile, params);

	PrintEndMessage(argv[1], argv[2]);

	return 0;
}

