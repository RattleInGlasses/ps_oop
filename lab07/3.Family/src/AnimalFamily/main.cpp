// AnimalFamily.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Family.h"
#include "PetCreator.h"
#include "HumanCreator.h"
#include "Cat.h"
#include "Dog.h"
#include "Human.h"

using namespace std;
using Gender = CGenderedNamedCreature::Gender;

template <typename Pet>
void MakePetChild(CFamily<Pet, CPetCreator<Pet>> &petFamily, string const &name, Gender const &gender)
{
	CPetCreator<Pet> childCreator(name, gender);
	petFamily.MakeChild(childCreator);
}

template <typename Human>
void MakeHumanChild(CFamily<Human, CHumanCreator<Human>> &humanFamily, string const &name, Gender const &gender, unsigned birthCertificate)
{
	CHumanCreator<Human> childCreator(name, gender, birthCertificate);
	humanFamily.MakeChild(childCreator);
}

/*по-моему, вывод - это часть интерфейса, а интерфейс - это специфика конкретной программы,
поэтому лучше (универсальнее, логичнее) операторы вывода в поток определить в основной части
(или, лучше - в части, отвечающей за интерфейс) программы, а не в соответствующих классах?*/

ostream &operator <<(ostream &output, Gender const &gender)
{
	if (gender == Gender::FEMALE)
	{
		output << "female";
	}
	else
	{
		output << "male";
	}
	return output;
}

ostream &operator <<(ostream &output, CDog const &dog)
{
	output << dog.GetName() << " " << dog.GetGender();
	return output;
}

ostream &operator <<(ostream &output, CCat const &cat)
{
	output << cat.GetName() << " " << cat.GetGender();
	return output;
}

ostream &operator <<(ostream &output, CHuman const &human)
{
	output << human.GetName() << " " << human.GetGender() << " " << human.GetBirthCertificate();
	return output;
}

template <
	typename Creature,
	typename CreatureCreator = CStandardCreatureCreator<Creature>,
	typename GenderDeterminer = CStandardGenderDeterminer<Creature>
>
ostream &operator <<(ostream &output, CFamily<Creature, CreatureCreator, GenderDeterminer> const &family)
{
	output << "spouse 1: " << family.GetSpouse1() << endl;
	output << "spouse 2: " << family.GetSpouse2() << endl;
	output << "children:" << endl;
	for (size_t i = 0; i < family.GetChildCount(); ++i)
	{
		output << '\t' << family.GetChild(i) << endl;
	}
	return output;
}

int _tmain()
{
	CDog bobik("Bobik", Gender::MALE);
	CDog zuchka("Zhuchka", Gender::FEMALE);
	CFamily<CDog, CPetCreator<CDog>> dogFamily(bobik, zuchka);
	MakePetChild<CDog>(dogFamily, "Tuzik", Gender::MALE);
	MakePetChild<CDog>(dogFamily, "Sharik", Gender::MALE);
	MakePetChild<CDog>(dogFamily, "Knopochka", Gender::FEMALE);

	CCat vaska("Vas'ka", Gender::MALE);
	CCat murka("Murka", Gender::FEMALE);
	CFamily<CCat, CPetCreator<CCat>> catFamily(vaska, murka);
	MakePetChild<CCat>(catFamily, "Tom", Gender::MALE);
	MakePetChild<CCat>(catFamily, "Murzik", Gender::MALE);
	MakePetChild<CCat>(catFamily, "Pushok", Gender::MALE);
	MakePetChild<CCat>(catFamily, "Mashka", Gender::FEMALE);

	CHuman ruslan("Ruslan", Gender::MALE, 11001100);
	CHuman ludmila("Ludmila", Gender::FEMALE, 22110011);
	CFamily<CHuman, CHumanCreator<CHuman>> humanFamily(ruslan, ludmila);
	MakeHumanChild<CHuman>(humanFamily, "Gvidon", Gender::MALE, 11221133);
	MakeHumanChild<CHuman>(humanFamily, "Saltan", Gender::MALE, 33112211);
	MakeHumanChild<CHuman>(humanFamily, "Vasilisa", Gender::FEMALE, 11441122);

	cout << "Dog family:" << endl << dogFamily << endl;
	cout << "Cat family:" << endl << catFamily << endl;
	cout << "Human family:" << endl << humanFamily << endl;

	return 0;
}

