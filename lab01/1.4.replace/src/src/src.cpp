// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MSG_USAGE                    "Usage: replace.exe <input file> <output file> [<search string>] [<replace string>]\n"
#define MSG_DESCRIPTION              "Program replaces all entries of a substring in a text file by another substring\n" MSG_USAGE
#define MSG_ERR_NOT_ENOUGH_ARGUMENTS "ERROR: not enough arguments\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGUMENTS   "ERROR: too many arguments\n" MSG_USAGE
#define MSG_ERR_NO_INPUT             "ERROR: can't open input file (not enough rights or file doesn't exists)\n"
#define MSG_ERR_NO_OUTPUT            "ERROR: can't open output file\n"
#define MSG_GOOD_EXIT                "File %s created from file %s\n"

#define COPY_BUFFER_LENGTH 100;

// writes file content into buffer-string
void FillBuffer(FILE *pInput, char *pBuff, int buffSize)
{
	pBuff[0] = 0;
	int ch;
	for (int i = 0; i < (buffSize - 1); i++)
	{
		ch = getc(pInput);
		if (ch == EOF)
		{
			return;
		}
		pBuff[i] = ch;
		pBuff[i + 1] = 0;
	}
}

// Moves file window by 1 char
// in case of EOF shrinks the window
void MoveBuffer(FILE *pInput, char *pBuff, int buffSize)
{
	// move chars left by 1
	for (int i = 0; i < buffSize - 1; i++)
	{
		pBuff[i] = pBuff[i + 1];
	}
	// add next char from input
	int ch = getc(pInput);
	if (ch != EOF)
	{
		pBuff[buffSize - 2] = ch;
		pBuff[buffSize - 1] = '\0';
	}
}

void ByteReplace(FILE *pInput, char *const pSearchStr, char *const pReplaceStr, FILE *const pOutput)
{
	size_t buffSize = strlen(pSearchStr) + 1;
	if (buffSize == 1)
	{
		//just copy without replace
		buffSize = COPY_BUFFER_LENGTH;
	}
	char *pStrBuff = (char*)malloc(buffSize);;
	pStrBuff[0] = 0;

	FillBuffer(pInput, pStrBuff, buffSize);
	while (strlen(pStrBuff) == (buffSize - 1))
	{
		if (strcmp(pStrBuff, pSearchStr) == 0)
		{
			fputs(pReplaceStr, pOutput);
			FillBuffer(pInput, pStrBuff, buffSize);
		}
		else // strBuff != searchStr
		{
			fputc(pStrBuff[0], pOutput);
			MoveBuffer(pInput, pStrBuff, buffSize);
		}
	}
	fputs(pStrBuff, pOutput);

	free(pStrBuff);
}

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION);
		return false;
	}
	if (argc < 3)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGUMENTS);
		return false;
	}
	if (argc > 5)
	{
		printf(MSG_ERR_TOO_MANY_ARGUMENTS);
		return false;
	}
	return true;
}

bool OpenFile(char *pFileName, char *pMode, char *pErrMsg, FILE **ppFile)
{
	*ppFile = fopen(pFileName, pMode);
	if (!*ppFile)
	{
		printf(pErrMsg);
		return false;
	}
	return true;
}

void CloseFile(FILE *pFile)
{
	if (pFile)
	{
		fclose(pFile);
	}
}

int main(int argc, char* argv[])
{
	if (!CheckArgc(argc))
	{
		return 1;
	}
	
	FILE *pInputFile;
	FILE *pOutputFile;
	if (!OpenFile(argv[1], "rb", MSG_ERR_NO_INPUT, &pInputFile)
		|| (!OpenFile(argv[2], "wb", MSG_ERR_NO_OUTPUT, &pOutputFile)))
	{
		return 1;
	}

	char *pSearchStr = (argc < 4) ? "" : argv[3];
	char *pReplaceStr = (argc < 5) ? "" : argv[4];
	ByteReplace(pInputFile, pSearchStr, pReplaceStr, pOutputFile);

	CloseFile(pInputFile);
	CloseFile(pOutputFile);
	
	printf(MSG_GOOD_EXIT, argv[2], argv[1]);

	return 0;
}