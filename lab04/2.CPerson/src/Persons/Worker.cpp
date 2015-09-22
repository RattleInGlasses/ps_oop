#include "stdafx.h"
#include "Worker.h"

using namespace std;
using boost::trim;

namespace
{
	void CheckCompanyPtrThrow(CCompany const *pCompany)
	{
		if (pCompany == nullptr)
		{
			throw invalid_argument("A worker must be in a company");
		}
	}

	void CheckPostThrow(string const &post)
	{
		if (post == "")
		{
			throw invalid_argument("A worker must have a post");
		}
	}
}

CWorker::CWorker(Gender gender, unsigned age, string const &name, unsigned height, unsigned weight,
	CCompany const *pCompany, string const &post) :
	CPerson(gender, age, name, height, weight),
	m_pCompany(pCompany),
	m_post(post)
{
	CheckCompanyPtrThrow(pCompany);
	trim(m_post);
	CheckPostThrow(m_post);
}


void CWorker::SetCompany(CCompany const *value)
{
	CheckCompanyPtrThrow(value);
	m_pCompany = value;
}


void CWorker::SetPost(string value)
{
	trim(value);
	CheckPostThrow(value);
	m_post = value;
}


CCompany const *CWorker::GetCompany() const
{
	return m_pCompany;
}


string const &CWorker::GetPost() const
{
	return m_post;
}


