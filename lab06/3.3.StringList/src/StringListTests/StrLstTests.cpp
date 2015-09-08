#include "stdafx.h"
#include "..\StringList\StrLst.h"
#include <vld.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(StrLst_)
	
	BOOST_AUTO_TEST_CASE(empty_when_created)
	{
		CStrLst sList;
		BOOST_CHECK(sList.begin() == sList.end());
	}


	struct EmptyList
	{
		CStrLst sList;
		string str = "test string";
	};
	BOOST_FIXTURE_TEST_SUITE(can_get_first_element, EmptyList)
		BOOST_AUTO_TEST_CASE(from_list_with_one_element)
		{
			sList.Insert(str, sList.begin());
			BOOST_CHECK_EQUAL(str, *(sList.begin()));
		}

		BOOST_AUTO_TEST_CASE(from_list_with_three_elements)
		{
			sList.Insert(str, sList.end());
			sList.Insert("smth", sList.end());
			sList.Insert("else", sList.end());
			BOOST_CHECK_EQUAL(str, *(sList.begin()));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(can_get_last_element, EmptyList)
		BOOST_AUTO_TEST_CASE(from_list_with_one_element)
		{
			sList.Insert(str, sList.end());
			BOOST_CHECK_EQUAL(str, *(--sList.end()));
		}
		
		BOOST_AUTO_TEST_CASE(from_list_with_three_elements)
		{
			sList.Insert(str, sList.begin());
			sList.Insert("two", sList.begin());
			sList.Insert("more", sList.begin());
			BOOST_CHECK_EQUAL(str, *(--sList.end()));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct TwoElementsList : EmptyList
	{
		TwoElementsList()
		{
			sList.Insert("first", sList.end());
			sList.Insert("second", sList.end());
		}
	};
	BOOST_AUTO_TEST_SUITE(can_insert_element)
		BOOST_FIXTURE_TEST_CASE(into_empty_list, EmptyList)
		{
			sList.Insert(str, sList.end());
			BOOST_CHECK_EQUAL(str, *(--sList.end()));
		}

		BOOST_FIXTURE_TEST_SUITE(into_non_empty_list, TwoElementsList)
			BOOST_AUTO_TEST_CASE(after_last)
			{
				sList.Insert(str, sList.end());
				BOOST_CHECK_EQUAL(str, *(--sList.end()));
			}

			BOOST_AUTO_TEST_CASE(before_first)
			{
				sList.Insert(str, sList.begin());
				BOOST_CHECK_EQUAL(str, *(sList.begin()));
			}

			BOOST_AUTO_TEST_CASE(into_the_middle)
			{
				sList.Insert(str, ++sList.begin());
				BOOST_CHECK_EQUAL(str, *(++sList.begin()));
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	struct ThreeElementsList : TwoElementsList
	{
		ThreeElementsList()
		{
			sList.Insert("third", sList.end());
		}
	};
	BOOST_FIXTURE_TEST_SUITE(can_delete_element, ThreeElementsList)
		BOOST_AUTO_TEST_CASE(first)
		{
			string elem = *(++sList.begin());
			sList.Delete(sList.begin());
			BOOST_CHECK_EQUAL(elem, *(sList.begin()));
		}

		BOOST_AUTO_TEST_CASE(last)
		{
			string elem = *(--(--sList.end()));
			sList.Delete(--sList.end());
			BOOST_CHECK_EQUAL(elem, *(--sList.end()));
		}

		BOOST_AUTO_TEST_CASE(middle)
		{
			string elem = *(++(++sList.begin()));
			sList.Delete(++sList.begin());
			BOOST_CHECK_EQUAL(elem, *(++sList.begin()));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_CASE(cant_delete_end, ThreeElementsList)
	{
		CStrLst::iterator it = sList.end();
		sList.Delete(sList.end());
		BOOST_CHECK(it == sList.end());
	}

BOOST_AUTO_TEST_SUITE_END()