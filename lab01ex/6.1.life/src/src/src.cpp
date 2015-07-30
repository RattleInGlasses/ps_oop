// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

const char CELL_WALL  = '*';
const char CELL_OCCUPIED = '#';
const char CELL_EMPTY = ' ';

string MSG_USAGE =                       "USAGE: life <input file> [<output file>]\n";
string MSG_DESCRIPTION =                 "The program calculates next generation of cells based on input file\nand prints the result out into a file or the standart output.\n" + MSG_USAGE;
string MSG_ERR_TOO_MANY_ARGS =           "The program needs just 1 or 2 arguments\n" + MSG_USAGE;
string MSG_ERR_NO_INPUT =                "Error opening input file.\nMake sure you have enough rights and the file really exists.\n";
string MSG_ERR_NO_OUTPUT =               "Error opening output file.\nMake sure you have enough rights.\n";
string MSG_ERR_BAD_INPUT_FILE =          "The given file doesn't contain a valid life field.\n";
string MSG_ERR_ZERO_FIELD_WIDTH =        MSG_ERR_BAD_INPUT_FILE + "Zero field width\n";
string MSG_ERR_ZERO_FIELD_HEIGHT =       MSG_ERR_BAD_INPUT_FILE + "Zero field height\n";
string MSG_ERR_TOO_BIG_FIELD_WIDTH =     MSG_ERR_BAD_INPUT_FILE + "Width is too big, it must be no more than 256\n";
string MSG_ERR_TOO_BIG_FIELD_HEIGHT =    MSG_ERR_BAD_INPUT_FILE + "Height is too big, it must be no more than 256\n";
string MSG_ERR_FIELD_HAS_NO_WIDTH =      MSG_ERR_BAD_INPUT_FILE + "Filed has no valid bounds\n";
string MSG_ERR_FIELD_HAS_NO_BOTTOM =     MSG_ERR_BAD_INPUT_FILE + "Field has no valid bottom\n";
string MSG_ERR_FIELD_INVALID_SYMBOL =    MSG_ERR_BAD_INPUT_FILE + "Invalid symbol on a field ";
string MSG_GOOD_END =                    "\nThe next generation of life has been successfully calculated\n";

enum CellState
{
	EMPTY,
	OCCUPIED
};

struct CellsField
{
	int height;
	int width;
	vector<CellState> cells;
};

// work with field
// main methods

CellsField CreateField(int width, int height)
{
	CellsField field;
	field.height = height;
	field.width = width;
	field.cells.resize(height * width);

	return field;
}

bool IsValidCell(int x, int y, int fieldWidth, int fieldHeight)
{
	return (y >= 0) && (x >= 0) && (y < fieldHeight) && (x < fieldWidth);
}

int GetVectorPosition(int x, int y, int width)
{
	return x + y * width;
}

CellState GetCell(CellsField const &field, int x, int y)
{
	return (IsValidCell(x, y, field.width, field.height)) ? field.cells[GetVectorPosition(x, y, field.width)] : EMPTY;
}

void SetCell(CellsField &field, int x, int y, CellState value)
{
	field.cells[GetVectorPosition(x, y, field.width)] = value;
}

// process field

int GetNeighboursCount(CellsField const &field, int x, int y)
{
	auto GetLifeCellCount = [&field](int x, int y)
	{
		return (GetCell(field, x, y) == OCCUPIED) ? 1 : 0;
	};
	return
		GetLifeCellCount(x - 1, y - 1) +
		GetLifeCellCount(x + 0, y - 1) +
		GetLifeCellCount(x + 1, y - 1) +
		GetLifeCellCount(x - 1, y + 0) +
		GetLifeCellCount(x + 1, y + 0) +
		GetLifeCellCount(x - 1, y + 1) +
		GetLifeCellCount(x + 0, y + 1) +
		GetLifeCellCount(x + 1, y + 1);
}

CellState CalcNextGenCellState(int x, int y, CellsField const &curGenField)
{
	CellState state = GetCell(curGenField, x, y);
	int neighboursCount = GetNeighboursCount(curGenField, x, y);
	if (state == EMPTY)
	{
		if (neighboursCount == 3)
		{
			state = OCCUPIED;
		}
	}
	else // state == OCCUPIED
	{
		if ((neighboursCount < 2) || (neighboursCount > 3))
		{
			state = EMPTY;
		}
	}

	return state;
}

CellsField CalcNextGenField(CellsField const &curGenField)
{
	CellsField nextGenField = CreateField(curGenField.width, curGenField.height);
	for (int y = 0; y < curGenField.height; y++)
	{
		for (int x = 0; x < curGenField.width; x++)
		{
			SetCell(nextGenField, x, y, CalcNextGenCellState(x, y, curGenField));
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
	else if (GetCell(field, x, y) == OCCUPIED)
	{
		fputc(CELL_OCCUPIED, pOutFile);
	}
	else
	{
		fputc(CELL_EMPTY, pOutFile);
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

bool SetCellState(CellsField &field, int x, int y, char cellFileSymbol)
{
	
	if (cellFileSymbol == CELL_EMPTY)
	{
		SetCell(field, x, y, EMPTY);
	}
	else if (cellFileSymbol == CELL_OCCUPIED)
	{
		SetCell(field, x, y, OCCUPIED);
	}
	else
	{
		return false;
	}

	return true;
}

bool FillField(CellsField &field, FILE *pFieldFile)
{
	for (int y = 0; y < field.height; ++y)
	{
		//goto next line
		SkipToNewLine(pFieldFile);
		int ch = fgetc(pFieldFile);

		//start from second symbol
		for (int x = 0; x < field.width; ++x)
		{
			if (!SetCellState(field, x, y, fgetc(pFieldFile)))
			{
				printf(MSG_ERR_FIELD_INVALID_SYMBOL.c_str());
				printf("at line %d column %d\n", (y + 1), (x + 1));
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
			printf(MSG_GOOD_END.c_str());
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

	return 0;
}

