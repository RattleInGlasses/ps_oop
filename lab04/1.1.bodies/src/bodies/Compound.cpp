#include "stdafx.h"
#include "Compound.h"

using namespace std;
using boost::accumulate;

// public functions

bool CCompound::AddBody(shared_ptr<CBody> const &pNewBody)
{
	if ((pNewBody->HasParent())
	|| (IsParentOrTheSame(this, pNewBody.get())))
	{
		return false;
	}
	
	m_bodies.push_back(pNewBody);
	pNewBody->SetParent(this);
	return true;
}


double CCompound::GetDensity() const
{
	return (GetVolume() > 0) ? GetMass() / GetVolume() : 0;
}


double CCompound::GetMass() const
{
	return accumulate(m_bodies, 0.0,
		[](double sum, shared_ptr<CBody> const &body)
		{
			return sum + body->GetMass();
		});
}


double CCompound::GetVolume() const
{
	return accumulate(m_bodies, 0.0,
		[](double sum, shared_ptr<CBody> const &body)
		{
			return sum + body->GetVolume();
		});
}


string CCompound::ToString() const
{
	string result = "Compound:\n";
	
	if (m_bodies.size() == 0)
	{
		result += "\tempty\n";
	}
	else
	{
		result += GetTabbedAggregateDescription(m_bodies);
	}

	result += "\tAggregate Mass   = " + to_string(GetMass()) + '\n';
	result += "\tAggregate Volume = " + to_string(GetVolume()) + '\n';
	result += "\tAverage Density  = " + to_string(GetDensity());

	return result;
}


// private functions

bool CCompound::IsParentOrTheSame(CBody const *pPossibleChild, CBody const *pPossibleAncestor) const
{
	if (pPossibleChild == pPossibleAncestor)
	{
		return true;
	}
	if (!pPossibleChild->HasParent())
	{
		return false;
	}
	return IsParentOrTheSame(pPossibleChild->GetParent(), pPossibleAncestor);
}


string CCompound::GetTabbedAggregateDescription(vector<shared_ptr<CBody>> const &bodies) const
{
	string result;
	for (auto body : bodies)
	{
		result += AddTabToEveryLine(body->ToString());
	}
	return result;
}


string CCompound::AddTabToEveryLine(string const &str) const
{
	vector<string> lines;
	boost::split(lines, str, bind2nd(equal_to<char>(), '\n'));

	string result;
	for_each(lines.begin(), lines.end(), [&result](string &line){ ((result += '\t') += line) += '\n'; });
	return result;
}