#pragma once
#include <memory>
#include <vector>
#include "Body.h"
class CCompound :
	public CBody
{
public:
	bool AddBody(std::shared_ptr<CBody> const &pNewBody);
	double GetVolume()const override;
	double GetMass()const override;
	double GetDensity()const override;
	std::string ToString()const override;
private:
	bool IsParentOrTheSame(CBody const *pPossibleChild, CBody const *pPossibleAncestor) const;
	std::string GetTabbedAggregateDescription(std::vector<std::shared_ptr<CBody>> const &bodies) const;
	std::string AddTabToEveryLine(std::string const &lines) const;
private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
};
