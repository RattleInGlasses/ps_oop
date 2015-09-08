#include "stdafx.h"
#include "..\MySet\MySet.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CMySet_)
	
	BOOST_AUTO_TEST_CASE(empty_by_default)
	{
		BOOST_CHECK(CMySet<int>().IsEmpty());
		BOOST_CHECK(CMySet<string>().IsEmpty());
		BOOST_CHECK(CMySet<char>().IsEmpty());
	}


	BOOST_AUTO_TEST_CASE(can_be_created_from_initializer_list)
	{
		CMySet<char> set1 = { 'a', 'b', 'c' };
		BOOST_CHECK_EQUAL(set1.GetSize(), 3);
		BOOST_CHECK(set1.Contains('a'));
		BOOST_CHECK(set1.Contains('b'));
		BOOST_CHECK(set1.Contains('c'));
	}


	BOOST_AUTO_TEST_CASE(can_get_size)
	{
		BOOST_CHECK_EQUAL((CMySet<int> { 12 }).GetSize(), 1);
		BOOST_CHECK_EQUAL((CMySet<int> { 12, -2, 3, 4, 5 }).GetSize(), 5);
	}


	struct CreatedIntSet
	{
		CMySet<int> intSet;
	};
	void CheckAddElement(CMySet<int> &set, int el)
	{
		BOOST_REQUIRE(!set.Contains(el));
		set.Add(el);
		BOOST_CHECK(set.Contains(el));
	}
	BOOST_FIXTURE_TEST_CASE(can_add_an_element, CreatedIntSet)
	{
		CheckAddElement(intSet, 25);
		CheckAddElement(intSet, -23);
	}


	BOOST_FIXTURE_TEST_CASE(can_get_any_element, CreatedIntSet)
	{
		intSet = { 10, 11, 12, 13 };
		BOOST_CHECK_EQUAL(10, intSet[0]);
		BOOST_CHECK_EQUAL(11, intSet[1]);
		BOOST_CHECK_EQUAL(12, intSet[2]);
		BOOST_CHECK_EQUAL(13, intSet[3]);
	}


	BOOST_FIXTURE_TEST_CASE(can_be_checked_on_empty, CreatedIntSet)
	{
		BOOST_CHECK(intSet.IsEmpty());

		intSet = { 12 };
		BOOST_CHECK(!intSet.IsEmpty());

		intSet = {};
		BOOST_CHECK(intSet.IsEmpty());

		intSet.Add(12);
		BOOST_CHECK(!intSet.IsEmpty());
	}


	BOOST_FIXTURE_TEST_CASE(can_check_element, CreatedIntSet)
	{
		intSet.Add(12);
		intSet.Add(24);

		BOOST_CHECK(intSet.Contains(12));
		BOOST_CHECK(intSet.Contains(24));
		BOOST_CHECK(!intSet.Contains(32));
	}


	BOOST_AUTO_TEST_CASE(can_check_subset)
	{		
		BOOST_CHECK((CMySet<int>()).ContainsSubset(CMySet<int>()));
		BOOST_CHECK((CMySet<int> { 12 }).ContainsSubset(CMySet<int>()));
		BOOST_CHECK((CMySet<int> { 12, 24, 32}).ContainsSubset({ 12, 32 }));
		BOOST_CHECK(!(CMySet<int> { 12, 24 }).ContainsSubset({ 23 }));
	}


	BOOST_FIXTURE_TEST_CASE(can_be_tested_to_equality, CreatedIntSet)
	{
		BOOST_CHECK(CMySet<int>() == CMySet<int>());
		BOOST_CHECK(!(CMySet<int>() == CMySet<int> { 1 }));
		BOOST_CHECK(!(CMySet<int> { 1 } == CMySet<int>()));
		BOOST_CHECK(CMySet<int> { 1 } == CMySet<int> { 1 });
		BOOST_CHECK(!(CMySet<int> { 1 } == CMySet<int> { 3 }));
		BOOST_CHECK((CMySet<int> { 1, 2 }) == (CMySet<int> { 1, 2 }));
		BOOST_CHECK(!((CMySet<int> { 1, 2 }) == (CMySet<int> { 1, 2, 3 })));
		BOOST_CHECK(!((CMySet<int> { 1, 2, 3 }) == (CMySet<int> { 1, 2 })));
	}


	BOOST_FIXTURE_TEST_CASE(can_unite_another_set, CreatedIntSet)
	{
		intSet.Unite(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int>());

		intSet.Unite(CMySet<int> { 21 });
		BOOST_CHECK(intSet == CMySet<int> { 21 });

		intSet = { 11, 22 };
		intSet.Unite(CMySet<int> { 33, 44 });
		BOOST_CHECK(intSet == (CMySet<int> { 11, 22, 33, 44 }));

		intSet = { 11, 22, 33 };
		intSet.Unite(CMySet<int> { 22, 33, 44 });
		BOOST_CHECK(intSet == (CMySet<int> { 11, 22, 33, 44 }));
	}


	BOOST_FIXTURE_TEST_CASE(can_intersect_another_set, CreatedIntSet)
	{
		intSet.Intersect(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int>());

		intSet.Intersect(CMySet<int> { 12 });
		BOOST_CHECK(intSet == CMySet<int>());

		intSet = { 12 };
		intSet.Intersect(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int>());

		intSet = { 12, 24 };
		intSet.Intersect((CMySet<int> { 12, 48 }));
		BOOST_CHECK(intSet == CMySet<int> { 12 });
	}


	BOOST_FIXTURE_TEST_CASE(can_find_difference_with_another_set, CreatedIntSet)
	{
		intSet.Difference(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int>());

		intSet.Difference({ 12 });
		BOOST_CHECK(intSet == CMySet<int>());

		intSet = { 11 };
		intSet.Difference(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int> { 11 });

		intSet = { 11, 12 };
		intSet.Difference({ 12, 13 });
		BOOST_CHECK(intSet == CMySet<int> { 11 });
	}


	BOOST_FIXTURE_TEST_CASE(can_find_symmetric_difference_with_another_set, CreatedIntSet)
	{
		intSet.SymmetricDyfference(CMySet<int>());
		BOOST_CHECK(intSet == CMySet<int>());

		intSet.SymmetricDyfference({ 12 });
		BOOST_CHECK(intSet == CMySet<int> { 12 });

		intSet = { 11, 12 };
		intSet.SymmetricDyfference({ 12, 13 });
		BOOST_CHECK(intSet == (CMySet<int> { 11, 13 }));
	}

BOOST_AUTO_TEST_SUITE_END()