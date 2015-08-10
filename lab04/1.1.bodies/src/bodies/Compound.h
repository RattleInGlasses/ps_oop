#pragma once
#include <memory>
#include <vector>
#include "Body.h"
class CCompound :
	public CBody
{
public:
	bool AddBody(std::shared_ptr<CBody> pNewBody);
	double GetVolume()const;
	double GetMass()const;
	double GetDensity()const;
	std::string ToString()const;
private:
	bool IsParentOrTheSame(CBody const *pPossibleChild, CBody const *pPossibleAncestor) const;
	std::string GetTabbedAggregateDescription(std::vector<std::shared_ptr<CBody>> const &bodies) const;
	std::string AddTabToEveryLine(std::string const &lines) const;
private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
};
