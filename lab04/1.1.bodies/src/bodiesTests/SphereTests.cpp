#include "stdafx.h"
#include "..\bodies\Sphere.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CSphere_object)

	BOOST_AUTO_TEST_SUITE(can_be_createad)
		BOOST_AUTO_TEST_CASE(with_positive_density_and_radius)
		{
			CSphere sphere(10.0, 15.0);
			BOOST_CHECK_CLOSE(sphere.GetDensity(), 10.0, 0.001);
			BOOST_CHECK_CLOSE(sphere.GetMass(), ((M_PI * 15 * 15 * 15 * 4 / 3) * 10), 0.001);
			BOOST_CHECK_CLOSE(sphere.GetVolume(), (M_PI * 15 * 15 * 15 * 4 / 3), 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_mass)
		{
			CSphere sphere(0.0, 15.0);
			BOOST_CHECK_EQUAL(sphere.GetDensity(), 0.0);
			BOOST_CHECK_CLOSE(sphere.GetMass(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_volume)
		{
			CSphere sphere(10.0, 0.0);
			BOOST_CHECK_CLOSE(sphere.GetVolume(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_negative_arguments)
		{
			CSphere sphere(-10.0, -15.0);
			BOOST_CHECK_CLOSE(sphere.GetDensity(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(sphere.GetMass(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(sphere.GetVolume(), 0.0, 0.001);
		}
	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_CASE(has_valid_string_description)
	{
		CSphere sphere(10.0, 15.0);

		ostringstream expectedDescription;
		expectedDescription.setf(ios::fixed);
		expectedDescription.precision(6);

		expectedDescription << "Sphere:\n";
		expectedDescription << "	Radius  = " << 15.0 << "\n";
		expectedDescription << "	Mass    = " << sphere.GetMass() << "\n";
		expectedDescription << "	Volume  = " << sphere.GetVolume() << "\n";
		expectedDescription << "	Density = " << sphere.GetDensity();
		BOOST_CHECK_EQUAL(sphere.ToString(), expectedDescription.str());
	}

BOOST_AUTO_TEST_SUITE_END()