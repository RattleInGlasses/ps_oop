#include "stdafx.h"
#include <string>
#include "..\bodies\Compound.h"
#include "..\bodies\Cone.h"
#include "..\bodies\Cylinder.h"
#include "..\bodies\Parallelepiped.h"
#include "..\bodies\Sphere.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CCompound_object)

	BOOST_AUTO_TEST_CASE(can_be_created)
	{
		CCompound compound;
		BOOST_CHECK(compound.ToString() != "");
	}
	
	struct createdCompound
	{
		CCompound compound;
	};
	BOOST_FIXTURE_TEST_SUITE(has_init_state, createdCompound)
		BOOST_AUTO_TEST_CASE(with_zero_density)
		{
			BOOST_CHECK_EQUAL(compound.GetDensity(), 0);
		}

		BOOST_AUTO_TEST_CASE(with_zero_mass)
		{
			BOOST_CHECK_EQUAL(compound.GetMass(), 0);
		}

		BOOST_AUTO_TEST_CASE(with_zero_volume)
		{
			BOOST_CHECK_EQUAL(compound.GetVolume(), 0);
		}

		BOOST_AUTO_TEST_CASE(with_valid_string_description)
		{
			string expectedDescription;
			expectedDescription += "Compound:\n";
			expectedDescription += "	empty\n";
			expectedDescription += "	Aggregate Mass   = 0.000000\n";
			expectedDescription += "	Aggregate Volume = 0.000000\n";
			expectedDescription += "	Average Density  = 0.000000";
			BOOST_CHECK_EQUAL(compound.ToString(), expectedDescription);
		}
	BOOST_AUTO_TEST_SUITE_END()

	
	BOOST_FIXTURE_TEST_SUITE(can_add, createdCompound)
		BOOST_AUTO_TEST_CASE(solid_body)
		{
			BOOST_CHECK(compound.AddBody(make_shared<CCone>(0, 0, 0)));
		}

		BOOST_AUTO_TEST_CASE(compound_body)
		{
			BOOST_CHECK(compound.AddBody(make_shared<CCompound>()));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(have_valid_description, createdCompound)
	
		BOOST_AUTO_TEST_CASE(with_a_solid_body)
		{
			compound.AddBody(make_shared<CCone>(0, 0, 0));

			string expectedDescription;
			expectedDescription += "Compound:\n";
			expectedDescription += "	Cone:\n";
			expectedDescription += "		Radius  = 0.000000\n";
			expectedDescription += "		Height  = 0.000000\n";
			expectedDescription += "		Mass    = 0.000000\n";
			expectedDescription += "		Volume  = 0.000000\n";
			expectedDescription += "		Density = 0.000000\n";
			expectedDescription += "	Aggregate Mass   = 0.000000\n";
			expectedDescription += "	Aggregate Volume = 0.000000\n";
			expectedDescription += "	Average Density  = 0.000000";
			BOOST_CHECK_EQUAL(compound.ToString(), expectedDescription);
		}

		BOOST_AUTO_TEST_CASE(with_an_empty_compound)
		{
			compound.AddBody(make_shared<CCompound>());

			string expectedDescription;
			expectedDescription += "Compound:\n";
			expectedDescription += "	Compound:\n";
			expectedDescription += "		empty\n";
			expectedDescription += "		Aggregate Mass   = 0.000000\n";
			expectedDescription += "		Aggregate Volume = 0.000000\n";
			expectedDescription += "		Average Density  = 0.000000\n";
			expectedDescription += "	Aggregate Mass   = 0.000000\n";
			expectedDescription += "	Aggregate Volume = 0.000000\n";
			expectedDescription += "	Average Density  = 0.000000";
			BOOST_CHECK_EQUAL(compound.ToString(), expectedDescription);
		}

		BOOST_AUTO_TEST_CASE(with_a_non_empty_compound)
		{
			auto pCompound2 = make_shared<CCompound>();
			pCompound2->AddBody(make_shared<CCone>(0, 0, 0));
			compound.AddBody(pCompound2);

			string expectedDescription;
			expectedDescription += "Compound:\n";
			expectedDescription += "	Compound:\n";
			expectedDescription += "		Cone:\n";
			expectedDescription += "			Radius  = 0.000000\n";
			expectedDescription += "			Height  = 0.000000\n";
			expectedDescription += "			Mass    = 0.000000\n";
			expectedDescription += "			Volume  = 0.000000\n";
			expectedDescription += "			Density = 0.000000\n";
			expectedDescription += "		Aggregate Mass   = 0.000000\n";
			expectedDescription += "		Aggregate Volume = 0.000000\n";
			expectedDescription += "		Average Density  = 0.000000\n";
			expectedDescription += "	Aggregate Mass   = 0.000000\n";
			expectedDescription += "	Aggregate Volume = 0.000000\n";
			expectedDescription += "	Average Density  = 0.000000";
			BOOST_CHECK_EQUAL(compound.ToString(), expectedDescription);
		}		
	BOOST_AUTO_TEST_SUITE_END()

		
	BOOST_FIXTURE_TEST_SUITE(cant_add_the_same_body_twice, createdCompound)
		BOOST_AUTO_TEST_CASE(onto_the_same_level)
		{
			auto pBody = make_shared<CParallelepiped>(0, 10, 10, 10);
			BOOST_CHECK(compound.AddBody(pBody));
			BOOST_CHECK(!compound.AddBody(pBody));
			BOOST_CHECK_CLOSE(compound.GetVolume(), 1000, 0.1);
		}
		
		BOOST_AUTO_TEST_CASE(onto_the_other_level)
		{
			auto pBody = make_shared<CParallelepiped>(0, 10, 10, 10);
			auto pContainer = make_shared<CCompound>();
			compound.AddBody(pContainer);
			BOOST_CHECK(compound.AddBody(pBody));
			BOOST_CHECK(!pContainer->AddBody(pBody));
			BOOST_CHECK_CLOSE(compound.GetVolume(), 1000, 0.1);
		}
	BOOST_AUTO_TEST_SUITE_END()

	
	BOOST_AUTO_TEST_SUITE(cant_add_the_compound)
		BOOST_AUTO_TEST_CASE(into_itself)
		{
			auto pCompound = make_shared<CCompound>();

			string descriptionBeforeAddition = pCompound->ToString();
			BOOST_REQUIRE(!pCompound->AddBody(pCompound));
			BOOST_CHECK_EQUAL(pCompound->ToString(), descriptionBeforeAddition);
		}

		BOOST_AUTO_TEST_CASE(into_its_child)
		{
			auto pCompound = make_shared<CCompound>();
			auto pChildCompound = make_shared<CCompound>();
			pCompound->AddBody(pChildCompound);

			string descriptionBeforeAddition = pCompound->ToString();
			BOOST_REQUIRE(!pChildCompound->AddBody(pCompound));
			BOOST_CHECK_EQUAL(pCompound->ToString(), descriptionBeforeAddition);
		}
	BOOST_AUTO_TEST_SUITE_END()
	

	void CheckCompoundPropertiesEquality(CCompound obj, double density, double mass, double volume)
	{
		BOOST_CHECK_CLOSE(obj.GetDensity(), density, 0.1);
		BOOST_CHECK_CLOSE(obj.GetMass(), mass, 0.1);
		BOOST_CHECK_CLOSE(obj.GetVolume(), volume, 0.1);
	}

	BOOST_FIXTURE_TEST_SUITE(has_valid_properites, createdCompound)
		
		BOOST_FIXTURE_TEST_CASE(with_nothing_added, createdCompound)
		{
			CheckCompoundPropertiesEquality(compound, 0, 0, 0);
		}			
		

		struct compoundWithSolidBody : createdCompound 
		{
			compoundWithSolidBody()
			{
				compound.AddBody(make_shared<CParallelepiped>(10, 10, 10, 10));
			}
		};
		BOOST_FIXTURE_TEST_CASE(with_solid_body_added, compoundWithSolidBody)
		{
			CheckCompoundPropertiesEquality(compound, 10, 10000, 1000);
		}

		
		struct compoundWithTwoSolidBodies : compoundWithSolidBody
		{
			compoundWithTwoSolidBodies()
			{
				compound.AddBody(make_shared<CParallelepiped>(10, 10, 10, 10));
			}
		};
		BOOST_FIXTURE_TEST_CASE(with_several_solid_bodies_added, compoundWithTwoSolidBodies)
		{
			CheckCompoundPropertiesEquality(compound, 10, 20000, 2000);
		}

		
		struct compoundWithTwoSolidBodiesAndEmptyCompound : compoundWithTwoSolidBodies
		{
			compoundWithTwoSolidBodiesAndEmptyCompound()
			{
				compound.AddBody(make_shared<CCompound>());
			}
		};
		BOOST_FIXTURE_TEST_CASE(with_empty_compound_added, compoundWithTwoSolidBodiesAndEmptyCompound)
		{
			CheckCompoundPropertiesEquality(compound, 10, 20000, 2000);
		}

		
		struct compoundWithTwoSolidBodiesEmptyCompoundAndCompoundWithSolidBody : compoundWithTwoSolidBodiesAndEmptyCompound
		{
			compoundWithTwoSolidBodiesEmptyCompoundAndCompoundWithSolidBody()
			{
				auto pNewCompound = make_shared<CCompound>();
				pNewCompound->AddBody(make_shared<CParallelepiped>(10, 10, 10, 10));
				compound.AddBody(pNewCompound);
			}
		};
		BOOST_FIXTURE_TEST_CASE(with_non_empty_compound_added, compoundWithTwoSolidBodiesEmptyCompoundAndCompoundWithSolidBody)
		{
			CheckCompoundPropertiesEquality(compound, 10, 30000, 3000);
		}
		
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()