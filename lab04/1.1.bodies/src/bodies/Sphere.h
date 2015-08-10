#pragma once
#include <string>
#include "SolidBody.h"
class CSphere :
	public CSolidBody
{
public:
	CSphere(double density, double radius);
	double GetVolume()const;
	std::string ToString()const;
private:
	double m_radius;
};

