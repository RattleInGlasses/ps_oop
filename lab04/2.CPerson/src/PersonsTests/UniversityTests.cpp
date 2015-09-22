#include "stdafx.h"
#include "..\Persons\University.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CUniversity_)
	
	BOOST_AUTO_TEST_CASE(can_be_created_and_get_name)
	{
		CUniversity university1("UNI");
		BOOST_CHECK_EQUAL(university1.GetName(), "UNI");

		CUniversity university2("MGU");
		BOOST_CHECK_EQUAL(university2.GetName(), "MGU");
	}

	BOOST_AUTO_TEST_CASE(can_set_name)
	{
		CUniversity university("FGU");
		university.SetName("FFF");
		BOOST_CHECK_EQUAL(university.GetName(), "FFF");

		BOOST_CHECK_THROW(university.SetName(""), invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()