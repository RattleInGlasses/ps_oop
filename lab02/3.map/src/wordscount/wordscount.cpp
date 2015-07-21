#include "stdafx.h"

using namespace std;

string ReadWord(istream &input)
{
	string word;
	input >> word;
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
		++words[word];
	}
}

void PrintWords(map<string, int> const &words)
{
	for_each(words.begin(), words.end(), [](pair<string, int> const &word) { cout << word.first << ' ' << word.second << endl; });
}

bool MapsAreEqual(const map<string, int> & lhs, const map<string, int> & rhs)
{
	return lhs == rhs;
}

void TestAddWord()
{
	map<string, int> testWords;
	
	AddWord("", testWords);
	assert(MapsAreEqual(testWords, {}));
	
	AddWord("Word", testWords);
	assert(MapsAreEqual(testWords, {
		{"word", 1}
	}));

	AddWord("woRd", testWords);
	assert(MapsAreEqual(testWords, {
		{ "word", 2 }
	}));

	AddWord("Ка†б≠л©", testWords);     // расный в cp866       
	assert(MapsAreEqual(testWords, {
		{ "word", 2 },
		{ "™а†б≠л©", 1 }               //красный в cp866
	}));

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

