#include "stdafx.h"

enum ReadState
{
	BEGINING,
	WORD,
	SPACE,
	END
};

using namespace std;

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
