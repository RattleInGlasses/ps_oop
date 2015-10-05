#include "stdafx.h"
#include "..\Persons\Person.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CPerson_)
	
	BOOST_AUTO_TEST_CASE(can_be_created_and_get_properties)
	{
		CPerson person1(Gender::MALE, 11, "George", 50, 10);
		BOOST_CHECK_EQUAL(person1.GetName(), "George");
		BOOST_CHECK(person1.GetGender() == Gender::MALE);
		BOOST_CHECK_EQUAL(person1.GetAge(), 11u);
		BOOST_CHECK_EQUAL(person1.GetHeight(), 50u);
		BOOST_CHECK_EQUAL(person1.GetWeight(), 10u);

		CPerson person2(Gender::FEMALE, 1, "NewBorn", 60, 3);
		BOOST_CHECK_EQUAL(person2.GetName(), "NewBorn");
		BOOST_CHECK(person2.GetGender() == Gender::FEMALE);
		BOOST_CHECK_EQUAL(person2.GetAge(), 1u);
		BOOST_CHECK_EQUAL(person2.GetHeight(), 60u);
		BOOST_CHECK_EQUAL(person2.GetWeight(), 3u);
	}


	struct CreatedPersons
	{
		shared_ptr<CPerson> pPerson1 = make_shared<CPerson>(Gender::FEMALE, 13, "Person1", 100, 50);
		shared_ptr<CPerson> pPerson2 = make_shared<CPerson>(Gender::MALE, 30, "Person2", 150, 70);
	};
	BOOST_FIXTURE_TEST_SUITE(can_set_properties, CreatedPersons)
		BOOST_AUTO_TEST_CASE(age)
		{
			pPerson1->SetAge(26);
			BOOST_CHECK_EQUAL(pPerson1->GetAge(), 26u);

			BOOST_CHECK_THROW(pPerson2->SetAge(29), invalid_argument);
			BOOST_CHECK_EQUAL(pPerson2->GetAge(), 30u);
		}

		BOOST_AUTO_TEST_CASE(name)
		{
			pPerson1->SetName("newName");
			BOOST_CHECK_EQUAL(pPerson1->GetName(), "newName");

			BOOST_CHECK_THROW(pPerson2->SetName(""), invalid_argument);
			BOOST_CHECK_EQUAL(pPerson2->GetName(), "Person2");
		}

		BOOST_AUTO_TEST_CASE(height)
		{
			pPerson1->SetHeight(120);
			BOOST_CHECK_EQUAL(pPerson1->GetHeight(), 120u);

			BOOST_CHECK_THROW(pPerson2->SetHeight(149), invalid_argument);
			BOOST_CHECK_EQUAL(pPerson2->GetHeight(), 150u);
		}

		BOOST_AUTO_TEST_CASE(weight)
		{
			pPerson1->SetWeight(70);
			BOOST_CHECK_EQUAL(pPerson1->GetWeight(), 70u);

			BOOST_CHECK_THROW(pPerson2->SetWeight(0), invalid_argument);
			BOOST_CHECK_EQUAL(pPerson2->GetWeight(), 70u);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()