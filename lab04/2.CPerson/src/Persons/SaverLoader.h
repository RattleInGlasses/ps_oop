#pragma once
#include <string>
#include <list>
#include "University.h"
#include "Student.h"
#include "Company.h"
#include "Worker.h"

bool SaveData(std::string const &filename,
	std::list<CStudent> const &students,
	std::list<CUniversity> const &universities,
	std::list<CWorker> const &workers,
	std::list<CCompany> const &companies);

bool LoadData(std::string const &filename,
	std::list<CStudent> &students,
	std::list<CUniversity> &universities,
	std::list<CWorker> &workers,
	std::list<CCompany> &companies);
