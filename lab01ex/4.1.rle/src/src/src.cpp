// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MSG_USAGE                         "USAGE: rle pack | unpack <input file> <output file>\n"
#define MSG_NO_ARGS                       "The program packs file into rle archive or unpacks rle archive.\n" MSG_USAGE
#define MSG_ERR_NOT_ENOUGH_ARGS           "The program needs at least 3 arguments.\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGS             "The program needs only 3 arguments.\n" MSG_USAGE
#define MSG_ERR_WRONG_ARG                 "The second argument must be \"pack\" or \"unpack\"\n"
#define MSG_ERR_INPUT_FILE_OPENING_ERROR  "Error opening input file.\nMake sure you have enough rights and the file exists.\n"
#define MSG_ERR_OUTPUT_FILE_OPENING_ERROR "Error opening output file.\nMake sure you have enough rights.\n"
#define MSG_ERR_WRONG_RLE_ODD_LENGTH      "The given file is not a valid rle archive (odd length)\n"
#define MSG_ERR_WRONG_RLE_ZERO_COUNT      "The given file is not a valid rle archive (zero count)\n"
#define MSG_PACK_GOOD_END                 "The file successfully packed"
#define MSG_UNPACK_GOOD_END               "The file successfully unpacked"

enum ProgramMode
{
	PACK,
	UNPACK,
	UNDEFINED
};

enum ProgramError
{
	ERR_OK,
	ERR_ERROR_OPENING_INPUT_FILE,
	ERR_ERROR_OPENING_OUPUT_FILE,
	ERR_ZERO_COUNT,
	ERR_COUNT_WITHOUT_DATA
};

ProgramError Unpack(FILE *pPackedFile, FILE *pUnpackedFile)
{
	int count, curByte;
	do
	{
		count = fgetc(pPackedFile);
		curByte = fgetc(pPackedFile);
		if (count == 0)
		{
			return ERR_ZERO_COUNT;
		}
		if ((curByte == EOF) && (count != EOF))
		{
			return ERR_COUNT_WITHOUT_DATA;
		}

		for (int i = 0; i < count; i++)
		{
			fputc(curByte, pUnpackedFile);
		}
	} while (curByte != EOF);

	return ERR_OK;
}

void Pack(FILE *pInFile, FILE *pPackedFile)
{
	int count = 0;
	bool nextStreak = true;
	int curByte, nextByte;
	nextByte = fgetc(pInFile);
	do
	{
		curByte = nextByte;
		nextByte = fgetc(pInFile);
		count++;

		if ((curByte != nextByte) || (count == 255))
		{
			fputc(count, pPackedFile);
			fputc(curByte, pPackedFile);
			count = 0;
		}
	} while (nextByte != EOF);
}

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_NO_ARGS);
		return false;
	}
	if (argc < 4)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGS);
		return false;
	}
	if (argc > 4)
	{
		printf(MSG_ERR_TOO_MANY_ARGS);
		return false;
	}
	return true;
}

ProgramMode GetProgramMode(char *pModeStr)
{
	if (strcmp(pModeStr, "pack") == 0)
	{
		return PACK;
	}
	else if (strcmp(pModeStr, "unpack") == 0)
	{
		return UNPACK;
	}
	else
	{
		return UNDEFINED;
	}
}

bool OpenFile(char *pFileName, char *pMode, FILE *&pFile)
{
	pFile = fopen(pFileName, pMode);
	if (!pFile)
	{
		return false;
	}
	return true;
}

ProgramError DoAction(ProgramMode mode, char *pInFileName, char *pOutFileName)
{
	FILE *pInFile;
	if (!OpenFile(pInFileName, "rb", pInFile))
	{
		return ERR_ERROR_OPENING_INPUT_FILE;
	}
	FILE *pOutFile;
	if (!OpenFile(pOutFileName, "wb", pOutFile))
	{
		return ERR_ERROR_OPENING_OUPUT_FILE;
	}

	ProgramError err = ERR_OK;
	switch (mode)
	{
		case PACK:
			Pack(pInFile, pOutFile);
			break;
		case UNPACK:
			err = Unpack(pInFile, pOutFile);
			break;
	}

	fclose(pInFile);
	fclose(pOutFile);

	if (err != ERR_OK)
	{
		remove(pOutFileName);
	}
	return err;
}

bool CheckProgramError(ProgramError err)
{
	switch (err)
	{
		case ERR_ERROR_OPENING_INPUT_FILE:
			printf(MSG_ERR_INPUT_FILE_OPENING_ERROR);
			return false;
			break;
		case ERR_ERROR_OPENING_OUPUT_FILE:
			printf(MSG_ERR_OUTPUT_FILE_OPENING_ERROR);
			return false;
			break;
		case ERR_ZERO_COUNT:
			printf(MSG_ERR_WRONG_RLE_ZERO_COUNT);
			return false;
			break;
		case ERR_COUNT_WITHOUT_DATA:
			printf(MSG_ERR_WRONG_RLE_ODD_LENGTH);
			return false;
			break;
	}
	return true;
}

void PrintGoodEndMsg(ProgramMode mode)
{
	if (mode == PACK)
	{
		printf(MSG_PACK_GOOD_END);
	}
	if (mode == UNPACK)
	{
		printf(MSG_UNPACK_GOOD_END);
	}
}

int main(int argc, char* argv[])
{
	if (!CheckArgc(argc))
	{
		return 1;
	}

	ProgramMode mode;
	if ((mode = GetProgramMode(argv[1])) != UNDEFINED)
	{
		if (CheckProgramError(DoAction(mode, argv[2], argv[3])))
		{
			PrintGoodEndMsg(mode);
		}
		else
		{
			return 1;
		}
	}
	else
	{
		printf(MSG_ERR_WRONG_ARG);
		return 1;
	}

	return 0;
}

