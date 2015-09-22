#include "stdafx.h"
#include "..\Persons\Company.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CCompany_)

	BOOST_AUTO_TEST_CASE(can_be_created_and_get_properties)
	{
		CCompany comp1("UNI");
		BOOST_CHECK_EQUAL(comp1.GetName(), "UNI");
		BOOST_CHECK_EQUAL(comp1.GetWebsite(), "");

		CCompany comp2("MGU", "website");
		BOOST_CHECK_EQUAL(comp2.GetName(), "MGU");
		BOOST_CHECK_EQUAL(comp2.GetWebsite(), "website");
	}


	BOOST_AUTO_TEST_CASE(can_set_name)
	{
		CCompany comp("FGU");
		comp.SetName("FFF");
		BOOST_CHECK_EQUAL(comp.GetName(), "FFF");

		BOOST_CHECK_THROW(comp.SetName(""), invalid_argument);
	}


	BOOST_AUTO_TEST_CASE(can_set_website)
	{
		CCompany comp("FGU");
		comp.SetWebsite("website");
		BOOST_CHECK_EQUAL(comp.GetWebsite(), "website");
	}

BOOST_AUTO_TEST_SUITE_END()