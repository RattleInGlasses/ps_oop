#include "stdafx.h"
#include "..\rational\MyMath.h"

using namespace MyMath;

BOOST_AUTO_TEST_SUITE(MyMath_tests)

	BOOST_AUTO_TEST_SUITE(GreatesCommonDivisor_)
		BOOST_AUTO_TEST_CASE(can_process_postive_ints)
		{
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(18, 45), 9);
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(45, 45), 45);
		}

		BOOST_AUTO_TEST_CASE(can_process_negative_ints)
		{
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(-18, 45), 9);
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(18, -45), 9);
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(-18, -45), 9);
		}

		BOOST_AUTO_TEST_CASE(can_process_one_zero)
		{
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(0, 45), 45);
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(45, 0), 45);
		}

		BOOST_AUTO_TEST_CASE(return_error_on_both_zero)
		{
			BOOST_CHECK_EQUAL(GreatesCommonDivisor(0, 0), -1);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(LeastCommonMultiple_)
		BOOST_AUTO_TEST_CASE(can_process_postive_ints)
		{
			BOOST_CHECK_EQUAL(LeastCommonMultiple(25, 5), 25);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(25, 25), 25);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(7, 5), 35);
		}

		BOOST_AUTO_TEST_CASE(can_process_negative_ints)
		{
			BOOST_CHECK_EQUAL(LeastCommonMultiple(-7, 5), 35);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(7, -5), 35);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(-7, -5), 35);
		}

		BOOST_AUTO_TEST_CASE(return_error_on_at_least_one_zero)
		{
			BOOST_CHECK_EQUAL(LeastCommonMultiple(0, 0), -1);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(9, 0), -1);
			BOOST_CHECK_EQUAL(LeastCommonMultiple(0, 9), -1);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()