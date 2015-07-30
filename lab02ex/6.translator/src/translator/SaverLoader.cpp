#include "stdafx.h"

using namespace std;

char const WORD_BOUND_RIGHT = ']';
char const WORD_BOUND_LEFT =  '[';

string const MSG_ERR_NOINPUT =  "Can't open vocabulary file.\nMake sure you have enough rights and the file really exists.\n";
string const MSG_ERR_NOOUTPUT = "Error saving vocabulary file.\nMake sure you have enough rights.\n";
string const MSG_END_SAVING =   "Changes in vocabulary have been saved\n";

bool SaveVocabulary(map<string, string> const &vocabulary, char *pVocabularyFileName)
{
	ofstream vocabularyFileStream(pVocabularyFileName, ofstream::out);
	if (!vocabularyFileStream.is_open())
	{
		cout << MSG_ERR_NOOUTPUT;
		return false;
	}

	string vocabularyFileLine;
	for (map<string, string>::const_iterator it = vocabulary.begin(); it != vocabulary.end(); it++)
	{
		vocabularyFileLine = WORD_BOUND_LEFT + it->first + WORD_BOUND_RIGHT + " " + it->second;
		vocabularyFileStream << vocabularyFileLine << endl;
	}
	cout << MSG_END_SAVING;

	return true;
}

void AddVocabularyRecord(map<string, string> &vocabulary, string const &word, string const &translation)
{
	if ((word != "") && (translation != ""))  // second condition allows to skip bad lines of the vocabulary where there is a word but no translation
	{
		vocabulary[word] = translation;
	}
}

string GetTranslation(string const &line)
{
	size_t startPos = line.find(WORD_BOUND_RIGHT) + 2;
	return (startPos >= line.length()) ? "" : line.substr(startPos);
}

string GetWord(string const &line)
{
	regex wordReg("^\\[([[:print:]]+)\\]");
	smatch searchResult;
	if (regex_search(line, searchResult, wordReg))
	{
		string found = searchResult.str();
		return found.substr(1, found.length() - 2);
	}
	return "";
}

boost::optional<map<string, string>> GetVocabularyMap(char const *pVocabularyFileName)
{
	map<string, string> vocabulary;
	
	ifstream vocabularyStream(pVocabularyFileName, ifstream::in);
	if (vocabularyStream.is_open())
	{
		string line;
		string word, translation;
		while (getline(vocabularyStream, line))
		{
			word = GetWord(line);
			translation = GetTranslation(line);
			AddVocabularyRecord(vocabulary, word, translation);
		}
	}

	return vocabulary;
}

