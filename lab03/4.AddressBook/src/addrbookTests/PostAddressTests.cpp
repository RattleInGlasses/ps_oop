#include "stdafx.h"
#include "../addrbook/PostAddress.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CPostAddress_)

	BOOST_AUTO_TEST_SUITE(can_be_created_and_get_properties)
		BOOST_AUTO_TEST_CASE(empty_by_default)
		{
			CPostAddress addr;
			BOOST_CHECK_EQUAL(addr.GetCity(), "");
			BOOST_CHECK_EQUAL(addr.GetStreet(), "");
			BOOST_CHECK_EQUAL(addr.GetHouse(), "");
			BOOST_CHECK_EQUAL(addr.GetApartment(), 0);
		}

		BOOST_AUTO_TEST_CASE(with_predefinded_properties)
		{
			CPostAddress addr1("City1", "Street1", "1h", 10);
			BOOST_CHECK_EQUAL(addr1.GetCity(), "City1");
			BOOST_CHECK_EQUAL(addr1.GetStreet(), "Street1");
			BOOST_CHECK_EQUAL(addr1.GetHouse(), "1h");
			BOOST_CHECK_EQUAL(addr1.GetApartment(), 10);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_CASE(can_set_properties)
	{
		CPostAddress addr;
		addr.SetCity("City1");
		addr.SetStreet("Street1");
		addr.SetHouse("1h");
		addr.SetApartment(10);
		BOOST_CHECK_EQUAL(addr.GetCity(), "City1");
		BOOST_CHECK_EQUAL(addr.GetStreet(), "Street1");
		BOOST_CHECK_EQUAL(addr.GetHouse(), "1h");
		BOOST_CHECK_EQUAL(addr.GetApartment(), 10);

	}


	BOOST_AUTO_TEST_CASE(can_be_checked_on_match)
	{
		CPostAddress addr("City", "Street", "1h", 10);
		CPostAddress emptyAddr;
		CPostAddress cityAddr("City");
		CPostAddress streetAddr("", "Street");
		CPostAddress houseAddr("", "", "1h");
		CPostAddress apartmentAddr("", "", "", 10);
		CPostAddress cityStreetAddr("ciTy", "stREET");
		CPostAddress streetHouseApartmentAddr("", "street", "1H", 10);
		BOOST_CHECK(addr.Match(emptyAddr));
		BOOST_CHECK(addr.Match(cityAddr));
		BOOST_CHECK(addr.Match(streetAddr));
		BOOST_CHECK(addr.Match(houseAddr));
		BOOST_CHECK(addr.Match(apartmentAddr));
		BOOST_CHECK(addr.Match(cityStreetAddr));
		BOOST_CHECK(addr.Match(streetHouseApartmentAddr));
	}

BOOST_AUTO_TEST_SUITE_END()