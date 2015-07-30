#include "stdafx.h"

char const MASK_SYMBOL_OPENED_FOR_CHAGES = ' ';
char const MASK_SYMBOL_CLOSED_FOR_CHAGES = 'X';

using namespace std;

boost::optional<size_t> GetFirstClosedSymbolPosition(string const &mask, size_t startPos, size_t len)
{
	size_t result = distance(mask.begin(), find(mask.begin() + startPos, mask.begin() + startPos + len, MASK_SYMBOL_CLOSED_FOR_CHAGES));
	if (result >= startPos + len)
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
string Replace(string const &str, string const &searchStr, string const &replaceStr, string &mask)
{
	size_t searchFrom = 0;
	size_t pos = str.find(searchStr, searchFrom);
	boost::optional<size_t> firstClosedSymbolPosition;
	string result;
	result.reserve(str.length());
	size_t lastReplacePos = 0;

	string newMask; newMask.reserve(mask.length());
	while (pos < str.length())//(pos != string::npos)
	{
		if (firstClosedSymbolPosition = GetFirstClosedSymbolPosition(mask, pos, searchStr.length()))                   // check found substring, using mask                                               
		{
			// if we have found a char that is not meant to be changed then search again starting from a char next to the founded
			searchFrom = *firstClosedSymbolPosition + 1;
		}
		else
		{
			result += str.substr(lastReplacePos, pos - lastReplacePos);
			result += replaceStr;

			newMask += mask.substr(lastReplacePos, pos - lastReplacePos);
			newMask.append(replaceStr.length(), MASK_SYMBOL_CLOSED_FOR_CHAGES);

			lastReplacePos = pos + searchStr.length();
			searchFrom = pos + searchStr.length();
		}
		pos = str.find(searchStr, searchFrom);
	}

	newMask += mask.substr(lastReplacePos);
	swap(mask, newMask);
	return result + str.substr(lastReplacePos);
}


// the function returns true if key1 should go before key2 (key1Index < key2Index)
bool KeyCompare(string const &key1, string const &key2)
{
	if ((key1.find(key2) != string::npos) || (key1.length() > key2.length()))
	{
		return true;
	}
	return false;
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
					swap(keys[j], keys[i]);
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
	string mask(tpl.length(), MASK_SYMBOL_OPENED_FOR_CHAGES);

	vector<string> keys = GetSortedKeys(params);
	
	string result = tpl;
	for (vector<string>::const_iterator it = keys.begin(); it != keys.end(); it++)
	{
		result = Replace(result, *it, (params.find(*it)->second), mask);
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

	tmpl = "	return false;";
	assert(ExpandTemplate(tmpl, {
		{ "true", "false" },
		{ "false", "true" }
	}) == "	return true;");

	cout << "ExpandTemplate have passed the test" << endl;
}