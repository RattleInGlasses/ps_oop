#pragma once
#include "SolidBody.h"
class CCone :
	public CSolidBody
{
public:
	CCone(double density, double radius, double height);
	double GetVolume()const;
	std::string ToString()const;
private:
	double m_radius;
	double m_height;
};

