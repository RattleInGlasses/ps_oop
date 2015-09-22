#include "stdafx.h"
#include "..\Persons\Worker.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CWorker_)

	BOOST_AUTO_TEST_CASE(can_be_created_and_get_properties)
	{
		CCompany comp("Comp");
		CWorker w1(Gender::FEMALE, 17, "w1", 100, 100, &comp, "pst");
		BOOST_CHECK_EQUAL(w1.GetCompany(), &comp);
		BOOST_CHECK_EQUAL(w1.GetPost(), "pst");
	}


	struct CreatedWorker
	{
		CCompany comp1 = CCompany("Com1");
		CCompany comp2 = CCompany("Com2");
		shared_ptr<CWorker> pWrkr = make_shared<CWorker>(Gender::MALE, 17, "st", 100, 299, &comp1, "pst");
	};
	BOOST_FIXTURE_TEST_CASE(can_set_company, CreatedWorker)
	{
		pWrkr->SetCompany(&comp2);
		BOOST_CHECK_EQUAL(pWrkr->GetCompany(), &comp2);

		BOOST_CHECK_THROW(pWrkr->SetCompany(nullptr), invalid_argument);
	}


	BOOST_FIXTURE_TEST_CASE(can_set_post, CreatedWorker)
	{
		pWrkr->SetPost("new post");
		BOOST_CHECK_EQUAL(pWrkr->GetPost(), "new post");

		BOOST_CHECK_THROW(pWrkr->SetPost(""), invalid_argument);
		BOOST_CHECK_EQUAL(pWrkr->GetPost(), "new post");
	}

BOOST_AUTO_TEST_SUITE_END()