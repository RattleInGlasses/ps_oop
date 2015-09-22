#pragma once
#include <string>
#include "SolidBody.h"
class CSphere :
	public CSolidBody
{
public:
	CSphere(double density, double radius);
	double GetVolume()const override;
	std::string ToString()const override;
private:
	double m_radius;
};

