#include "stdafx.h"
#include "PostAddress.h"

using namespace std;
using boost::trim;

namespace
{
	string Lower(string const &str)
	{
		string result(str);
		boost::to_lower(result);
		return result;
	}
}


CPostAddress::CPostAddress(string const &city, string const &street, string const &house, unsigned apartment) :
m_city(city),
m_street(street),
m_house(house),
m_apartment(apartment)
{
	trim(m_city);
	trim(m_street);
	trim(m_house);
}


void CPostAddress::SetCity(std::string const &value)
{
	m_city = value;
	trim(m_city);
}


void CPostAddress::SetStreet(std::string const &value)
{
	m_street = value;
	trim(m_street);
}


void CPostAddress::SetHouse(std::string const &value)
{
	
	m_house = value;
	trim(m_house);
}


void CPostAddress::SetApartment(unsigned value)
{
	m_apartment = value;
}


string CPostAddress::GetCity() const
{
	return m_city;
}


string CPostAddress::GetStreet() const
{
	return m_street;
}


string CPostAddress::GetHouse() const
{
	return m_house;
}


unsigned CPostAddress::GetApartment() const
{
	return m_apartment;
}


bool CPostAddress::operator ==(CPostAddress const &address2) const
{
	
	return (((Lower(m_city) == Lower(address2.m_city)) || (address2.m_city == ""))
		&& ((Lower(m_street) == Lower(address2.m_street)) || (address2.m_street == ""))
		&& ((Lower(m_house) == Lower(address2.m_house)) || (address2.m_house == ""))
		&& ((m_apartment == address2.m_apartment) || (address2.m_apartment == 0)));
}


bool CPostAddress::operator !=(CPostAddress const &address2) const
{
	return !(*this == address2);
}
