// addrbook.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Name.h"
#include "PostAddress.h"
#include "Subscriber.h"
#include "AddressBook.h"
#include "MenuCLI.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CMenuCLI menu(cin, cout);
	
	menu.Start(CAddressBook());
	
	return 0;
}

