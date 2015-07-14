// remspaces.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

enum ReadState
{
	NEW_LINE,
	WORD,
	SPACE,
	END
};

using namespace std;

string RemoveExtraSpaces(string const &arg)
{
	ReadState state = NEW_LINE;
	int i = 0;
	unsigned char ch;
	string result = "";
	while (state != END)
	{
		ch = arg[i++];
		if (ch == '\n')
		{
			state = NEW_LINE;
			result += '\n';
			ch = arg[i++];
		}
		if (ch == '\0')
		{
			state = END;
		}
		switch (state)
		{
			case NEW_LINE:
				if (ch != ' ')
				{
					result += ch;
					state = WORD;
				}
				break;
			case WORD:
				if (ch != ' ')
				{
					result += ch;
				}
				else
				{
					state = SPACE;
				}
				break;
			case SPACE:
				if (ch != ' ')
				{
					result += ' ';
					result += ch;
					state = WORD;
				}
				break;
		}
	}

	return result;
}

void SendFormattedInputToOutput(istream &input, ostream &output)
{
	string line;
	getline(input, line, '\x1A');
	output << RemoveExtraSpaces(line);
}

void TestRemoveExtraSpaces()
{
	assert(RemoveExtraSpaces("") == "");
	assert(RemoveExtraSpaces(" ") == "");
	assert(RemoveExtraSpaces("    ") == "");
	assert(RemoveExtraSpaces("\n") == "\n");
	assert(RemoveExtraSpaces("a") == "a");
	assert(RemoveExtraSpaces("abcde") == "abcde");
	assert(RemoveExtraSpaces("  abc") == "abc");
	assert(RemoveExtraSpaces("abc  ") == "abc");
	assert(RemoveExtraSpaces(" a  b   c  ") == "a b c");
	assert(RemoveExtraSpaces("abc\n  ab ") == "abc\nab");
}

int main()
{
	//TestRemoveExtraSpaces();

	SendFormattedInputToOutput(cin, cout);
	
	return 0;
}

