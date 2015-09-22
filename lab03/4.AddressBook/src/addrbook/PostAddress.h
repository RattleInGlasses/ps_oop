#pragma once
#include <string>
class CPostAddress
{
public:
	CPostAddress(std::string const &city = "",
		std::string const &street = "", 
		std::string const &house = "", 
		unsigned apartment = 0);
public:
	void SetCity(std::string const &);
	void SetStreet(std::string const &);
	void SetHouse(std::string const &);
	void SetApartment(unsigned);
	std::string GetCity() const;
	std::string GetStreet() const;
	std::string GetHouse() const;
	unsigned GetApartment() const;
public:
	bool operator ==(CPostAddress const &) const;
	bool operator !=(CPostAddress const &) const;
private:
	std::string m_city;
	std::string m_street;
	std::string m_house;
	unsigned m_apartment;
};

