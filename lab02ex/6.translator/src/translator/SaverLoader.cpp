#include "stdafx.h"

#define WORD_BOUND_RIGHT ']'
#define WORD_BOUND_LEFT  '['

#define MSG_ERR_NOINPUT  "Can't open vocabulary file.\nMake sure you have enough rights and the file really exists.\n"
#define MSG_ERR_NOOUTPUT "Error saving vocabulary file.\nMake sure you have enough rights.\n"
#define MSG_END_SAVING  "Changes in vocabulary have been saved\n"

using namespace std;

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
	size_t leftBoundPos = line.find(WORD_BOUND_LEFT);
	size_t startPos = (leftBoundPos == string::npos) ? string::npos : (leftBoundPos + 1);
	size_t endPos = line.find(WORD_BOUND_RIGHT);
	size_t len = endPos - startPos;

	return (startPos == string::npos) ? "" : (line.substr(startPos, len));
}

bool GetVocabularyMap(char const *pVocabularyFileName, map<string, string> &vocabulary)
{
	ifstream vocabularyStream(pVocabularyFileName, ifstream::in);
	if (!vocabularyStream.is_open())
	{
		cout << MSG_ERR_NOINPUT;
		return false;
	}
	
	vocabulary.clear();
	string line;
	string word, translation;
	while (getline(vocabularyStream, line))
	{
		word = GetWord(line);
		translation = GetTranslation(line);
		AddVocabularyRecord(vocabulary, word, translation);
	}

	return true;
}

