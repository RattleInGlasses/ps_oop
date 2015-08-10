#include "stdafx.h"
#include "..\bodies\Cylinder.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CCylinder_object)

	BOOST_AUTO_TEST_SUITE(can_be_createad)
		BOOST_AUTO_TEST_CASE(with_positive_density_height_and_radius)
		{
			CCylinder cylinder(10.0, 20.0, 200.0);
			BOOST_CHECK_CLOSE(cylinder.GetDensity(), 10.0, 0.001);
			BOOST_CHECK_CLOSE(cylinder.GetMass(), (cylinder.GetVolume() * 10), 0.001);
			BOOST_CHECK_CLOSE(cylinder.GetVolume(), (M_PI * 400 * 200), 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_mass)
		{
			CCylinder cylinder(0.0, 20.0, 200.0);
			BOOST_CHECK_EQUAL(cylinder.GetDensity(), 0.0);
			BOOST_CHECK_CLOSE(cylinder.GetMass(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_zero_volume)
		{
			CCylinder cylinder1(10.0, 0.0, 200.0);
			BOOST_CHECK_CLOSE(cylinder1.GetVolume(), 0.0, 0.001);

			CCylinder cylinder2(10.0, 20.0, 0.0);
			BOOST_CHECK_CLOSE(cylinder2.GetVolume(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_negative_arguments)
		{
			CCylinder cylinder(-10.0, -15.0, -2.0);
			BOOST_CHECK_CLOSE(cylinder.GetDensity(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(cylinder.GetMass(), 0.0, 0.001);
			BOOST_CHECK_CLOSE(cylinder.GetVolume(), 0.0, 0.001);
		}
	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_CASE(has_valid_string_description)
	{
		CCylinder cylinder(10.0, 20.0, 200.0);

		ostringstream expectedDescription;
		expectedDescription.setf(ios::fixed);
		expectedDescription.precision(6);

		expectedDescription << "Cylinder:\n";
		expectedDescription << "	Radius  = " << 20.0 << "\n";
		expectedDescription << "	Height  = " << 200.0 << "\n";
		expectedDescription << "	Mass    = " << cylinder.GetMass() << "\n";
		expectedDescription << "	Volume  = " << cylinder.GetVolume() << "\n";
		expectedDescription << "	Density = " << cylinder.GetDensity();
		BOOST_CHECK_EQUAL(cylinder.ToString(), expectedDescription.str());
	}

BOOST_AUTO_TEST_SUITE_END()