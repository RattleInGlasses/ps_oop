// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


const char CELL_WALL  = '*';
const char CELL_ALIVE = '#';
const char CELL_DEAD  = ' ';

std::string MSG_USAGE =                       "USAGE: life <input file> [<output file>]\n";
std::string MSG_DESCRIPTION =                 "The program calculates next generation of cells based on input file\nand prints the result out into a file or the standart output.\n" + MSG_USAGE;
std::string MSG_ERR_TOO_MANY_ARGS =           "The program needs just 1 or 2 arguments\n" + MSG_USAGE;
std::string MSG_ERR_NO_INPUT =                "Error opening input file.\nMake sure you have enough rights and the file really exists.\n";
std::string MSG_ERR_NO_OUTPUT =               "Error opening output file.\nMake sure you have enough rights.\n";
std::string MSG_ERR_BAD_INPUT_FILE =          "The given file doesn't contain a valid life field.\n";
std::string MSG_ERR_ZERO_FIELD_WIDTH =        MSG_ERR_BAD_INPUT_FILE + "Zero field width\n";
std::string MSG_ERR_ZERO_FIELD_HEIGHT =       MSG_ERR_BAD_INPUT_FILE + "Zero field height\n";
std::string MSG_ERR_TOO_BIG_FIELD_WIDTH =     MSG_ERR_BAD_INPUT_FILE + "Width is too big, it must be no more than 256\n";
std::string MSG_ERR_TOO_BIG_FIELD_HEIGHT =    MSG_ERR_BAD_INPUT_FILE + "Height is too big, it must be no more than 256\n";
std::string MSG_ERR_FIELD_HAS_NO_WIDTH =      MSG_ERR_BAD_INPUT_FILE + "Filed has no valid bounds\n";
std::string MSG_ERR_FIELD_HAS_NO_BOTTOM =     MSG_ERR_BAD_INPUT_FILE + "Field has no valid bottom\n";
std::string MSG_ERR_FIELD_INVALID_SYMBOL =    MSG_ERR_BAD_INPUT_FILE + "Invalid symbol on a field ";
std::string MSG_GOOD_END =                    "\nThe next generation of life has been successfully calculated\n";

enum CellState
{
	DEAD,
	ALIVE
};

struct CellsField
{
	int height;
	int width;
	CellState **cells = nullptr;
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
	if (field.cells != nullptr)
	{
		for (int i = 0; i < field.height; i++)
		{
			free(field.cells[i]);
		}
		free(field.cells);
	}
}

// process field

bool IsValidCell(int x, int y, int fieldWidth, int fieldHeight)
{
	return (y >= 0) && (x >= 0) && (y < fieldHeight) && (x < fieldWidth);
}

int GetNeighboursCount(CellsField const &field, int x, int y)
{
	int count = 0;
	for (int curY = y - 1; curY <= y + 1; curY++)
	{
		for (int curX = x - 1; curX <= x + 1; curX++)
		{
			if (IsValidCell(curX, curY, field.width, field.height)  // the cell must be valid (not a wall)
				&& !((curY == y) && (curX == x))                    // do not count analyzed cell
				&& (field.cells[curY][curX] == ALIVE))              // the cell must be alive
			{
				count++;
			}
		}
	}

	return count;
}

CellState CalcNextGenCellState(int x, int y, CellsField const &curGenField)
{
	CellState state = curGenField.cells[y][x];
	int neighboursCount = GetNeighboursCount(curGenField, x, y);
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

	return state;
}

CellsField CalcNextGenField(CellsField const &curGenField)
{
	CellsField nextGenField = CreateField(curGenField.width, curGenField.height);
	CellState state;
	int neighboursCount;
	for (int y = 0; y < curGenField.height; y++)
	{
		for (int x = 0; x < curGenField.width; x++)
		{
			nextGenField.cells[y][x] = CalcNextGenCellState(x, y, curGenField);
		}
	}

	return nextGenField;
}

// field output

void PrintCell(FILE *pOutFile, int x, int y, CellsField const &field)
{
	if (!IsValidCell(x, y, field.width, field.height))
	{
		fputc(CELL_WALL, pOutFile);
	}
	else if (field.cells[y][x] == ALIVE)
	{
		fputc(CELL_ALIVE, pOutFile);
	}
	else
	{
		fputc(CELL_DEAD, pOutFile);
	}
}

bool PrintField(char *pOutFileName, CellsField const &field)
{
	FILE *pOutFile = (pOutFileName != nullptr) ? fopen(pOutFileName, "w") : stdout;
	if (!pOutFile)
	{
		printf(MSG_ERR_NO_OUTPUT.c_str());
		return false;
	}
	
	for (int y = -1; y <= field.height; y++)
	{
		for (int x = -1; x <= field.width; x++)
		{
			PrintCell(pOutFile, x, y, field);
		}
		fputc('\n', pOutFile);
	}

	if (pOutFile != stdout)
	{
		fclose(pOutFile);
	}

	return true;
}

// field init
	// get width

bool CheckWallWidth(int wallWidth)
{
	if ((wallWidth - 2) < 0)
	{
		printf(MSG_ERR_FIELD_HAS_NO_WIDTH.c_str());
		return false;
	}
	if ((wallWidth - 2) == 0)
	{
		printf(MSG_ERR_ZERO_FIELD_WIDTH.c_str());
		return false;
	}
	return true;
}

// scans first line of the file to get width of the upper field wall
int GetUpperWallWidth(FILE *pFieldFile)
{
	int ch = fgetc(pFieldFile);
	int wallWidth = 0;
	while (ch == CELL_WALL)
	{
		wallWidth++;
		ch = fgetc(pFieldFile);
	}
	rewind(pFieldFile);

	return wallWidth;
}

boost::optional<int> GetFieldWidth(FILE *pFieldFile)
{
	int upperWallWidth = GetUpperWallWidth(pFieldFile);
	if (!CheckWallWidth(upperWallWidth))
	{
		return boost::none;
	}

	return upperWallWidth - 2;
}

	// get height

bool CheckLeftWallHeight(int wallHeight)
{
	if ((wallHeight - 2) == 0)
	{
		printf(MSG_ERR_ZERO_FIELD_HEIGHT.c_str());
		return false;
	}
	return true;
}

void SkipToNewLine(FILE *pFile)
{
	int ch = fgetc(pFile);
	while ((ch != '\n') && (ch != EOF))
	{
		ch = fgetc(pFile);
	}
}

// scans first and second chars of lines to get height of the left field wall
boost::optional<int> GetLeftWallHeight(FILE *pFieldFile)
{
	int ch;
	int count = 1;
	bool endOfField = false;
	while (!endOfField)
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
			printf(MSG_ERR_FIELD_HAS_NO_BOTTOM.c_str());
			return boost::none;
		}
		// check second symbol of the line
		ch = fgetc(pFieldFile);
		if (ch == CELL_WALL)
		{
			endOfField = true;
		}
		ungetc(ch, pFieldFile);
	}
	rewind(pFieldFile);

	return count;
}

boost::optional<int> GetFieldHeight(FILE *pFieldFile)
{
	boost::optional<int> leftWallHeight;
	if ((leftWallHeight = GetLeftWallHeight(pFieldFile))
		&& (CheckLeftWallHeight(*leftWallHeight)))
	{
		return (*leftWallHeight - 2);
	}

	return boost::none;
}

bool CheckFieldDimension(int dimension, char const *pErrMsg)
{
	if (dimension > 256)
	{
		printf(pErrMsg);
		return false;
	}
	return true;
}

bool SetCellState(CellState &cell, char cellFileSymbol)
{
	if (cellFileSymbol == CELL_DEAD)
	{
		cell = DEAD;
	}
	else if (cellFileSymbol == CELL_ALIVE)
	{
		cell = ALIVE;
	}
	else
	{
		printf(MSG_ERR_FIELD_INVALID_SYMBOL.c_str());
		return false;
	}

	return true;
}

bool FillField(CellsField &field, FILE *pFieldFile)
{
	for (int i = 0; i < field.height; i++)
	{
		//goto next line
		SkipToNewLine(pFieldFile);
		int ch = fgetc(pFieldFile);

		//start from second symbol
		for (int j = 0; j < field.width; j++)
		{
			if (!SetCellState(field.cells[i][j], fgetc(pFieldFile)))
			{
				printf("at line %d column %d\n", (i + 1), (j + 1));
				return false;
			}
		}
	}
	return true;
}

bool ReadField(char *pFieldFileName, CellsField &field)
{
	FILE *pFieldFile = fopen(pFieldFileName, "r");
	if (pFieldFile)
	{
		boost::optional<int> width, height;
		if ((width = GetFieldWidth(pFieldFile))
			&& (CheckFieldDimension(*width, MSG_ERR_TOO_BIG_FIELD_WIDTH.c_str()))
			&& (height = GetFieldHeight(pFieldFile))
			&& (CheckFieldDimension(*height, MSG_ERR_TOO_BIG_FIELD_HEIGHT.c_str())))
		{
			field = CreateField(*width, *height);
			if (FillField(field, pFieldFile))
			{
				fclose(pFieldFile);
			}
			else
			{
				DestroyField(field);
				fclose(pFieldFile);
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		printf(MSG_ERR_NO_INPUT.c_str());
		return false;
	}
	
	return true;
}

// first check

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION.c_str());
		return false;
	}
	if (argc > 3)
	{
		printf(MSG_ERR_TOO_MANY_ARGS.c_str());
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!CheckArgc(argc))
	{
		return 1;
	}
	
	CellsField field;
	if (ReadField(argv[1], field))
	{
		// calc and print
		CellsField nextGenField = CalcNextGenField(field);
		if (PrintField(((argc == 3) ? argv[2] : nullptr), nextGenField))
		{
			DestroyField(field);
			DestroyField(nextGenField);
			printf(MSG_GOOD_END.c_str());
		}
		else
		{
			DestroyField(field);
			DestroyField(nextGenField);
			return 1;
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

