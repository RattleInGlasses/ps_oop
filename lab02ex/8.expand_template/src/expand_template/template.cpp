#include "stdafx.h"

char const MASK_SYMBOL_OPENED_FOR_CHAGES = ' ';
char const MASK_SYMBOL_CLOSED_FOR_CHAGES = 'X';

using namespace std;

string StrReplaceByChars(string const &baseStr, char replaceChar, size_t replaceCharCount, size_t pos, size_t len)
{
	string result = baseStr;
	result.erase(pos, len);
	result.insert(pos, replaceCharCount, replaceChar);

	return result;
}

string StrReplace(string const &baseStr, string const &replaceStr, size_t pos, size_t len)
{
	string result = baseStr;
	result.erase(pos, len);
	result.insert(pos, replaceStr);
	
	return result;
}

boost::optional<size_t> GetFirstClosedSymbolPosition(string const &mask, size_t startPos, size_t len)
{
	size_t result = mask.substr(startPos, len).find(MASK_SYMBOL_CLOSED_FOR_CHAGES);
	if (result == string::npos)
	{
		return boost::none;
	}
	else
	{
		return result;
	}
}

// the function uses mask to decide whether it needs to replace findings or not
// the mask is a string with a length == length of str and with a content like "  XX  X "
void Replace(string &str, string const &searchStr, string const &replaceStr, string &mask)
{
	size_t searchFrom = 0;
	size_t pos = str.find(searchStr, searchFrom);
	while (pos != string::npos)
	{
		if (auto firstClosedSymbolPosition = GetFirstClosedSymbolPosition(mask, pos, searchStr.length()))                   // check found substring, using mask                                               
		{
			// if we have found a char that is not meant to be changed then search again starting from a char next to the founded
			searchFrom = *firstClosedSymbolPosition + 1;
		}
		else
		{
			str = StrReplace(str, replaceStr, pos, searchStr.length());                                                     // replace found substring
			mask = StrReplaceByChars(mask, MASK_SYMBOL_CLOSED_FOR_CHAGES, replaceStr.length(), pos, searchStr.length());    // make changes in mask (mark symbols as changed)

			searchFrom = pos + replaceStr.length();
		}
		pos = str.find(searchStr, searchFrom);
	} 
}

// the function returns true if key1 should go before key2 (key1Index < key2Index)
bool KeyCompare(string key1, string key2)
{
	if ((key1.find(key2) != string::npos) || (key1.length() > key2.length()))
	{
		return true;
	}
	return false;
}

void SwapKeys(int keyIndex1, int keyIndex2, vector<string> &keys)
{
	string tmp = keys[keyIndex1];
	keys.erase(keys.begin() + keyIndex1, keys.begin() + keyIndex1 + 1);
	keys.insert(keys.begin() + keyIndex2, tmp);
}

void SortKeys(vector<string> &keys)
{	
	int keysCount = keys.size();
	int swapCount;
	do
	{
		swapCount = 0;
		for (int i = 0; i < keysCount - 1; i++)
		{
			for (int j = i + 1; j < keysCount; j++)
			{
				if (KeyCompare(keys[j], keys[i]))
				{
					SwapKeys(i, j, keys);
					swapCount++;
				}
			}
		}
	} while (swapCount > 0);
}

// the function constructs and returns sorted vector of a map keys
vector<string> GetSortedKeys(map<string, string> const &m)
{
	vector<string> keys;
	for (map<string, string>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		keys.push_back(it->first);
	}
	SortKeys(keys);

	return keys;
}

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	string result = tpl;
	string mask (result.length(), MASK_SYMBOL_OPENED_FOR_CHAGES);

	vector<string> keys = GetSortedKeys(params);
	
	for (vector<string>::const_iterator it = keys.begin(); it != keys.end(); it++)
	{
		Replace(result, *it, (params.find(*it)->second), mask);
	}

	return result;
}

void TestExpandTemplate()
{
	string tmpl = "-DQAABBCCCCCABC+";
	map<string, string> parametrs;
	parametrs["AA"] = "[aa]";
	parametrs["A"] = "[a]";
	parametrs["BB"] = "[bb]";
	parametrs["B"] = "[b]";
	parametrs["CC"] = "[cc]";
	parametrs["C"] = "[c]";
	parametrs["DQA"] = "[dqa]";
	assert(ExpandTemplate(tmpl, parametrs) == "-[dqa][a][bb][cc][cc][c][a][b][c]+");

	tmpl = "Строка с параметром {param} и слоПУСТОПУСТОвом ПУСТПУСТО";
	parametrs.clear();
	parametrs["{param}"] = "{1}";
	parametrs["ПУСТО"] = "";
	assert(ExpandTemplate(tmpl, parametrs) == "Строка с параметром {1} и словом ПУСТ");

	tmpl = "BBADC";
	parametrs.clear();
	parametrs["BB"] = "A";
	parametrs["AA"] = "\\\\";
	parametrs["A"] = "1";
	assert(ExpandTemplate(tmpl, parametrs) == "A1DC");

	tmpl = "";
	// parametrs == last parametrs
	assert(ExpandTemplate(tmpl, parametrs) == "");

	// tmpl = ""
	parametrs.clear();
	assert(ExpandTemplate(tmpl, parametrs) == "");

	tmpl = "Что-то есть";
	// parametrs.clear();
	assert(ExpandTemplate(tmpl, parametrs) == "Что-то есть");

	cout << "ExpandTemplate have passed the test";
}