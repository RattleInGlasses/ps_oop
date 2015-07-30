// rectangles.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Rectangle.h"
#include "Canvas.h"


using namespace std;


const string MSG_USAGE                = "USAGE: rectangles <file 1> <file 2> <out file>\n";
const string MSG_DESCRIPTION          = "The program reads 2 rectangles from given files, prints their stats and writes them into the given out file or into standard output\n" + MSG_USAGE;
const string MSG_NOT_ENOUGH_ARGUMENTS = "The program needs at least 2 parametrs\n" + MSG_USAGE;
const string MSG_TOO_MANY_ARGUMENTS   = "The program needs only 3 parametrs\n" + MSG_USAGE;
const string MSG_NO_INPUT_1           = "Can't open input file 1\nMake sure you have enough rights and the file really exists";
const string MSG_NO_INPUT_2           = "Can't open input file 2\nMake sure you have enough rights and the file really exists";
const string MSG_NO_OUTPUT            = "Can't open output file\nMake sure you have enough rights";


void FillRectangle(CRectangle const &rect, char code, CCanvas &canvas)
{
	for (int y = rect.GetTop(); y < rect.GetBottom(); ++y)
	{
		for (int x = rect.GetLeft(); x < rect.GetRight(); ++x)
		{
			canvas.SetPixel(x, y, code);
		}
	}
}


void PrintGraphicResult(CRectangle rect1, CRectangle const &rect2, ostream &outStream)
{
	CCanvas canvas(60, 20);
	FillRectangle(rect1, '+', canvas);
	FillRectangle(rect2, '-', canvas);
	if (rect1.Intersect(rect2))
	{
		FillRectangle(rect1, '#', canvas);
	}
	
	canvas.Write(outStream);
}


void PrintRectInfo(string const &rectName, CRectangle const &rect, ostream &outStream)
{
	outStream << rectName << ":\n";
	outStream << "\tLeft top: (" << rect.GetLeft() << "; " << rect.GetTop() << ")" << '\n';
	outStream << "\tSize: " << rect.GetWidth() << "*" << rect.GetHeight() << endl;
	outStream << "\tRightBottom: (" << rect.GetRight() << "; " << rect.GetBottom() << ")" << '\n';

	if (rect.GetArea())
	{
		outStream << "\tArea: " << *rect.GetArea() << '\n';
	}
	else
	{
		outStream << "\tArea: " << "Too big to calculate\n";
	}

	if (rect.GetPerimeter())
	{
		outStream << "\tPerimeter: " << *rect.GetPerimeter() << '\n';
	}
	else
	{
		outStream << "\tPerimeter: " << "Too big to calculate\n";
	}
}


void PrintTextResult(CRectangle rect1, CRectangle const &rect2, ostream &outStream)
{
	PrintRectInfo("Rectangle 1", rect1, outStream);
	PrintRectInfo("Rectangle 2", rect2, outStream);
	if (rect1.Intersect(rect2))
	{
		PrintRectInfo("Intersection rectangle", rect1, outStream);
	}
	else
	{
		outStream << "No intersection\n";
	}
}


void PrintResultToStream(CRectangle const &rect1, CRectangle const &rect2, ostream &outTextStream, ostream &outGraphicStream)
{
	PrintTextResult(rect1, rect2, outTextStream);
	PrintGraphicResult(rect1, rect2, outGraphicStream);
}


bool PrintResult(CRectangle const &rect1, CRectangle const &rect2, char* pOutFileName)
{
	if (pOutFileName)
	{
		ofstream outFileStream(pOutFileName);
		if (outFileStream.is_open())
		{
			PrintResultToStream(rect1, rect2, cout, outFileStream);
		}
		else
		{
			return false;
		}
	}
	else
	{
		PrintResultToStream(rect1, rect2, cout, cout);
	}
	
	return true;
}


void SetRectSizePosition(CRectangle &rect, int left, int top, int width, int height)
{
	if (left > rect.GetRight())
	{
		rect.SetRight(left);
	}
	if (top > rect.GetBottom())
	{
		rect.SetBottom(top);
	}		
	rect.SetLeft(left);
	rect.SetTop(top);

	rect.SetWidth(width);
	rect.SetHeight(height);
}


bool StreamHasNoSignificantCharacters(istream &stream)
{
	char ch;
	while (stream >> ch)
	{
		if (!isspace(ch))
		{
			return false;
		}
	}
	return true;
}

bool TryExecuteScaleCommand(CRectangle &rect, string const &commandLine)
{
	istringstream commandStream(commandLine);
	string command;
	commandStream >> command;

	if (command != "scale")
	{
		return false;
	}

	int sx, sy;
	if ((commandStream >> sx)
		&& (commandStream >> sy)
		&& (StreamHasNoSignificantCharacters(commandStream)))
	{
		rect.Scale(sx, sy);
	}
	else
	{
		return false;
	}

	return true;
}

bool TryExecuteMoveCommand(CRectangle &rect, string const &commandLine)
{
	istringstream commandStream(commandLine);
	string command;
	commandStream >> command;
	
	if (command != "move")
	{
		return false;
	}

	int dx, dy;
	if ((commandStream >> dx)
		&& (commandStream >> dy)
		&& (StreamHasNoSignificantCharacters(commandStream)))
	{
		rect.Move(dx, dy);
	}
	else
	{
		return false;
	}
	
	return true;
}

bool TryExecuteRectangleCommand(CRectangle &rect, string const &commandLine)
{
	istringstream commandStream(commandLine);
	string command;
	commandStream >> command;

	if (command != "rectangle")
	{
		return false;
	}

	int left, top, width, height;
	if ((commandStream >> left)
		&& (commandStream >> top)
		&& (commandStream >> width)
		&& (commandStream >> height)
		&& (StreamHasNoSignificantCharacters(commandStream)))
	{
		SetRectSizePosition(rect, left, top, width, height);
	}
	else
	{
		return false;
	}

	return true;
}


bool Execute(CRectangle &rect, string &commandLine)
{
	boost::to_lower(commandLine);

	if (!TryExecuteRectangleCommand(rect, commandLine))
	{
		if (!TryExecuteMoveCommand(rect, commandLine))
		{
			if (!TryExecuteScaleCommand(rect, commandLine))
			{
				return false;
			}
		}
	}
	
	return true;
}


boost::optional<CRectangle> ReadRectangleFile(char *pRectFileName)
{
	ifstream rectFileStream(pRectFileName, ifstream::in);
	if (!rectFileStream.is_open())
	{
		return boost::none;
	}

	CRectangle rect(0, 0, 0, 0);
	string command;
	size_t lineCount = 0;
	while (getline(rectFileStream, command))
	{
		++lineCount;
		if ((!Execute(rect, command)) && (command != ""))
		{
			cout << "Bad or unknown command skipped (file \"" << pRectFileName << "\" line " << lineCount << ")\n";
		}
	}

	return rect;
}


bool CheckArgc(int argc)
{
	if (argc < 2)
	{
		cout << MSG_DESCRIPTION;
		return false;
	}
	if (argc < 3)
	{
		cout << MSG_NOT_ENOUGH_ARGUMENTS;
		return false;
	}
	if (argc > 4)
	{
		cout << MSG_TOO_MANY_ARGUMENTS;
		return false;
	}

	return true;
}


int main(int argc, char* argv[])
{
	if (CheckArgc(argc))
	{
		if (auto rect1 = ReadRectangleFile(argv[1]))
		{
			if (auto rect2 = ReadRectangleFile(argv[2]))
			{
				if (!PrintResult(*rect1, *rect2, ((argc < 4) ? nullptr : argv[3])))
				{
					cout << MSG_NO_OUTPUT;
					return 1;
				}
			}
			else
			{
				cout << MSG_NO_INPUT_2;
				return 1;
			}
		}
		else
		{
			cout << MSG_NO_INPUT_1;
			return 1;
		}
	}
	else
	{
		return 1;
	}	

	return 0;
}

