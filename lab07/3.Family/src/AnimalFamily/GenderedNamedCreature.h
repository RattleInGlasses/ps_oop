#pragma once
enum class Gender
{
	MALE,
	FEMALE
};
class CGenderedNamedCreature
{
public:
	CGenderedNamedCreature(std::string const &name, Gender const &gender);
	virtual ~CGenderedNamedCreature() {};
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

Gender CGenderedNamedCreature::GetGender() const
{
	return m_gender;
}

std::string CGenderedNamedCreature::GetName() const
{
	return m_name;
}

