#pragma once
#include "stdafx.h"
#include "Body.h"
class CSolidBody :
	public CBody
{
public:
	CSolidBody(double density) { m_density = (density > 0) ? density : 0; };
	virtual ~CSolidBody() {};
	double GetDensity()const { return m_density; };
	double GetMass()const { return m_density * GetVolume(); }
private:
	double m_density;
};

