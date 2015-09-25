#include "stdafx.h"
#include "../addrbook/Subscriber.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CSubscriber_)

	void CheckSubscriberProperties(CSubscriber const &subscriber,
		string const &name,
		CPostAddress const &address,
		vector<string> const &phones,
		vector<string> const &emails)
	{
		BOOST_CHECK_EQUAL(string(subscriber.GetName()), name);
		BOOST_CHECK_EQUAL(subscriber.GetAddress().GetCity(), address.GetCity());
		BOOST_CHECK_EQUAL(subscriber.GetAddress().GetStreet(), address.GetStreet());
		BOOST_CHECK_EQUAL(subscriber.GetAddress().GetHouse(), address.GetHouse());
		BOOST_CHECK_EQUAL(subscriber.GetAddress().GetApartment(), address.GetApartment());
		BOOST_CHECK(subscriber.GetPhones() == phones);
		BOOST_CHECK(subscriber.GetEmails() == emails);
	}
	BOOST_AUTO_TEST_CASE(can_be_created_and_get_properties)
	{
		CSubscriber subscriber1("name");
		CheckSubscriberProperties(subscriber1, "name", CPostAddress(), vector<string>(), vector<string>());

		CSubscriber subscriber2("name", CPostAddress("City"), { "112211" }, { "e@ma.il" });
		CheckSubscriberProperties(subscriber2, "name", CPostAddress("City"), { "112211" }, { "e@ma.il" });

		BOOST_CHECK_THROW(CSubscriber(""), invalid_argument);
	}


	BOOST_AUTO_TEST_CASE(can_set_properties)
	{
		CSubscriber subscriber("name");
		subscriber.SetName("new name");
		subscriber.SetAddress(CPostAddress("New City"));
		subscriber.SetPhones({ "11", "22", "33" });
		subscriber.SetEmails({ "ema@i.l, e@m.ail" });
		CheckSubscriberProperties(subscriber, "new name", CPostAddress("New City"), { "11", "22", "33" }, { "ema@i.l, e@m.ail" });

		BOOST_CHECK_THROW(subscriber.SetName(""), invalid_argument);
	}


	BOOST_AUTO_TEST_CASE(can_be_checked_on_match)
	{
		CSubscriber subscriber("Name", CPostAddress("City", "Street"), { "ph1", "ph2" }, { "em1", "em2", "em3" });
		BOOST_CHECK(subscriber.Match("NaME", CPostAddress(), vector<string>(), {"em1", "em3"}));
		BOOST_CHECK(!subscriber.Match("NaME", CPostAddress(), { "33 korovy" }, { "em1", "em3" }));
	}

BOOST_AUTO_TEST_SUITE_END()