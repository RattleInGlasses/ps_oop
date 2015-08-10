#include "stdafx.h"
#include <string>
#include "..\bodies\Parallelepiped.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CParallelepiped_object)

	BOOST_AUTO_TEST_SUITE(can_be_createad)
		BOOST_AUTO_TEST_CASE(with_positive_density_and_dimensions)
		{
			CParallelepiped parallelepiped(10.0, 200.0, 20.0, 10.0);
			BOOST_CHECK_CLOSE(parallelepiped.GetDensity(), 10.0, 0.001);
			BOOST_CHECK_CLOSE(parallelepiped.GetMass(), 400000.0, 0.001);
			BOOST_CHECK_CLOSE(parallelepiped.GetVolume(), 40000.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_mass)
		{
			CParallelepiped parallelepiped(0.0, 200.0, 20.0, 10.0);
			BOOST_CHECK_EQUAL(parallelepiped.GetDensity(), 0.0);
			BOOST_CHECK_CLOSE(parallelepiped.GetMass(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_volume)
		{
			CParallelepiped parallelepiped1(10.0, 0.0, 20.0, 10.0);
			BOOST_CHECK_CLOSE(parallelepiped1.GetVolume(), 0.0, 0.001);

			CParallelepiped parallelepiped2(10.0, 200.0, 0.0, 10.0);
			BOOST_CHECK_CLOSE(parallelepiped2.GetVolume(), 0.0, 0.001);

			CParallelepiped parallelepiped3(10.0, 200.0, 20.0, 0.0);
			BOOST_CHECK_CLOSE(parallelepiped3.GetVolume(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_negative_arguments)
		{
			CParallelepiped parallelepiped(-10.0, -15.0, -2.0, -3.1);
			BOOST_CHECK_CLOSE(parallelepiped.GetDensity(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(parallelepiped.GetMass(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(parallelepiped.GetVolume(), 0.0, 0.001);
		}
	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_CASE(has_valid_string_description)
	{
		CParallelepiped parallelepiped(10.0, 200.0, 20.0, 10.0);

		ostringstream expectedDescription;
		expectedDescription.setf(ios::fixed);
		expectedDescription.precision(6);

		expectedDescription << "Parallelepiped:\n";
		expectedDescription << "	Width   = " << 200.0 << "\n";
		expectedDescription << "	Height  = " << 20.0 << "\n";
		expectedDescription << "	Depth   = " << 10.0 << "\n";
		expectedDescription << "	Mass    = " << parallelepiped.GetMass() << "\n";
		expectedDescription << "	Volume  = " << parallelepiped.GetVolume() << "\n";
		expectedDescription << "	Density = " << parallelepiped.GetDensity();

		BOOST_CHECK_EQUAL(parallelepiped.ToString(), expectedDescription.str());
	}

BOOST_AUTO_TEST_SUITE_END()