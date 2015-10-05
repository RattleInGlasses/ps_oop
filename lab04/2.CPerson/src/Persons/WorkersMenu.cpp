#include "stdafx.h"
#include "WorkersMenu.h"
#include "CliFunctions.h"
#include "CliMenus.h"

using namespace std;


namespace
{
	void SetWorkerProperties(CWorker &worker,
		unsigned age, string const &name, unsigned height, unsigned weight,
		CCompany const *pCompany, string const &post)
	{
		worker.SetAge(age);
		worker.SetName(name);
		worker.SetHeight(height);
		worker.SetWeight(weight);
		worker.SetCompany(pCompany);
		worker.SetPost(post);
	}

	list<reference_wrapper<const CWorker>> GetWorkerListByCompany(list<CWorker> const &workers, CCompany const &company)
	{
		list<reference_wrapper<const CWorker>> result;
		for (auto &worker : workers)
		{
			if (worker.GetCompany() == &company)
			{
				result.push_back(worker);
			}
		}
		return result;
	}

	void PrintWorkerProperties(ostream &ost,
		string const &name, Gender gender, unsigned age, unsigned height,
		unsigned weight, string const &post, CCompany const *pCompany)
	{
		ost << "Name: " << name << endl
			<< "Gender: "; PrintGender(ost, gender); ost << endl
			<< "Age: " << age << endl
			<< "Height: " << height << endl
			<< "Weight: " << weight << endl
			<< "Post: " << post << endl
			<< "Company: " << pCompany->GetName() << endl;
	}

	void PrintWorkerInfo(ostream &ost, CWorker const &worker)
	{
		PrintWorkerProperties(ost,
			worker.GetName(), worker.GetGender(), worker.GetAge(), worker.GetHeight(),
			worker.GetWeight(), worker.GetPost(), worker.GetCompany());
	}
}


CWorkersMenu::CWorkersMenu(ostream &ost, istream &ist, list<CWorker> &workers, list<CCompany> const &companies) :
m_ost(ost),
m_ist(ist),
m_workers(workers),
m_companies(companies)
{
}


bool CWorkersMenu::Start()
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "WorkersMenu", {
		{ "1", bind(&CWorkersMenu::ShowWorkers, &*this) },
		{ "2", bind(&CWorkersMenu::AddWorker, &*this) },
		{ "3", bind(&CWorkersMenu::EditWorkers, &*this) },
		{ "4", bind(&CWorkersMenu::DeleteWorker, &*this) }
	});

	return HaveChangesBeenHappened();
}


// Menu relations functions

void CWorkersMenu::ShowWorkers() const
{
	PredefinedChoiseAndReturnMenu(m_ost, m_ist, "ShowWorkersMenu", {
		{ "1", bind(&CWorkersMenu::ShowAllWorkers, &*this) },
		{ "2", bind(&CWorkersMenu::ShowWorkersByCompany, &*this) },
	});
}


void CWorkersMenu::ShowAllWorkers() const
{
	ShowWorkersList(m_workers, "ShowAllWorkersMenu");
}


void CWorkersMenu::ShowWorkersByCompany() const
{
	if (auto company = ChooseOrganizationPtrMenu(m_ost, m_ist, m_companies))
	{
		auto workersOfCompany = GetWorkerListByCompany(m_workers, **company);
		ShowWorkersList(workersOfCompany, "ShowWorkersByCompanyMenu");
	}
}


void CWorkersMenu::ShowWorker(CWorker const &worker) const
{
	ListChoiseAndReturnWithoutProcessFunctionMenu(m_ost, m_ist,
		bind(PrintWorkerInfo, ref(m_ost), worker));
}


void CWorkersMenu::AddWorker()
{
	string name = ReadNonEmptyString(m_ost, m_ist, "Enter new worker's name");
	Gender gender = ReadGender(m_ost, m_ist, "Is the worker male? (Y/N)");
	unsigned age = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "How old is the worker?", "The age must be more than 0");
	unsigned height = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the worker's height?", "The height must be more than 0");
	unsigned weight = ReadFromStreamWithRestrictionsUntilResultIsGiven<unsigned>(m_ost, m_ist, 1u, UINT_MAX, "What is the worker's weight?", "The weight must be more than 0");
	string post = ReadNonEmptyString(m_ost, m_ist, "Enter new worker's post");
	CCompany const *pCompany = ChooseOrganizationPtrWithoutCancelMenu(m_ost, m_ist, m_companies, "Where does the worker has a job?");

	if (EditWorkerProperties(gender, name, age, height, weight, post, pCompany))
	{
		m_workers.push_back(CWorker(gender, age, name, height, weight, pCompany, post));
	}
}


bool CWorkersMenu::EditWorkerProperties(Gender &gender,	std::string &name, unsigned &age, unsigned &height, 
	unsigned &weight, std::string &post, CCompany const *&pCompany)
{
	string menuName = "EditWorkerPropertiesMenu";

	auto genderCopy = gender;
	auto nameCopy = name;
	auto ageCopy = age;
	auto heightCopy = height;
	auto weightCopy = weight;
	auto postCopy = post;
	auto pCompanyCopy = pCompany;
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName, 
			bind(PrintWorkerProperties, ref(m_ost), nameCopy, genderCopy, ageCopy, heightCopy, weightCopy, postCopy, pCompanyCopy));
		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetWorkerName(nameCopy);
		}
		if (command == "2")
		{
			SetWorkerGender(genderCopy);
		}
		if (command == "3")
		{
			SetWorkerAge(ageCopy);
		}
		if (command == "4")
		{
			SetWorkerHeight(heightCopy);
		}
		if (command == "5")
		{
			SetWorkerWeight(weightCopy);
		}
		if (command == "6")
		{
			SetWorkerPost(postCopy);
		}
		if (command == "7")
		{
			SetWorkerCompany(pCompanyCopy);
		}
		else if (command == "a")
		{
			gender = genderCopy;
			name = nameCopy;
			age = ageCopy;
			height = heightCopy;
			weight = weightCopy;
			post = postCopy;
			pCompany = pCompanyCopy;
			MarkChangesOccurrence();
			return true;
		}
		else if (command == "c")
		{
			return false;
		}
	}
}


void CWorkersMenu::EditWorkers()
{
	ListChoiseAndReturnWithProcessFunctionMenu(m_ost, m_ist, "EditWorkersMenu", m_workers,
		bind(&CWorkersMenu::EditWorker, &*this, std::placeholders::_1));
}


void CWorkersMenu::EditWorker(CWorker &worker)
{
	string menuName = "EditWorkerMenu";

	auto name = worker.GetName();
	auto age = worker.GetAge();
	auto height = worker.GetHeight();
	auto weight = worker.GetWeight();
	auto post = worker.GetPost();
	auto pCompany = worker.GetCompany();
	for (;;)
	{
		PrintMenuMessage(m_ost, menuName,
			bind(PrintWorkerProperties, ref(m_ost), name, worker.GetGender(), age, height, weight, post, pCompany));
		string command = ReadUserCommand(m_ist);

		if (command == "1")
		{
			SetWorkerName(name);
		}
		if (command == "2")
		{
			SetWorkerAge(age, worker.GetAge());
		}
		if (command == "3")
		{
			SetWorkerHeight(height, worker.GetHeight());
		}
		if (command == "4")
		{
			SetWorkerWeight(weight);
		}
		if (command == "5")
		{
			SetWorkerPost(post);
		}
		if (command == "6")
		{
			SetWorkerCompany(pCompany);
		}
		else if (command == "a")
		{
			SetWorkerProperties(worker, age, name, height, weight, pCompany, post);
			MarkChangesOccurrence();
			return;
		}
		else if (command == "c")
		{
			return;
		}
	}
}


void CWorkersMenu::DeleteWorker()
{
	if (m_workers.size() > 0)
	{
		if (DeleteListElementMenu<CWorker>(m_ost, m_ist, m_workers, "DeleteWorkerMenu"))
		{
			MarkChangesOccurrence();
		}
	}
}


// Work with data functions

void CWorkersMenu::SetWorkerName(string &name) const
{
	name = ReadNonEmptyString(m_ost, m_ist, "Enter new name for the worker");
}


void CWorkersMenu::SetWorkerGender(Gender &gender) const
{
	gender = ReadGender(m_ost, m_ist, "Is the worker male? (Y/N)");
}


void CWorkersMenu::SetWorkerAge(unsigned &age, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, age, min, UINT_MAX,
		"Enter new age for the worker",
		"Can't set the age. The new age must be more than previous and more than 0");
}


void CWorkersMenu::SetWorkerHeight(unsigned &height, unsigned min /*= 1u*/) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, height, min, UINT_MAX,
		"Enter new height for the worker",
		"Can't set the height. The new height must be more than previous and more than 0");
}


void CWorkersMenu::SetWorkerWeight(unsigned &weight) const
{
	SetValueWithRestrictions<unsigned>(m_ost, m_ist, weight, 1u, UINT_MAX,
		"Enter new weight for the worker",
		"The weight must be more than 0");
}


void CWorkersMenu::SetWorkerPost(string &post) const
{
	post = ReadNonEmptyString(m_ost, m_ist, "Enter new post for the worker");
}


void CWorkersMenu::SetWorkerCompany(CCompany const *&pCompany) const
{
	if (auto company = ChooseOrganizationPtrMenu(m_ost, m_ist, m_companies))
	{
		pCompany = *company;
	}
}

