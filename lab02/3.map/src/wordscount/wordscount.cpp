#include "stdafx.h"

using namespace std;

string ReadWord(istream &input)
{
	string word;
	locale loc(".866");
	int ch = input.get();
	while (isspace(ch, loc) && !input.eof())
	{
		ch = input.get();
	}
	while (!isspace(ch, loc) && !input.eof())
	{
		word += ch;
		ch = input.get();
	}

	return word;
}

string ToLowerCase(string const &str)
{
	string result;
	locale rusLoc(".866");
	for (string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		result += tolower(*it, rusLoc);
	}
	return result;
}

void AddWord(string word, map<string, int> &words)
{
	if (word != "")
	{
		word = ToLowerCase(word);

		if (words.find(word) != words.end())
		{
			words[word]++;
		}
		else
		{
			words[word] = 1;
		}
	}
}

void PrintWord(pair<string, int> const &word)
{
	cout << word.first << ' ' << word.second << '\n';
}

void PrintWords(map<string, int> const &words)
{
	for_each(words.begin(), words.end(), &PrintWord);
}

void TestAddWord()
{
	map<string, int> testWords;
	map<string, int> words;
	
	AddWord("", testWords);
	assert(testWords == words);
	
	AddWord("Word", testWords);
	words["word"] = 1;
	assert(testWords == words);

	AddWord("woRd", testWords);
	words["word"] = 2;
	assert(testWords == words);

	AddWord("Ка†б≠л©", testWords); // расный в cp866
	words["™а†б≠л©"] = 1;          //красный в cp866
	assert(testWords == words);

	cout << "testing of AddWord successfully completed\n";
}

int main()
{
	//TestAddWord();
	
	map<string, int> words;
	while (!cin.eof())
	{
		AddWord(ReadWord(cin), words);
	}
	PrintWords(words);
	
	return 0;
}

