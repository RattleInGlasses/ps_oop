// bodies.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"
#include "Compound.h"
#include <boost\concept_check.hpp>
#include <iterator>

using namespace std;

#define makeBodyPointer(T) make_shared<T>
typedef shared_ptr<CBody> BodyPointer;
typedef vector<BodyPointer> BodyVector;

const string USER_INPUT_BEGINING = "> ";


// print functions

void PrintBody(BodyPointer const &pBody, ostream &output)
{
	if (pBody)
	{
		output << pBody->ToString() << endl;
	}
	else
	{
		output << "nothing to show" << endl;
	}
}


double CalcInWaterWeight(BodyPointer const &pBody)
{
	return (pBody->GetDensity() - 1000) * 9.8 * pBody->GetVolume();
}


bool LighterInWater(BodyPointer const &b1, BodyPointer const &b2)
{
	return CalcInWaterWeight(b1) < CalcInWaterWeight(b2);
}


bool LessMass(BodyPointer const &b1, BodyPointer const &b2)
{
	return b1->GetMass() < b2->GetMass();
}


typedef std::vector<BodyPointer>::const_iterator BodyIterator;
BodyPointer ChooseBody
(
	BodyVector const &bodies,
	BodyIterator(*fChooseElement)(BodyIterator, BodyIterator, bool(BodyPointer const &, BodyPointer const &)),
	bool(*fLess)(BodyPointer const &, BodyPointer const &)
)
{
	if (bodies.size() > 0)
	{
		return *(fChooseElement(bodies.begin(), bodies.end(), fLess));
	}

	return BodyPointer();
}


void PrintLeastInWaterWeightBody(BodyVector const &bodies, ostream &output)
{
	output << "Body with the least in water weight:" << endl;
	PrintBody(ChooseBody(bodies, min_element, LighterInWater), output);
}


void PrintMaxMassBody(BodyVector const &bodies, ostream &output)
{
	output << "Body with max mass:" << endl;
	PrintBody(ChooseBody(bodies, max_element, LessMass), output);
	output << endl;	
}


// read functions

void ClearIStream(istream &input)
{
	input.clear();
	string s;
	getline(input, s);
}

template <typename T>
T ReadFromIStreamWithMessage(istream &input, string msg, ostream &output)
{	
	T value;
	output << msg;
	output.flush();
	while (!(input >> value))
	{
		ClearIStream(input);
		output << msg;
		output.flush();
	} 
	ClearIStream(input);

	return value;
}


boost::optional<BodyPointer> ReadBody(istream &input, ostream &output);

BodyPointer ReadCompound(istream &input, ostream &output)
{
	output << "=== Start read compound ===" << endl;
	
	auto pCompound = makeBodyPointer(CCompound)(CCompound());
	while (auto body = ReadBody(input, output))
	{
		pCompound->AddBody(*body);
	}		
	
	output << "===  End read compound  ===" << endl;

	return pCompound;
}


BodyPointer ReadCylinder(istream &input, ostream &output)
{
	return makeBodyPointer(CCylinder)(CCylinder
		(
			ReadFromIStreamWithMessage<double>(input, "Density = ", output),
			ReadFromIStreamWithMessage<double>(input, "Radius  = ", output),
			ReadFromIStreamWithMessage<double>(input, "Height  = ", output)
		));
}


BodyPointer ReadCone(istream &input, ostream &output)
{
	output << "Enter cone's properties" << endl;
	
	return makeBodyPointer(CCone)(CCone
		(
			ReadFromIStreamWithMessage<double>(input, "Density = ", output),
			ReadFromIStreamWithMessage<double>(input, "Radius  = ", output),
			ReadFromIStreamWithMessage<double>(input, "Height  = ", output)
		));
}


BodyPointer ReadParallelepiped(istream &input, ostream &output)
{
	output << "Enter parallelepiped's properties" << endl;

	return makeBodyPointer(CParallelepiped)(CParallelepiped
		(
			ReadFromIStreamWithMessage<double>(input, "Density = ", output),
			ReadFromIStreamWithMessage<double>(input, "Width   = ", output),
			ReadFromIStreamWithMessage<double>(input, "Height  = ", output),
			ReadFromIStreamWithMessage<double>(input, "Depth   = ", output)
		));
}


BodyPointer ReadSphere(istream &input, ostream &output)
{
	output << "Enter sphere's properties" << endl;

	return makeBodyPointer(CSphere)(CSphere
		(
			ReadFromIStreamWithMessage<double>(input, "Density = ", output),
			ReadFromIStreamWithMessage<double>(input, "Radius  = ", output)
		));
}


string GetCommand(istream &input)
{
	string command;
	getline(input, command);
	boost::algorithm::trim(command);
	boost::to_lower(command);
	return command;
}


boost::optional<BodyPointer> ReadBody(istream &input, ostream &output)
{	
	while (true)
	{
		output << "choose next body" << endl;
		output << USER_INPUT_BEGINING;

		string command = GetCommand(input);
		if ("sphere" == command)
		{
			output << "Adding a sphere" << endl;
			return ReadSphere(input, output);
		}
		else if ("para" == command)
		{
			output << "Adding a parallelepiped" << endl;
			return ReadParallelepiped(input, output);
		}
		else if ("cone" == command)
		{
			output << "Adding a cone" << endl;
			return ReadCone(input, output);
		}
		else if ("cylinder" == command)
		{
			output << "Adding a cylinder" << endl;
			return ReadCylinder(input, output);
		}
		else if ("compound" == command)
		{
			output << "Adding a compound body" << endl;
			return ReadCompound(input, output);
		}
		else if ("end" == command)
		{
			output << "Ending read bodies" << endl;
			return boost::none;
		}
		else
		{
			output << "Unknown command" << endl;
		}
	}
}


void WriteReadBodiesMenu(ostream &output)
{
	output << "Create bodies\nAvailable commands:\n";
	output << "\"sphere\"   - Create sphere\n";
	output << "\"para\"     - Create parallelepiped\n";
	output << "\"cone\"     - Create cone\n";
	output << "\"cylinder\" - Create cylinder\n";
	output << "\"compound\" - Create compound\n";
	output << "\"end\"      - End input" << endl;
}


BodyVector ReadBodies(istream &input, ostream &output)
{	
	WriteReadBodiesMenu(output);

	BodyVector bodies;
	while (auto body = ReadBody(input, output))
	{
		bodies.push_back(*body);
	}

	output << endl;

	return bodies;
}


int main()
{
	auto bodies = ReadBodies(cin, cout);
	PrintMaxMassBody(bodies, cout);
	PrintLeastInWaterWeightBody(bodies, cout);

	return 0;
}

