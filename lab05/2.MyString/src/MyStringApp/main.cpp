// MyStringApp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyString.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CMyString strEmpty("");
	CMyString str1Sym("a");
	CMyString strManySyms("it's a word-phrase");
	CMyString strMoved("");
	strEmpty = std::move(strMoved);
	CMyString const constStr("This is constant");
	
	auto itc = constStr.begin();
	++itc;
	std::cout << *(++itc);
	
	CMyString strToWrite(constStr);
	for (auto ch : strToWrite)
	{
		std::cout << ch;
	}
	
	return 0;
}

