#pragma once
#include <iostream>
#include <list>
#include "CliMenu.h"
#include "Worker.h"
#include "Company.h"
class CWorkersMenu :
	public CCliMenu, 
	boost::noncopyable
{
public:
	CWorkersMenu(std::ostream &ost, std::istream &ist, std::list<CWorker> &workers, std::list<CCompany> const &companies);
	virtual ~CWorkersMenu() {};
	bool Start();
private:
	void ShowWorkers() const;
	void ShowAllWorkers() const;
	void ShowWorkersByCompany() const;
	template <typename T>
	void ShowWorkersList(std::list<T> const &workers, std::string const &menuName) const;
	void ShowWorker(CWorker const &worker) const;
	void AddWorker();
	bool EditWorkerProperties(Gender &gender, std::string &name, unsigned &age,	unsigned &height,
		unsigned &weight, std::string &post, CCompany const *&pCompany);
	void EditWorkers();
	void EditWorker(CWorker &worker);
	void DeleteWorker();

	void SetWorkerName(std::string &name) const;
	void SetWorkerGender(Gender &gender) const;
	void SetWorkerAge(unsigned &age, unsigned min = 1u) const;
	void SetWorkerHeight(unsigned &height, unsigned min = 1u) const;
	void SetWorkerWeight(unsigned &weight) const;
	void SetWorkerPost(std::string &post) const;
	void SetWorkerCompany(CCompany const *&pCompany) const;
private:
	std::ostream &m_ost;
	std::istream &m_ist;
	std::list<CWorker> &m_workers;
	std::list<CCompany> const &m_companies;
};


template <typename T>
void CWorkersMenu::ShowWorkersList(std::list<T> const &workers, std::string const &menuName) const
{
	ListChoiseAndReturnWithProcessFunctionMenu(m_ost, m_ist, menuName, workers,
		bind(&CWorkersMenu::ShowWorker, &*this, std::placeholders::_1));
}
