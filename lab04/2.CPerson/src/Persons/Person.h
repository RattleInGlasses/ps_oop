#pragma once
#include <string>
enum class Gender
{
	MALE,
	FEMALE
};
class CPerson
{
public:
	CPerson(Gender gender, unsigned age, std::string const &name, unsigned height, unsigned weight);
	virtual ~CPerson() {};
public:
	Gender GetGender() const;
	unsigned GetAge() const;
	std::string const &GetName() const;
	unsigned GetHeight() const;
	unsigned GetWeight() const;
	void SetAge(unsigned value);
	void SetName(std::string value);
	void SetHeight(unsigned value);
	void SetWeight(unsigned value);
private:
	CPerson &operator =(CPerson &);
private:
	Gender const m_gender;
	unsigned m_age;
	std::string m_name;
	unsigned m_height;
	unsigned m_weight;
};

