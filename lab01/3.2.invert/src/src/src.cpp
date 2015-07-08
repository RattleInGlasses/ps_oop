// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MSG_USAGE                  "USAGE: invert <matrix file>\n"
#define MSG_DESCRIPTION_1          "The program is trying to calculate the invert matrix for\n"
#define MSG_DESCRIPTION_2          "a given one in a text file.\n"
#define MSG_DESCRIPTION_3          "The matrix must have size of 3 x 3.\n"
#define MSG_DESCRIPTION            MSG_DESCRIPTION_1 MSG_DESCRIPTION_2 MSG_DESCRIPTION_3 MSG_USAGE
#define MSG_ERR_TOO_MANY_PARMS     "The program needs only one argument\n"
#define MSG_ERR_OPENING            "Error opening file (not enough rights or the file doesn't exists)\n"
#define MSG_ERR_WRONG_FILE_CONTENT "The file must contain matrix with size of 3 x 3\n"
#define MSG_NO_RESULT              "The matrix can't be inverted\n"

#define READ_BUFFER_SIZE 255

enum MatrixFileError
{
	ERR_OK,
	ERR_SMALL_FILE,
	ERR_BIG_FILE,
	ERR_NOT_A_VALID_MATRIX
};

bool StrIsEmpty(char* pStr)
{
	int i = 0;
	while (pStr[i] != '\0')
	{
		if ((pStr[i] != ' ') && ((pStr[i] != '\t')) && (pStr[i] != '\n'))
		{
			return false;
		}
		i++;
	}
	return true;
}

MatrixFileError GetMatrixFromFile(FILE* pMatrixFile, double matrix[3][3])
{
	char buff[READ_BUFFER_SIZE];
	char* pLine;
	char* pEndPos;
	for (int i = 0; i < 3; i++)
	{
		pLine = fgets(buff, sizeof(buff), pMatrixFile);
		if (pLine == NULL) // check that file contains 3 lines
		{
			return ERR_SMALL_FILE;
		}

		for (int j = 0; j < 3; j++)
		{
			if (StrIsEmpty(pLine)) // check that line contains 3 numbers
			{
				return ERR_SMALL_FILE;
			}
			matrix[i][j] = strtod(pLine, &pEndPos);
			pLine = pEndPos;
		}
		if (!StrIsEmpty(pEndPos))
		{
			return ERR_NOT_A_VALID_MATRIX;
		}
	}

	return ERR_OK;
}

double Determinant(double const matrix[2][2])
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
}

double Determinant(double const m[3][3])
{
	return (m[0][0] * m[1][1] * m[2][2]) - (m[0][0] * m[1][2] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2])
		+ (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1]) - (m[0][2] * m[1][1] * m[2][0]);
}

void GetMinor(double const matrix[3][3], int i, int j, double minor[2][2])
{
	int minori = 0;
	int minorj = 0;
	for (int matrixi = 0; matrixi < 3; matrixi++)
	{
		if (matrixi != i)
		{
			for (int matrixj = 0; matrixj < 3; matrixj++)
			{
				if (matrixj != j)
				{
					minor[minori][minorj] = matrix[matrixi][matrixj];
					minorj++;
				}
			}
			minorj = 0;
			minori++;
		}
	}
}

void GetMinorMatrix(double const matrix[3][3], double minorMatrix[3][3])
{
	double minor[2][2];
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
		GetMinor(matrix, j, i, minor);
		minorMatrix[i][j] = pow(-1.0, i + j) * Determinant(minor);
	}
}

// Multiply matrix by number
void NumMultMatrix(double const inputMatrix[3][3], double number, double resultMatrix[3][3])
{
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
		resultMatrix[i][j] = number * inputMatrix[i][j];
	}
}

//return true if matrix can't be inverted
bool InvertMatrix(double const matrix[3][3], double invertedMatrix[3][3])
{
	double matrixDet = Determinant(matrix);
	if (matrixDet == 0)
	{
		return true;
	}

	double minorMatrix[3][3];
	GetMinorMatrix(matrix, minorMatrix);
	NumMultMatrix(minorMatrix, (1.0 / matrixDet), invertedMatrix);

	return false;
}

void PrintMatrix(double matrix[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f ", (matrix[i][j] ? matrix[i][j] : 0)); //prevent output of negative zeroes
		}
		printf("\n");
	}
}

void CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION);
		exit(0);
	}
	if (argc > 2)
	{
		printf(MSG_ERR_TOO_MANY_PARMS);
		printf(MSG_USAGE);
		exit(1);
	}
}

void CheckMatrixFileError(MatrixFileError err)
{
	switch (err)
	{
		case ERR_SMALL_FILE:
			printf(MSG_ERR_WRONG_FILE_CONTENT);
			exit(1);
			break;
		case ERR_NOT_A_VALID_MATRIX:
			printf(MSG_ERR_WRONG_FILE_CONTENT);
			exit(1);
			break;
	}
}

FILE *OpenInputFile(char *pFileName)
{
	FILE *pFile = fopen(pFileName, "r");
	if (!pFile)
	{
		printf(MSG_ERR_OPENING);
		exit(1);
	}

	return pFile;
}

void CloseFile(FILE *pFile)
{
	if (pFile)
	{
		fclose(pFile);
	}
}

int main(int argc, char* argv[])
{
	CheckArgc(argc);

	double matrix[3][3];
	FILE *pMatrixFile = OpenInputFile(argv[1]);
	MatrixFileError err = GetMatrixFromFile(pMatrixFile, matrix);
	CheckMatrixFileError(err);

	double invertedMatrix[3][3];
	bool noResult = InvertMatrix(matrix, invertedMatrix);
	if (noResult)
	{
		printf(MSG_NO_RESULT);
	}
	else
	{
		PrintMatrix(invertedMatrix);
	}

	CloseFile(pMatrixFile);
	return 0;
}

