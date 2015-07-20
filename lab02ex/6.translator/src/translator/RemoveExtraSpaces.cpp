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
			continue;
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