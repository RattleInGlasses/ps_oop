// src.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

const std::string  MSG_USAGE =                  "USAGE: invert <matrix file>\n";
const std::string  MSG_DESCRIPTION_1 =          "The program is trying to calculate the invert matrix for\n";
const std::string  MSG_DESCRIPTION_2 =          "a given one in a text file.\n";
const std::string  MSG_DESCRIPTION_3 =          "The matrix must have size of 3 x 3.\n";
const std::string  MSG_DESCRIPTION =            MSG_DESCRIPTION_1 + MSG_DESCRIPTION_2 + MSG_DESCRIPTION_3 + MSG_USAGE;
const std::string  MSG_ERR_TOO_MANY_PARMS =     "The program needs only one argument\n";
const std::string  MSG_ERR_OPENING =            "Error opening file (not enough rights or the file doesn't exists)\n";
const std::string  MSG_ERR_WRONG_FILE_CONTENT = "The file must contain matrix with size of 3 x 3\n";
const std::string  MSG_NO_RESULT =              "The matrix can't be inverted\n";

const int READ_BUFFER_SIZE = 255;

struct Matrix3x3
{
	double items[3][3];
};

struct Matrix2x2
{
	double items[2][2];
};

enum MatrixFileError
{
	ERR_OK,
	ERR_OPENING_FILE_ERROR,
	ERR_SMALL_FILE,
	ERR_NOT_A_VALID_MATRIX
};

bool OpenInputFile(char *pFileName, FILE *&pFile)
{
	pFile = fopen(pFileName, "r");
	if (!pFile)
	{
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

bool StrHasSignificantChars(char* pStr)
{
	int i = 0;
	while (pStr[i] != '\0')
	{
		if ((pStr[i] != ' ') && ((pStr[i] != '\t')) && (pStr[i] != '\n'))
		{
			return true;
		}
		i++;
	}
	return false;
}

MatrixFileError ReadMatrixFromFile(FILE* pMatrixFile, Matrix3x3 &matrix)
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
			if (!StrHasSignificantChars(pLine)) // check that line contains 3 numbers
			{
				return ERR_SMALL_FILE;
			}
			matrix.items[i][j] = strtod(pLine, &pEndPos);
			pLine = pEndPos;
		}
		if (StrHasSignificantChars(pEndPos))
		{
			return ERR_NOT_A_VALID_MATRIX;
		}
	}

	return ERR_OK;
}

MatrixFileError GetMatrixFromFile(char* pMatrixFileName, Matrix3x3 &matrix)
{
	FILE *pMatrixFile;
	if (!OpenInputFile(pMatrixFileName, pMatrixFile))
	{
		return ERR_OPENING_FILE_ERROR;
	}
	MatrixFileError err = ReadMatrixFromFile(pMatrixFile, matrix);
	CloseFile(pMatrixFile);

	return err;
}

double Determinant(Matrix2x2 const &matrix)
{
	return (matrix.items[0][0] * matrix.items[1][1]) - (matrix.items[1][0] * matrix.items[0][1]);
}

double Determinant(Matrix3x3 const &m)
{
	return (m.items[0][0] * m.items[1][1] * m.items[2][2]) - (m.items[0][0] * m.items[1][2] * m.items[2][1])
		- (m.items[0][1] * m.items[1][0] * m.items[2][2]) + (m.items[0][1] * m.items[1][2] * m.items[2][0])
		+ (m.items[0][2] * m.items[1][0] * m.items[2][1]) - (m.items[0][2] * m.items[1][1] * m.items[2][0]);
}

Matrix2x2 GetMinor(Matrix3x3 const &matrix, int i, int j)
{
	Matrix2x2 minor;
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
					minor.items[minori][minorj] = matrix.items[matrixi][matrixj];
					minorj++;
				}
			}
			minorj = 0;
			minori++;
		}
	}

	return minor;
}

Matrix3x3 GetMinorMatrix(Matrix3x3 const &matrix)
{
	Matrix3x3 minorMatrix;
	Matrix2x2 minor;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			minor = GetMinor(matrix, j, i);
			minorMatrix.items[i][j] = pow(-1.0, i + j) * Determinant(minor);
		}
	}

	return minorMatrix;
}

// Multiply matrix by number
Matrix3x3 MultMatrixByScalar(Matrix3x3 const &inputMatrix, double number)
{
	Matrix3x3 resultMatrix;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			resultMatrix.items[i][j] = number * inputMatrix.items[i][j];
		}
	}

	return resultMatrix;
}

// return false if matrix can't be inverted
bool InvertMatrix(Matrix3x3 const &matrix, Matrix3x3 &invertedMatrix)
{
	double matrixDet = Determinant(matrix);
	if ((matrixDet < DBL_EPSILON) && (matrixDet > (-1.0 * DBL_EPSILON)))
	{
		return false;
	}

	invertedMatrix = MultMatrixByScalar(GetMinorMatrix(matrix), (1.0 / matrixDet));

	return true;
}

void PrintMatrix(Matrix3x3 const &matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f ", (matrix.items[i][j] ? matrix.items[i][j] : 0)); //prevent output of negative zeroes
		}
		printf("\n");
	}
}

bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		printf(MSG_DESCRIPTION.c_str());
		return false;
	}
	if (argc > 2)
	{
		printf(MSG_ERR_TOO_MANY_PARMS.c_str());
		printf(MSG_USAGE.c_str());
		return false;
	}
	return true;
}

bool CheckMatrixFileError(MatrixFileError err)
{
	switch (err)
	{
		case ERR_OPENING_FILE_ERROR:
			printf(MSG_ERR_OPENING.c_str());
			return false;
			break;
		case ERR_SMALL_FILE:
			printf(MSG_ERR_WRONG_FILE_CONTENT.c_str());
			return false;
			break;
		case ERR_NOT_A_VALID_MATRIX:
			printf(MSG_ERR_WRONG_FILE_CONTENT.c_str());
			return false;
			break;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!CheckArgc(argc))
	{
		return 1;
	}

	Matrix3x3 matrix;
	if (CheckMatrixFileError(GetMatrixFromFile(argv[1], matrix)))
	{
		Matrix3x3 invertedMatrix;
		if (InvertMatrix(matrix, invertedMatrix))
		{
			PrintMatrix(invertedMatrix);
		}
		else
		{
			printf(MSG_NO_RESULT.c_str());
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

