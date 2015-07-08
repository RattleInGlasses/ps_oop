// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

enum ConversionError
{
	OK,
	LESS_THAN_0,
	MORE_THAN_255,
	NOT_INTEGER
};

unsigned char ReverseByte(unsigned char inputByte)
{
	unsigned char lastBit;
	unsigned char reversedByte = 0;
	for (int i = 0; i < 8; i++)
	{
		reversedByte <<= 1;
		lastBit = inputByte & 1;
		inputByte >>= 1;
		reversedByte += lastBit;
	}

	return reversedByte;
}

bool StrIsEmpty(char* str)
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

ConversionError StringToByte(char* const pStr, unsigned char &byte)
{
	char* endP;
	int number = strtol(pStr, &endP, 10);

	if ((!StrIsEmpty(endP)) || (StrIsEmpty(pStr)))
	{
		return NOT_INTEGER;
	}
	if (number < 0)
	{
		return LESS_THAN_0;
	}
	if (number > 255)
	{
		return MORE_THAN_255;
	}

	byte = (unsigned char)number;

	return OK;
}

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf("The program reverses bit structure of a given number.\n");
		printf("The number must be integer with base of 10 that is\n");
		printf("no less than 0 and no more than 255.\n");
		printf("USAGE: flipbyte <number>\n");
		exit(0);
	}
	if (argc > 2)
	{
		printf("The program needs only one argument.\n");
		printf("USAGE: flipbyte <number>\n");
		exit(1);
	}
}

void CheckConversionError(ConversionError error)
{
	switch (error)
	{
		case LESS_THAN_0:
			printf("The number must not be negative\n");
			exit(1);
			break;
		case MORE_THAN_255:
			printf("The number must be no more than 255\n");
			exit(1);
			break;
		case NOT_INTEGER:
			printf("The argument must be an integer number with base of 10\n");
			exit(1);
			break;
	}
}

int main(int argc, char* argv[])
{
	CheckArgc(argc);

	// convert string to byte
	unsigned char byte;
	ConversionError error = StringToByte(argv[1], byte);
	CheckConversionError(error);	
	// reverse byte structure
	printf("%d\n", ReverseByte(byte));

	return 0;
}
