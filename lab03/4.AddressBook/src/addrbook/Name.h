#pragma once
#include <string>
class CName
{
public:
	CName(std::string const & = "");
	CName(char const *);
public:
	CName &operator =(std::string const &);
	operator std::string() const;
	bool Match(std::string const &) const;
private:
	std::string m_name;
};

