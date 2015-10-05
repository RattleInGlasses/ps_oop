#pragma once
#include <iostream>
#include <list>
#include "CliMenu.h"
#include "Company.h"
#include "Worker.h"
class CCompaniesMenu :
	public CCliMenu,
	boost::noncopyable
{
public:
	CCompaniesMenu(std::ostream &ost, std::istream &ist, std::list<CCompany> &companies, std::list<CWorker> &workers);
	bool Start();
private:
	void ShowCompanies() const;
	void ShowCompany(CCompany const &company) const;
	void AddCompany();
	void EditCompanies();
	bool EditCompany(CCompany &company);
	void DeleteCompany();

	bool SetCompanyName(CCompany &company) const;
	void SetCompanyWebsite(CCompany &company) const;
private:
	std::ostream &m_ost;
	std::istream &m_ist;
	std::list<CCompany> &m_companies;
	std::list<CWorker> &m_workers;
};

