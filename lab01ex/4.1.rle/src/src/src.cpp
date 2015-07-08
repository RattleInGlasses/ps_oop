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
	UNPACK
};

enum ProgramError
{
	ERR_OK,
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

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_NO_ARGS);
		exit(0);
	}
	if (argc < 4)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGS);
		exit(1);
	}
	if (argc > 4)
	{
		printf(MSG_ERR_TOO_MANY_ARGS);
		exit(1);
	}
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
		printf(MSG_ERR_WRONG_ARG);
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

ProgramError DoAction(ProgramMode mode, FILE *pInFile, FILE *pOutFile)
{
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

	return err;
}

void CheckProgramError(ProgramError err)
{
	switch (err)
	{
		case ERR_ZERO_COUNT:
			printf(MSG_ERR_WRONG_RLE_ZERO_COUNT);
			break;
		case ERR_COUNT_WITHOUT_DATA:
			printf(MSG_ERR_WRONG_RLE_ODD_LENGTH);
			break;
	}
}

void CloseFiles(FILE *pInFile, FILE *pOutFile, char* outFileName, ProgramError err)
{
	if (pInFile)
	{
		fclose(pInFile);
	}
	if (pOutFile)
	{
		fclose(pOutFile);
	}
	if (err != ERR_OK)
	{
		remove(outFileName);
		exit(1);
	}
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
	CheckArgc(argc);
	ProgramMode mode = GetProgramMode(argv[1]);
	FILE *pInFile = OpenFile(argv[2], "rb", MSG_ERR_INPUT_FILE_OPENING_ERROR);
	FILE *pOutFile = OpenFile(argv[3], "wb", MSG_ERR_OUTPUT_FILE_OPENING_ERROR);
	ProgramError actionErr = DoAction(mode, pInFile, pOutFile);
	CheckProgramError(actionErr);
	CloseFiles(pInFile, pOutFile, argv[3], actionErr);
	PrintGoodEndMsg(mode);

	return 0;
}

