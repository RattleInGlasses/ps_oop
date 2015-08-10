#pragma once
#include "Body.h"
class CSolidBody :
	public CBody
{
public:
	CSolidBody(double density) { m_density = (density > 0) ? density : 0; };
	double GetDensity()const override final { return m_density; };
	double GetMass()const override final { return m_density * GetVolume(); }
private:
	double m_density;
};

