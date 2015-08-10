#include "stdafx.h"
#include <string>
#include "..\bodies\Cone.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CCone_object)

	BOOST_AUTO_TEST_SUITE(can_be_createad)
		BOOST_AUTO_TEST_CASE(with_positive_density_height_and_radius)
		{
			CCone cone(10.0, 20.0, 200.0);
			BOOST_CHECK_CLOSE(cone.GetDensity(), 10.0, 0.001);
			BOOST_CHECK_CLOSE(cone.GetMass(), (cone.GetVolume() * 10), 0.001);
			BOOST_CHECK_CLOSE(cone.GetVolume(), (M_PI * 400 * 200 / 3), 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_mass)
		{
			CCone cone(0.0, 20.0, 200.0);
			BOOST_CHECK_EQUAL(cone.GetDensity(), 0.0);
			BOOST_CHECK_CLOSE(cone.GetMass(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_volume)
		{
			CCone cone1(10.0, 0.0, 200.0);
			BOOST_CHECK_CLOSE(cone1.GetVolume(), 0.0, 0.001);

			CCone cone2(10.0, 20.0, 0.0);
			BOOST_CHECK_CLOSE(cone2.GetVolume(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_negative_arguments)
		{
			CCone cone(-10.0, -15.0, -2.0);
			BOOST_CHECK_CLOSE(cone.GetDensity(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(cone.GetMass(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(cone.GetVolume(), 0.0, 0.001);
		}
	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_CASE(has_valid_string_description)
	{
		CCone cone(10.0, 20.0, 200.0);

		ostringstream expectedDescription;
		expectedDescription.setf(ios::fixed);
		expectedDescription.precision(6);

		expectedDescription << "Cone:\n";
		expectedDescription << "	Radius  = " << 20.0 << "\n";
		expectedDescription << "	Height  = " << 200.0 << "\n";
		expectedDescription << "	Mass    = " << cone.GetMass() << "\n";
		expectedDescription << "	Volume  = " << cone.GetVolume() << "\n";
		expectedDescription << "	Density = " << cone.GetDensity();
		BOOST_CHECK_EQUAL(cone.ToString(), expectedDescription.str());
	}

BOOST_AUTO_TEST_SUITE_END()