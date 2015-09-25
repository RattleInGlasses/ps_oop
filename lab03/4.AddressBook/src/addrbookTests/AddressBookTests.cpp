#include "stdafx.h"
#include "../addrbook/AddressBook.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CAddressBook_)

	BOOST_AUTO_TEST_CASE(can_be_created_empty)
	{
		CAddressBook adb;
		BOOST_CHECK(adb.FindSubscribers() == vector<size_t>());
	}


	struct CreatedBook
	{
		CAddressBook adb;
	};
	BOOST_FIXTURE_TEST_CASE(can_add_subscriber, CreatedBook)
	{
		adb.AddSubscriber(CSubscriber("sub"));
		vector<size_t> expectedResult = { 0 };
		BOOST_CHECK(adb.FindSubscribers() == expectedResult);
	}


	struct BookWithSubscribers : CreatedBook
	{
		BookWithSubscribers()
		{
			adb.AddSubscriber(CSubscriber("sub1"));
			adb.AddSubscriber(CSubscriber("sub2"));
			adb.AddSubscriber(CSubscriber("sub1"));
		}
	};
	BOOST_FIXTURE_TEST_CASE(can_delete_subscriber, BookWithSubscribers)
	{
		adb.DeleteSubscriber(1);
		BOOST_CHECK_EQUAL(string(adb[1].GetName()), "sub1");
	}


	BOOST_FIXTURE_TEST_CASE(can_get_subscriber, BookWithSubscribers)
	{
		BOOST_CHECK_EQUAL(string(adb[0].GetName()), "sub1");
		BOOST_CHECK_EQUAL(string(adb[1].GetName()), "sub2");
		BOOST_CHECK_EQUAL(string(adb[2].GetName()), "sub1");
	}


	BOOST_FIXTURE_TEST_CASE(can_find_subscribers, BookWithSubscribers)
	{
		vector<size_t> expectedResult1 = { 0, 2 };
		BOOST_CHECK(adb.FindSubscribers("sub1") == expectedResult1);

		vector<size_t> expectedResult2 = { 0, 1, 2 };
		BOOST_CHECK(adb.FindSubscribers() == expectedResult2);
	}

BOOST_AUTO_TEST_SUITE_END()