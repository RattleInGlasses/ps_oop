#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(Simple_tests)

	BOOST_AUTO_TEST_CASE(are_running)
	{
		BOOST_CHECK_SMALL(0.00001, 0.1);
	}
	
BOOST_AUTO_TEST_SUITE_END()