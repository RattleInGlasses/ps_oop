// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#define CELL_WALL  '*'
#define CELL_ALIVE '#'
#define CELL_DEAD  ' '

#define MSG_USAGE                       "USAGE: life <input file> [<output file>]\n"
#define MSG_DESCRIPTION                 "The program calculates next generation of cells based on input file\nand prints the result out into a file or the standart output.\n" MSG_USAGE
#define MSG_ERR_TOO_MANY_ARGS           "The program needs just 1 or 2 arguments\n" MSG_USAGE
#define MSG_ERR_NO_INPUT                "Error opening input file.\nMake sure you have enough rights and the file really exists.\n"
#define MSG_ERR_NO_OUTPUT               "Error opening output file.\nMake sure you have enough rights.\n"
#define MSG_ERR_BAD_INPUT_FILE          "The given file doesn't contain a valid life field.\n"
#define MSG_ERR_ZERO_FIELD_WIDTH        MSG_ERR_BAD_INPUT_FILE "Zero field width\n"
#define MSG_ERR_ZERO_FIELD_HEIGHT       MSG_ERR_BAD_INPUT_FILE "Zero field height\n"
#define MSG_ERR_TOO_BIG_FIELD_WIDTH     MSG_ERR_BAD_INPUT_FILE "Width is too big, it must be no more than 256\n"
#define MSG_ERR_TOO_BIG_FIELD_HEIGHT    MSG_ERR_BAD_INPUT_FILE "Height is too big, it must be no more than 256\n"
#define MSG_ERR_FIELD_HAS_NO_BOTTOM     MSG_ERR_BAD_INPUT_FILE "Field has no valid bottom\n"
#define MSG_ERR_FIELD_INVALID_SYMBOL    MSG_ERR_BAD_INPUT_FILE "Invalid symbol on a field "
#define MSG_GOOD_END                    "\nThe next generation of life has been successfully calculated\n"

enum CellState
{
	DEAD,
	ALIVE
};

struct CellsField
{
	int height;
	int width;
	CellState **cells;
};

// work with field
// create destroy

CellsField CreateField(int width, int height)
{
	CellsField field;
	field.height = height;
	field.width = width;
	field.cells = (CellState**)malloc(field.height * sizeof(CellState*));
	for (int i = 0; i < field.height; i++)
	{
		field.cells[i] = (CellState*)malloc(field.width * sizeof(CellState));
	}

	return field;
}

void DestroyField(CellsField &field)
{
	for (int i = 0; i < field.height; i++)
	{
		free(field.cells[i]);
	}
	free(field.cells);
}

// process field

bool IsValidCell(int x, int y, int fieldWidth, int fieldHeight)
{
	return (y >= 0) && (x >= 0) && (y < fieldHeight) && (x < fieldWidth);
}

int GetNeighboursCount(CellsField &const field, int x, int y)
{
	int count = 0;
	for (int i = y - 1; i <= y + 1; i++)
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (IsValidCell(j, i, field.width, field.height)
				&& !((i == y) && (j == x))
				&& (field.cells[i][j] == ALIVE))
			{
				count++;
			}
		}

	return count;
}

CellsField CalcNextGenField(CellsField &const curGenField)
{
	CellsField nextGenField = CreateField(curGenField.width, curGenField.height);
	CellState state;
	int neighboursCount;
	for (int i = 0; i < curGenField.height; i++)
	{
		for (int j = 0; j < curGenField.width; j++)
		{
			state = curGenField.cells[i][j];
			neighboursCount = GetNeighboursCount(curGenField, j, i);
			if (state == DEAD)
			{
				if (neighboursCount == 3)
				{
					state = ALIVE;
				}
			}
			else // state == ALIVE
			{
				if ((neighboursCount < 2) || (neighboursCount > 3))
				{
					state = DEAD;
				}
			}

			nextGenField.cells[i][j] = state;
		}
	}

	return nextGenField;
}

// field output

void PrintField(FILE *pOutFile, CellsField &const field)
{
	for (int i = -1; i <= field.height; i++)
	{
		for (int j = -1; j <= field.width; j++)
		{
			if (!IsValidCell(j, i, field.width, field.height))
			{
				fputc(CELL_WALL, pOutFile);
			}
			else if (field.cells[i][j] == ALIVE)
			{

				fputc(CELL_ALIVE, pOutFile);
			}
			else
			{
				fputc(CELL_DEAD, pOutFile);
			}
		}
		fputc('\n', pOutFile);
	}
}

// field init

void SkipToNewLine(FILE *pFile)
{
	int ch = fgetc(pFile);
	while ((ch != '\n') && (ch != EOF))
	{
		ch = fgetc(pFile);
	}
}

// scans first line of the file to get width of the field
int GetFieldWidth(FILE *pFieldFile)
{
	int ch = fgetc(pFieldFile);
	int count = 0;
	while (ch == CELL_WALL)
	{
		count++;
		ch = fgetc(pFieldFile);
	}

	rewind(pFieldFile);
	return count - 2;
}

// scans first and second chars of a line to get height of the field
int GetFieldHeight(FILE *pFieldFile)
{
	int ch;
	int count = 0;
	while (true)
	{
		SkipToNewLine(pFieldFile);
		// check first symbol of the line
		ch = fgetc(pFieldFile);
		if (ch == CELL_WALL)
		{
			count++;
		}
		else
		{
			printf(MSG_ERR_FIELD_HAS_NO_BOTTOM);
			exit(1);
		}
		// check second symbol of the line
		ch = fgetc(pFieldFile);
		if (ch == CELL_WALL)
		{
			// End of field
			break;
		}
		ungetc(ch, pFieldFile);
	}

	rewind(pFieldFile);
	return count - 1;
}

void CheckFieldDimension(int fieldDim, int min, int max, char *pLessMinErrMsg, char *pMoreMaxErrMsg)
{
	if (fieldDim < min)
	{
		printf(pLessMinErrMsg);
		exit(1);
	}
	if (fieldDim > max)
	{
		printf(pMoreMaxErrMsg);
		exit(1);
	}
}

void FillField(CellsField &field, FILE *pFieldFile)
{
	for (int i = 0; i < field.height; i++)
	{
		//goto next line
		SkipToNewLine(pFieldFile);
		int ch = fgetc(pFieldFile);

		//start with second symbol
		for (int j = 0; j < field.width; j++)
		{
			ch = fgetc(pFieldFile);
			if (ch == CELL_DEAD)
			{
				field.cells[i][j] = DEAD;
			}
			else if (ch == CELL_ALIVE)
			{
				field.cells[i][j] = ALIVE;
			}
			else
			{
				printf(MSG_ERR_FIELD_INVALID_SYMBOL);
				printf("at line %d column %d\n", (i + 1), (j + 1));
				exit(1);
			}
		}
	}
}

CellsField ReadField(FILE *pFieldFile)
{
	int width = GetFieldWidth(pFieldFile);
	CheckFieldDimension(width, 1, 256, MSG_ERR_ZERO_FIELD_WIDTH, MSG_ERR_TOO_BIG_FIELD_WIDTH);
	int height = GetFieldHeight(pFieldFile);
	CheckFieldDimension(height, 1, 256, MSG_ERR_ZERO_FIELD_HEIGHT, MSG_ERR_TOO_BIG_FIELD_HEIGHT);

	CellsField field = CreateField(width, height);
	FillField(field, pFieldFile);

	return field;
}

// first check

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION);
		exit(0);
	}
	if (argc > 3)
	{
		printf(MSG_ERR_TOO_MANY_ARGS);
		exit(1);
	}
}

FILE *OpenFile(char *pFileName, char* pMode, char* ErrorMessage)
{
	FILE *pFile = fopen(pFileName, pMode);
	if (!pFile)
	{
		printf(ErrorMessage);
		exit(1);
	}
	return pFile;
}

// deinit

void CloseFile(FILE *pFile)
{
	if (pFile != stdout)
		fclose(pFile);
}

int main(int argc, char* argv[])
{
	// init
	CheckArgc(argc);
	FILE *pFieldFile = OpenFile(argv[1], "r", MSG_ERR_NO_INPUT);
	FILE *pOutFile = (argc == 3) ? OpenFile(argv[2], "w", MSG_ERR_NO_OUTPUT) : stdout;
	CellsField field = ReadField(pFieldFile);

	// calc and print
	CellsField nextGenField = CalcNextGenField(field);
	PrintField(pOutFile, nextGenField);
	printf(MSG_GOOD_END);

	// deinit
	DestroyField(field);
	DestroyField(nextGenField);
	CloseFile(pFieldFile);
	CloseFile(pOutFile);

	return 0;
}

