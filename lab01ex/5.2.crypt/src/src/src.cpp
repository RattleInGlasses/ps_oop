// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#define	MSG_USAGE                     "USAGE: crypt <encrypt | decrypt> <input file> <output file> <key>\n"
#define MSG_KEY_DESCRIPTION           "The key must be an integer number no less than 0 and no more than 255.\n"
#define MSG_NO_ARGS                   "The program encrypts or decrypts given file using given key.\n" MSG_KEY_DESCRIPTION MSG_USAGE
#define MSG_ERR_NOT_ENOUGH_ARGS       "The program needs at least 4 arguments.\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGS         "The program needs only 4 arguments.\n" MSG_USAGE
#define MSG_ERR_CANT_OPEN_INPUT_FILE  "Error opening input file.\nMake sure you have enough rights and the file really exists.\n"
#define MSG_ERR_CANT_OPEN_OUTPUT_FILE "Error opening output file.\nMake sure you have enough rights.\n"
#define MSG_ERR_WRONG_ACTION_ARGUMENT "The first argument must be \"encrypt\" or \"decrypt\"\n"
#define MSG_ERR_KEY_NOT_INTEGER       "The key needs to be an integer number\n"
#define MSG_ERR_KEY_LESS_THAN_0       "The key must be no less than 0\n"
#define MSG_ERR_KEY_MORE_THAN_255     "The key must be no more than 255\n"
#define MSG_ENCRYPTION_DONE           "The file successfully encrypted\n"
#define MSG_DECRTYPTION_DONE          "The file successfully decrypted\n"

enum Task
{
	ENCRYPT,
	DECRYPT
};

enum ErrReadByte
{
	BYTE_OK,
	BYTE_NOT_INTEGER,
	BYTE_LESS_THAN_0,
	BYTE_MORE_THAN_255
};

// main functions

void PutBit(unsigned char &dest, char pos, unsigned char bit)
{
	bit <<= pos;
	dest += bit;
}

unsigned char GetBit(unsigned char byte, char pos)
{
	byte >>= pos;
	return byte & 1;
}

unsigned char EncryptByte(unsigned char byte, unsigned char key)
{
	byte ^= key;
	unsigned char result = 0;
	PutBit(result, 2, GetBit(byte, 0));
	PutBit(result, 3, GetBit(byte, 1));
	PutBit(result, 4, GetBit(byte, 2));
	PutBit(result, 6, GetBit(byte, 3));
	PutBit(result, 7, GetBit(byte, 4));
	PutBit(result, 0, GetBit(byte, 5));
	PutBit(result, 1, GetBit(byte, 6));
	PutBit(result, 5, GetBit(byte, 7));

	return result;
}

unsigned char DecryptByte(unsigned char byte, unsigned char key)
{
	unsigned char result = 0;
	PutBit(result, 5, GetBit(byte, 0));
	PutBit(result, 6, GetBit(byte, 1));
	PutBit(result, 0, GetBit(byte, 2));
	PutBit(result, 1, GetBit(byte, 3));
	PutBit(result, 2, GetBit(byte, 4));
	PutBit(result, 7, GetBit(byte, 5));
	PutBit(result, 3, GetBit(byte, 6));
	PutBit(result, 4, GetBit(byte, 7));
	result ^= key;

	return result;
}

void EncryptFile(FILE *pInFile, FILE *pEncryptedFile, unsigned char key)
{
	int byte = fgetc(pInFile);
	unsigned char encryptedByte;
	while (byte != EOF)
	{
		encryptedByte = EncryptByte(byte, key);
		fputc(encryptedByte, pEncryptedFile);
		byte = fgetc(pInFile);
	}
}

void DecryptFile(FILE *pEncryptedFile, FILE *pDecryptedFile, unsigned char key)
{
	int encryptedByte = fgetc(pEncryptedFile);
	int decryptedByte;
	while (encryptedByte != EOF)
	{
		decryptedByte = DecryptByte(encryptedByte, key);
		fputc(decryptedByte, pDecryptedFile);
		encryptedByte = fgetc(pEncryptedFile);
	}
}

bool OpenFile(char *pFileName, char *pMode, char *pErrMsg, FILE *&pFile)
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

bool PerformAction(Task task, char *pInFileName, char *pOutFileName, unsigned char key)
{
	FILE *pInFile;
	FILE *pOutFile;
	if ((OpenFile(pInFileName, "rb", MSG_ERR_CANT_OPEN_INPUT_FILE, pInFile))
		&& (OpenFile(pOutFileName, "wb", MSG_ERR_CANT_OPEN_OUTPUT_FILE, pOutFile)))
	{
		if (task == ENCRYPT)
		{
			EncryptFile(pInFile, pOutFile, key);
		}
		else if (task == DECRYPT)
		{
			DecryptFile(pInFile, pOutFile, key);
		}
	}
	else
	{
		return false;
	}
	
	return true;
}

// print end message function

void PrintGoodEndMsg(Task task)
{
	if (task == ENCRYPT)
	{
		printf(MSG_ENCRYPTION_DONE);
	}
	if (task == DECRYPT)
	{
		printf(MSG_DECRTYPTION_DONE);
	}
}

// convert args to variables funcitons

bool IsEmptyStr(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ') && ((str[i] != '\t')))
		{
			return false;
		}
		i++;
	}

	return true;
}

ErrReadByte StrToByte(char *const pStr, unsigned char &byte)
{
	char* pEndP;
	int number = strtol(pStr, &pEndP, 10);

	if ((!IsEmptyStr(pEndP)) || (IsEmptyStr(pStr)))
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

bool GetKey(char *pKeyStr, unsigned char &key)
{
	switch (StrToByte(pKeyStr, key))
	{
		case BYTE_NOT_INTEGER:
			printf(MSG_ERR_KEY_NOT_INTEGER);
			return false;
			break;
		case BYTE_LESS_THAN_0:
			printf(MSG_ERR_KEY_LESS_THAN_0);
			return false;
			break;
		case BYTE_MORE_THAN_255:
			printf(MSG_ERR_KEY_MORE_THAN_255);
			return false;
			break;
	}
	return true;
}

bool StrToProgramTask(char *const pTaskStr, Task &task)
{
	if (strcmp(pTaskStr, "encrypt") == 0)
	{
		task = ENCRYPT;
	}
	else if (strcmp(pTaskStr, "decrypt") == 0)
	{
		task = DECRYPT;
	}
	else
	{
		return false;
	}

	return true;
}

// check arguments function

bool CheckArgumentsCount(int argc)
{
	if (argc < 2)
	{
		printf(MSG_NO_ARGS);
		return false;
	}
	if (argc < 5)
	{
		printf(MSG_ERR_NOT_ENOUGH_ARGS);
		return false;
	}
	if (argc > 5)
	{
		printf(MSG_ERR_TOO_MANY_ARGS);
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

	Task task;
	if (StrToProgramTask(argv[1], task))
	{
		unsigned char key;
		if (GetKey(argv[4], key))
		{
			if (PerformAction(task, argv[2], argv[3], key))
			{
				PrintGoodEndMsg(task);
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
		printf(MSG_ERR_WRONG_ACTION_ARGUMENT);
		return 1;
	}

	return 0;
}

