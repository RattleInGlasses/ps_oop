#pragma once
#include <string>
class CName
{
public:
	CName(std::string const & = "");
public:
	std::string GetValue() const;
	void SetValue(std::string const &);
public:
	bool operator ==(std::string const &) const;
	bool operator !=(std::string const &) const;
private:
	std::string m_data;
};

