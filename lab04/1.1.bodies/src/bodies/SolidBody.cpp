#include "stdafx.h"
#include "SolidBody.h"

using namespace std;


CSolidBody::CSolidBody(double density) :
m_density(max(0.0, density))
{
}


double CSolidBody::GetDensity() const
{
	return m_density;
}


double CSolidBody::GetMass() const
{
	return m_density * GetVolume();
}
