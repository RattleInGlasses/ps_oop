#include "stdafx.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Cylinder.h"

using namespace std;

CCylinder::CCylinder(double density, double radius, double height) :
	CSolidBody(density)
{
	m_radius = (radius > 0) ? radius : 0;
	m_height = (height > 0) ? height : 0;
}


double CCylinder::GetVolume() const
{
	return M_PI * m_radius * m_radius * m_height;
}


string CCylinder::ToString() const
{
	string bodyType = "Cylinder:\n";
	string radius;
	(radius  += "\tRadius  = ") += to_string(m_radius) += "\n";
	string height;
	(height  += "\tHeight  = ") += to_string(m_height) += "\n";
	string mass;
	(mass    += "\tMass    = ") += to_string(GetMass()) += "\n";
	string volume;
	(volume  += "\tVolume  = ") += to_string(GetVolume()) += "\n";
	string density;
	(density += "\tDensity = ") += to_string(GetDensity());

	return bodyType + radius + height + mass + volume + density;
}