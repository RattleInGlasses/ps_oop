// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

const std::string MSG_USAGE =                     "USAGE: crypt <encrypt | decrypt> <input file> <output file> <key>\n";
const std::string MSG_KEY_DESCRIPTION =           "The key must be an integer number no less than 0 and no more than 255.\n";
const std::string MSG_NO_ARGS =                   "The program encrypts or decrypts given file using given key.\n" + MSG_KEY_DESCRIPTION + MSG_USAGE;
const std::string MSG_ERR_NOT_ENOUGH_ARGS =       "The program needs at least 4 arguments.\n" + MSG_USAGE;
const std::string MSG_ERR_TOO_MANY_ARGS =         "The program needs only 4 arguments.\n" + MSG_USAGE;
const std::string MSG_ERR_CANT_OPEN_INPUT_FILE =  "Error opening input file.\nMake sure you have enough rights and the file really exists.\n";
const std::string MSG_ERR_CANT_OPEN_OUTPUT_FILE = "Error opening output file.\nMake sure you have enough rights.\n";
const std::string MSG_ERR_WRONG_ACTION_ARGUMENT = "The first argument must be \"encrypt\" or \"decrypt\"\n";
const std::string MSG_ERR_KEY_NOT_INTEGER =       "The key needs to be an integer number\n";
const std::string MSG_ERR_KEY_LESS_THAN_0 =       "The key must be no less than 0\n";
const std::string MSG_ERR_KEY_MORE_THAN_255 =     "The key must be no more than 255\n";
const std::string MSG_CRYPT_DONE =                "The file successfully crypted\n";

const int ENCRYPT_TABLE[] = { 5, 6, 0, 1, 2, 7, 3, 4 };
const int DECRYPT_TABLE[] = { 2, 3, 4, 6, 7, 0, 1, 5 };

typedef std::function<uint8_t(uint8_t byteToCrypt, uint8_t key)> CryptByteFunc;

enum ErrReadByte
{
	BYTE_OK,
	BYTE_NOT_INTEGER,
	BYTE_LESS_THAN_0,
	BYTE_MORE_THAN_255
};

// main functions

void SetBit(uint8_t &dest, uint8_t pos, uint8_t bit)
{
	dest &= ~(1 << pos);  // set bit in the position to 0
	bit <<= pos;
	dest |= bit;
}

unsigned char GetBit(uint8_t byte, uint8_t pos)
{
	byte >>= pos;
	return byte & 1;
}

uint8_t ShuffleByte(uint8_t byteToShuffle, int const shuffleTable[])
{
	uint8_t result;
	for (int i = 0; i < 8; i++)
	{
		SetBit(result, shuffleTable[i], GetBit(byteToShuffle, i));
	}
	return result;
}

uint8_t EncryptByte(uint8_t byteToCrypt, uint8_t key)
{
	byteToCrypt ^= key;
	return ShuffleByte(byteToCrypt, ENCRYPT_TABLE);
}

uint8_t DecryptByte(uint8_t byteToCrypt, uint8_t key)
{
	uint8_t result = ShuffleByte(byteToCrypt, DECRYPT_TABLE);
	return result ^ key;
}

void CryptFile(FILE *pInFile, FILE *pOutFile, uint8_t key, CryptByteFunc fCryptByte)
{
	int inputByte = fgetc(pInFile);
	uint8_t cryptedByte;
	while (inputByte != EOF)
	{
		cryptedByte = fCryptByte(inputByte, key);
		fputc(cryptedByte, pOutFile);
		inputByte = fgetc(pInFile);
	}
}

bool OpenFile(char const *pFileName, char const *pMode, char const *pErrMsg, FILE *&pFile)
{
	pFile = fopen(pFileName, pMode);
	if (!pFile)
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

bool PerformAction(char *pInFileName, char *pOutFileName, uint8_t key, CryptByteFunc fCryptByte)
{
	FILE *pInFile;
	FILE *pOutFile;
	if ((OpenFile(pInFileName, "rb", MSG_ERR_CANT_OPEN_INPUT_FILE.c_str(), pInFile))
		&& (OpenFile(pOutFileName, "wb", MSG_ERR_CANT_OPEN_OUTPUT_FILE.c_str(), pOutFile)))
	{
		CryptFile(pInFile, pOutFile, key, fCryptByte);
	}
	else
	{
		CloseFile(pInFile);
		return false;
	}

	CloseFile(pInFile);
	CloseFile(pOutFile);
	
	return true;
}

// convert args to variables funcitons

bool StrHasSignificantChars(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ') && ((str[i] != '\t')))
		{
			return true;
		}
		i++;
	}

	return false;
}

ErrReadByte StrToByte(char *const pStr, uint8_t &byte)
{
	char* pEndP;
	int number = strtol(pStr, &pEndP, 10);

	if ((StrHasSignificantChars(pEndP)) || (!StrHasSignificantChars(pStr)))
	{
		return BYTE_NOT_INTEGER;
	}
	if (number < 0)
	{
		return BYTE_LESS_THAN_0;
	}
	if (number > 255)
	{
		return BYTE_MORE_THAN_255;
	}

	byte = (unsigned char)number;

	return BYTE_OK;
}

boost::optional<uint8_t> GetKey(char *pKeyStr)
{
	uint8_t key;
	switch (StrToByte(pKeyStr, key))
	{
		case BYTE_NOT_INTEGER:
			printf(MSG_ERR_KEY_NOT_INTEGER.c_str());
			return boost::none;
			break;
		case BYTE_LESS_THAN_0:
			printf(MSG_ERR_KEY_LESS_THAN_0.c_str());
			return boost::none;
			break;
		case BYTE_MORE_THAN_255:
			printf(MSG_ERR_KEY_MORE_THAN_255.c_str());
			return boost::none;
			break;
	}
	return key;
}

boost::optional<CryptByteFunc> GetCryptByteFunction(char *const pTaskStr)
{
	if (strcmp(pTaskStr, "encrypt") == 0)
	{
		return EncryptByte;
	}
	else if (strcmp(pTaskStr, "decrypt") == 0)
	{
		return DecryptByte;
	}

	return boost::none;
}

// check arguments function

bool CheckArgumentsCount(int argc)
{
	if (argc < 2)
	{
		printf(MSG_NO_ARGS.c_str());
		return false;
	}
	if (argc < 5)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGS.c_str());
		return false;
	}
	if (argc > 5)
	{
		printf(MSG_ERR_TOO_MANY_ARGS.c_str());
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!CheckArgumentsCount(argc))
	{
		return 1;
	}

	if (boost::optional<CryptByteFunc> fCryptByte = GetCryptByteFunction(argv[1]))
	{
		if (boost::optional<uint8_t> key = GetKey(argv[4]))
		{
			if (PerformAction(argv[2], argv[3], *key, *fCryptByte))
			{
				printf(MSG_CRYPT_DONE.c_str());
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		printf(MSG_ERR_WRONG_ACTION_ARGUMENT.c_str());
		return 1;
	}

	return 0;
}

