#pragma once
#include "SolidBody.h"
class CParallelepiped :
	public CSolidBody
{
public:
	CParallelepiped(double density, double width, double height, double depth);
	double GetVolume()const override;
	std::string ToString()const override;
private:
	double m_width;
	double m_height;
	double m_depth;
};

