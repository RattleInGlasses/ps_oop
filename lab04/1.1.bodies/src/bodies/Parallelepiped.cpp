#include "stdafx.h"
#include <boost/format.hpp>
#include "Parallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double height, double depth) :
	CSolidBody(density)
{
	m_width = (width > 0) ? width : 0;
	m_height = (height > 0) ? height : 0;
	m_depth = (depth > 0) ? depth : 0;
}


double CParallelepiped::GetVolume() const
{
	return m_depth * m_height * m_width;
}

string CParallelepiped::ToString() const
{
	/*
	return (boost::format(
R"(Parallelepiped:
	Width   = %1%
	Height  = %2%
	Depth   = %3%
	Mass    = %4%
	Volume  = %5%
	Density = %6%)") 
		% m_width 
		% m_height 
		% m_depth 
		% GetMass() 
		% GetVolume() 
		% GetDensity()
		).str();
	*/
	string bodyType = "Parallelepiped:\n";
	string width;
	(width   += "\tWidth   = ") += to_string(m_width) += "\n";
	string height;
	(height  += "\tHeight  = ") += to_string(m_height) += "\n";
	string depth;
	(depth   += "\tDepth   = ") += to_string(m_depth) += "\n";
	string mass;
	(mass    += "\tMass    = ") += to_string(GetMass()) += "\n";
	string volume;
	(volume  += "\tVolume  = ") += to_string(GetVolume()) += "\n";
	string density;
	(density += "\tDensity = ") += to_string(GetDensity());

	return bodyType + width + height + depth + mass + volume + density;
}