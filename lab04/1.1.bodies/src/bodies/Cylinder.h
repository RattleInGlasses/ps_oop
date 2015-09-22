#pragma once
#include "SolidBody.h"
class CCylinder :
	public CSolidBody
{
public:
	CCylinder(double density, double radius, double height);
	double GetVolume()const override;
	std::string ToString()const override;
private:
	double m_radius;
	double m_height;
};

