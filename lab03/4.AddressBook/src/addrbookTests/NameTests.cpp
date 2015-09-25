#include "stdafx.h"
#include "../addrbook/Name.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CName_)

	BOOST_AUTO_TEST_SUITE(can_be_created)
		BOOST_AUTO_TEST_CASE(empty_by_default)
		{
			CName name;
			BOOST_CHECK_EQUAL(string(name), "");
		}

		BOOST_AUTO_TEST_CASE(from_string)
		{
			CName name1(string(""));
			BOOST_CHECK_EQUAL(string(name1), "");

			CName name2(string("from_string"));
			BOOST_CHECK_EQUAL(string(name2), "from_string");
		}

		BOOST_AUTO_TEST_CASE(from_cstring)
		{
			CName name1("");
			BOOST_CHECK_EQUAL(string(name1), "");

			CName name2("from_cstring");
			BOOST_CHECK_EQUAL(string(name2), "from_cstring");
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_CASE(can_assign_string)
	{
		CName name;
		name = string("new value");
		BOOST_CHECK_EQUAL(string(name), "new value");
	}


	BOOST_AUTO_TEST_CASE(can_be_checked_on_match_by_string)
	{
		CName name = "Ivanov Ivan";
		BOOST_CHECK(name.Match("ivaNOv"));
		BOOST_CHECK(name.Match("ivaN"));
		BOOST_CHECK(name.Match("IvAn IvaNOv"));
		BOOST_CHECK(name.Match("Ivanov Ivan"));
		BOOST_CHECK(!name.Match("Ivan Ivanov Ivan"));
		BOOST_CHECK(!name.Match("Ivanov Ivan Petrovich"));
	}

BOOST_AUTO_TEST_SUITE_END()