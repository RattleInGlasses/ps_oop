// addrbook.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Name.h"
#include "PostAddress.h"
#include "Subscriber.h"
#include "AddressBook.h"
#include "MenuCLI.h"

using namespace std;

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	CMenuCLI menu(cin, cout);
	CAddressBook addressBook;	

	addressBook.LoadSubsribers("test.txt");

	menu.Start(addressBook);

	addressBook.SaveSubsribers("testout.txt");
	
	return 0;
}

