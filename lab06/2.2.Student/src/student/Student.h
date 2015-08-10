#pragma once
class CStudent
{
public:
	CStudent(std::string const &name, std::string const &surname, std::string const &patronymic, int age);
private:
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	int m_age = 0;
public:
	std::string GetName()const;
	std::string GetSurname()const;
	std::string GetPatronymic()const;
	int GetAge()const;

	void Rename(std::string name, std::string surname, std::string patronymic);
	void SetAge(int value);
};

