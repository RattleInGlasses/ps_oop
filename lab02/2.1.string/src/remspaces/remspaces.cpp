// remspaces.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

enum ReadState
{
	BEGINING,
	WORD,
	SPACE,
	END
};

using namespace std;

/*
string RemoveExtraSpaces(string const &arg)
{
	ReadState state = BEGINING;
	size_t i = 0;
	unsigned char ch;
	string result;
	result.reserve(arg.length());
	while (state != END)
	{
		if (i == arg.length())
		{
			state = END;
			continue;
		}
		ch = arg[i++];
		switch (state)
		{
			case BEGINING:
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
*/

string RemoveExtraSpaces(string const &arg)
{
	string result;
	result.reserve(arg.length());
	string word;
	istringstream inputStream(arg);
	while (inputStream >> word)
	{
		result += word;
		result += " ";
	}
	if (result.length() > 0)
	{
		result.erase(result.length() - 1);
	}

	return result;
}

void SendFormattedInputToOutput(istream &input, ostream &output)
{
	string line;
	while (getline(input, line))
	{
		output << RemoveExtraSpaces(line);
		input.unget();
		if (input.get() == '\n')
		{
			output << endl;
		}
	}
}

void TestRemoveExtraSpaces()
{
	assert(RemoveExtraSpaces("") == "");
	assert(RemoveExtraSpaces(" ") == "");
	assert(RemoveExtraSpaces("    ") == "");
	assert(RemoveExtraSpaces("a") == "a");
	assert(RemoveExtraSpaces("abcde") == "abcde");
	assert(RemoveExtraSpaces("  abc") == "abc");
	assert(RemoveExtraSpaces("abc  ") == "abc");
	assert(RemoveExtraSpaces(" a  b   c  ") == "a b c");
}

int main()
{
	TestRemoveExtraSpaces();

	SendFormattedInputToOutput(cin, cout);
	
	return 0;
}

