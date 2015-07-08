// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MSG_USAGE                    "Usage: replace.exe <input file> <output file> [<search string>] [<replace string>]\n"
#define MSG_DESCRIPTION              "Program replaces all entries of a substring in a text file by another substring\n" MSG_USAGE
#define MSG_ERR_NOT_ENOUGH_ARGUMENTS "ERROR: not enough arguments\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGUMENTS   "ERROR: too many arguments\n" MSG_USAGE
#define MSG_ERR_NO_INPUT             "ERROR: can't open input file (not enough rights or file doesn't exists)\n"
#define MSG_ERR_NO_OUTPUT            "ERROR: can't open output file\n"
#define MSG_ERR_BIG_STRING           "can't work with strings of such big size"


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

//return 0 if str1 == str2
//return 1 if str1 != str2
int StrCompare(char *pStr1, char *pStr2)
{
	int i = 0;
	while ((pStr1[i] != '\0') && (pStr2[i] != '\0'))
	{
		if (pStr1[i] != pStr2[i])
		{
			return 1;
		}
		i++;
	}
	if (pStr1[i] != pStr2[i]) // len1 != len2
	{
		return 1;
	}
	return 0;
}

//return lenght of string or -1 if the length is too big to store it in int
signed int StrLen(char* str)
{
	int i = 0;
	while (str[i] != 0)
	{
		if (i++ == UINT_MAX)
		{
			return -1;
		}
	}
	return i;
}

bool ByteReplace(FILE *pInput, char *const pSearchStr, char *const pReplaceStr, FILE *const pOutput)
{
	signed int buffSize = StrLen(pSearchStr) + 1;
	if (buffSize == 0)
	{
		//error
		return true;
	}
	if (buffSize == 1)
	{
		//just copy without replace
		buffSize = COPY_BUFFER_LENGTH;
	}
	char *pStrBuff = (char*)malloc(buffSize);;
	pStrBuff[0] = 0;

	FillBuffer(pInput, pStrBuff, buffSize);
	while (StrLen(pStrBuff) == (buffSize - 1))
	{
		if (StrCompare(pStrBuff, pSearchStr) == 0)
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
	return false;
}

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION);
		exit(0);
	}
	if (argc < 3)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGUMENTS);
		exit(1);
	}
	if (argc > 5)
	{
		printf(MSG_ERR_TOO_MANY_ARGUMENTS);
		exit(1);
	}
}

FILE *OpenFile(char *pFileName, char *pMode, char *pErrMsg)
{
	FILE *pFile = fopen(pFileName, pMode);
	if (!pFile)
	{
		printf(pErrMsg);
		exit(1);
	}

	return pFile;
}

void CloseFile(FILE *pFile)
{
	if (pFile)
		fclose(pFile);
}

int main(int argc, char* argv[])
{
	CheckArgc(argc);

	char *pInputFileName = argv[1];
	char *pOutputFileName = argv[2];
	char *pSearchStr = (argc < 4) ? "" : argv[3];
	char *pReplaceStr = (argc < 5) ? "" : argv[4];

	//открытие файлов	
	FILE *pInputFile = OpenFile(pInputFileName, "rb", MSG_ERR_NO_INPUT);
	FILE *pOutputFile = OpenFile(pOutputFileName, "wb", MSG_ERR_NO_OUTPUT);

	//замена строки
	bool err = ByteReplace(pInputFile, pSearchStr, pReplaceStr, pOutputFile);
	if (err)
	{
		printf(MSG_ERR_BIG_STRING);
		return 1;
	}

	//закрытие файлов
	CloseFile(pInputFile);
	CloseFile(pOutputFile);

	//сообщение о завершении работы программы
	printf("File %s created from file %s\n", pOutputFileName, pInputFileName);

	return 0;
}