#pragma once
#include "Person.h"
#include "Company.h"
#include <string>
class CWorker :
	public CPerson
{
public:
	CWorker(Gender gender, unsigned age, std::string const &name, unsigned height, unsigned weight,
		CCompany const *pCompany, std::string const &post);
	virtual ~CWorker() override final {};
public:
	void SetCompany(CCompany const *value);
	void SetPost(std::string value);
	CCompany const *GetCompany() const;
	std::string const &GetPost() const;
private:
	CCompany const *m_pCompany;
	std::string m_post;
};

