#pragma once
#include "Body.h"
class CSolidBody :
	public CBody
{
public:
	CSolidBody(double density);
	double GetDensity()const override final;
	double GetMass()const override final;
private:
	double m_density;
};

