#include "stdafx.h"
#include "..\Persons\Student.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CStudent_)

	BOOST_AUTO_TEST_CASE(can_be_created_and_get_properties)
	{
		CUniversity univer("UNI");
		CStudent st1(Gender::FEMALE, 17, "st1", 100, 100, &univer);
		BOOST_CHECK_EQUAL(st1.GetUniversity(), &univer);
		BOOST_CHECK_EQUAL(st1.GetStudyYear(), 1);

		CStudent st2(Gender::MALE, 19, "st2", 200, 200, &univer, 3);
		BOOST_CHECK_EQUAL(st2.GetUniversity(), &univer);
		BOOST_CHECK_EQUAL(st2.GetStudyYear(), 3);
	}

	struct CreatedStudent
	{
		CUniversity univer1 = CUniversity("UNI1");
		CUniversity univer2 = CUniversity("UNI2");
		shared_ptr<CStudent> pSt = make_shared<CStudent>(Gender::MALE, 17, "st", 100, 299, &univer1, 3);
	};
	BOOST_FIXTURE_TEST_CASE(can_set_university, CreatedStudent)
	{
		pSt->SetUniversity(&univer2);
		BOOST_CHECK_EQUAL(pSt->GetUniversity(), &univer2);

		BOOST_CHECK_THROW(pSt->SetUniversity(nullptr), invalid_argument);
	}

	BOOST_FIXTURE_TEST_CASE(can_set_study_year, CreatedStudent)
	{
		pSt->SetStudyYear(4);
		BOOST_CHECK_EQUAL(pSt->GetStudyYear(), 4);

		BOOST_CHECK_THROW(pSt->SetStudyYear(1), invalid_argument);
		BOOST_CHECK_THROW(pSt->SetStudyYear(6), invalid_argument);
		BOOST_CHECK_EQUAL(pSt->GetStudyYear(), 4);
	}
	
BOOST_AUTO_TEST_SUITE_END()