#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Sphere.h"

using namespace std;

CSphere::CSphere(double density, double radius) : 
	CSolidBody(density)
{
	m_radius = (radius > 0) ? radius : 0;
}


double CSphere::GetVolume() const
{
	return M_PI * m_radius * m_radius * m_radius * 4 / 3;
}


string CSphere::ToString() const
{
	string bodyType = "Sphere:\n";
	string radius;
	(radius  += "\tRadius  = ") += to_string(m_radius) += "\n";
	string mass;
	(mass    += "\tMass    = ") += to_string(GetMass()) += "\n";
	string volume;
	(volume  += "\tVolume  = ") += to_string(GetVolume()) += "\n";
	string density;
	(density += "\tDensity = ") += to_string(GetDensity());

	return bodyType + radius + mass+ volume + density;
}