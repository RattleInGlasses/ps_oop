#pragma once
#include "stdafx.h"
#include "SolidBody.h"
class CParallelepiped :
	public CSolidBody
{
public:
	CParallelepiped(double density, double width, double height, double depth);
	double GetVolume()const;
	std::string ToString()const;
private:
	double m_width;
	double m_height;
	double m_depth;
};

