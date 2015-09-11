#pragma once
class CGenderedNamedCreature
{
public:
	enum class Gender
	{
		MALE,
		FEMALE
	};
public:
	CGenderedNamedCreature(std::string const &name, Gender const &gender);
	virtual ~CGenderedNamedCreature();
	Gender GetGender()const;
	std::string GetName()const;
private:
	std::string m_name;
	Gender m_gender;
};

CGenderedNamedCreature::CGenderedNamedCreature(std::string const &name, Gender const &gender) :
m_name(name),
m_gender(gender)
{
}

CGenderedNamedCreature::~CGenderedNamedCreature()
{
}

CGenderedNamedCreature::Gender CGenderedNamedCreature::GetGender() const
{
	return m_gender;
}

std::string CGenderedNamedCreature::GetName() const
{
	return m_name;
}

