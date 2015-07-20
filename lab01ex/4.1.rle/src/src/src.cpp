// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

const std::string  MSG_USAGE =                         "USAGE: rle pack | unpack <input file> <output file>\n";
const std::string  MSG_NO_ARGS =                       "The program packs file into rle archive or unpacks rle archive.\n" + MSG_USAGE;
const std::string  MSG_ERR_NOT_ENOUGH_ARGS =           "The program needs at least 3 arguments.\n" + MSG_USAGE;
const std::string  MSG_ERR_TOO_MANY_ARGS =             "The program needs only 3 arguments.\n" + MSG_USAGE;
const std::string  MSG_ERR_WRONG_ARG =                 "The second argument must be \"pack\" or \"unpack\"\n";
const std::string  MSG_ERR_INPUT_FILE_OPENING_ERROR =  "Error opening input file.\nMake sure you have enough rights and the file exists.\n";
const std::string  MSG_ERR_OUTPUT_FILE_OPENING_ERROR = "Error opening output file.\nMake sure you have enough rights.\n";
const std::string  MSG_ERR_WRONG_RLE_ODD_LENGTH =      "The given file is not a valid rle archive (odd length)\n";
const std::string  MSG_ERR_WRONG_RLE_ZERO_COUNT =      "The given file is not a valid rle archive (zero count)\n";
const std::string  MSG_PACK_GOOD_END =                 "The file successfully packed";
const std::string  MSG_UNPACK_GOOD_END =               "The file successfully unpacked";

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

struct RLEChunk
{
	uint8_t counter;
	char character;
};

boost::optional<RLEChunk> ReadChunk(FILE *pPackedFile, ProgramError &err)
{
	err = ERR_OK;
	int count = fgetc(pPackedFile);
	int ch = fgetc(pPackedFile);
	if (count == 0)
	{
		err = ERR_ZERO_COUNT;
		return boost::none;
	}
	if ((ch == EOF) && (count != EOF))
	{
		err = ERR_COUNT_WITHOUT_DATA;
		return boost::none;
	}

	if (ch != EOF)
	{
		RLEChunk chunk = { count, ch };
		return chunk;
	}
	return boost::none;
}

void UnpackChunk(FILE *pUnpackedFile, RLEChunk chunk)
{
	for (int i = 0; i < chunk.counter; i++)
	{
		fputc(chunk.character, pUnpackedFile);
	}
}

ProgramError Unpack(FILE *pPackedFile, FILE *pUnpackedFile)
{
	ProgramError err = ERR_OK;
	while (auto chunk = ReadChunk(pPackedFile, err))
	{
		UnpackChunk(pUnpackedFile, *chunk);
	}

	return err;
}

boost::optional<RLEChunk> PackChunk(FILE *pInFile)
{
	int count = 0;
	int curCh, nextCh;
	nextCh = fgetc(pInFile);
	while (nextCh != EOF)
	{
		curCh = nextCh;
		nextCh = fgetc(pInFile);
		count++;

		if ((curCh != nextCh) || (count == 255))
		{
			if (nextCh != EOF)
			{
				ungetc(nextCh, pInFile);
			}
			break;
		}
	}

	if (count > 0)
	{
		RLEChunk chunk = { count, curCh };
		return chunk;
	}
	return boost::none;
}

void WriteChunk(FILE *pPackedFile, RLEChunk const &chunk)
{
	fputc(chunk.counter, pPackedFile);
	fputc(chunk.character, pPackedFile);
}

void Pack(FILE *pInFile, FILE *pPackedFile)
{
	while (auto chunk = PackChunk(pInFile))
	{
		WriteChunk(pPackedFile, *chunk);
	}
}

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_NO_ARGS.c_str());
		return false;
	}
	if (argc < 4)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGS.c_str());
		return false;
	}
	if (argc > 4)
	{
		printf(MSG_ERR_TOO_MANY_ARGS.c_str());
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
		fclose(pInFile);
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
			printf(MSG_ERR_INPUT_FILE_OPENING_ERROR.c_str());
			return false;
			break;
		case ERR_ERROR_OPENING_OUPUT_FILE:
			printf(MSG_ERR_OUTPUT_FILE_OPENING_ERROR.c_str());
			return false;
			break;
		case ERR_ZERO_COUNT:
			printf(MSG_ERR_WRONG_RLE_ZERO_COUNT.c_str());
			return false;
			break;
		case ERR_COUNT_WITHOUT_DATA:
			printf(MSG_ERR_WRONG_RLE_ODD_LENGTH.c_str());
			return false;
			break;
	}
	return true;
}

void PrintGoodEndMsg(ProgramMode mode)
{
	if (mode == PACK)
	{
		printf(MSG_PACK_GOOD_END.c_str());
	}
	if (mode == UNPACK)
	{
		printf(MSG_UNPACK_GOOD_END.c_str());
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
		printf(MSG_ERR_WRONG_ARG.c_str());
		return 1;
	}

	return 0;
}

