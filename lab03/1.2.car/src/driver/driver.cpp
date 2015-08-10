// driver.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Car.h"

using namespace std;

string const MSG_DESCRIPTION = "The program allows you to control a virtual car\n";
string const USAGE_INFO      = "Info             - shows the car's stats\n";
string const USAGE_ENGINEON  = "EngineOn         - start the car's engine\n";
string const USAGE_ENGINEOFF = "EngineOff        - stop the car's engine\n";
string const USAGE_SETGEAR   = "SetGear <gear>   - try to set a gear\n";
string const USAGE_SETSPEED  = "SetSpeed <speed> - try to set a speed\n";
string const USAGE_EXIT      = "Exit             - exit the program\n";
string const MSG_USAGE       = "Allowed commands :\n" + USAGE_INFO + USAGE_ENGINEON + USAGE_ENGINEOFF + USAGE_SETGEAR + USAGE_SETSPEED + USAGE_EXIT;
string const MSG_DELIMITER   = "-----------------------------------------------\n";
string const MSG_COMMAND_PROMPT = "Enter your command:\n";

string const COMMAND_LINE_SYMBOL = "> ";


int GetMinGearSpeed(int gear)
{
	return CCar::SPEED_RANGE.at(gear).min;
}


int GetMaxGearSpeed(int gear)
{
	return CCar::SPEED_RANGE.at(gear).max;
}


bool SpeedIsInGearLimit(int speed, int gear)
{
	return (CCar::SPEED_RANGE.find(gear) == CCar::SPEED_RANGE.end())
		? false
		: ((speed >= CCar::SPEED_RANGE.at(gear).min) && (speed <= CCar::SPEED_RANGE.at(gear).max));
}


string GearsToStr(vector<int> const &gears)
{
	string result;
	for_each(gears.begin(), gears.end(), [&result](int gear){ result += to_string(gear) + " "; });
	return result;
}


void AddAvailableGear(vector<int> &gears, int gear, int speed)
{
	if (SpeedIsInGearLimit(speed, gear))
	{
		gears.push_back(gear);
	}
}


vector<int> GetAvailableGears(int speed, CCar::Direction direction)
{
	vector<int> result = { 0 };
	
	if (direction == CCar::Direction::BACKWARD)
	{
		AddAvailableGear(result, -1, speed);
	}
	else if (direction == CCar::Direction::FORWARD)
	{
		for (int gear = 1; gear <= 5; ++gear)
		{
			AddAvailableGear(result, gear, speed);
		}
	}
	else // direction == NOWHERE
	{
		result.insert(result.end(), { -1, 1 });
	}	
	
	return result;
}


void SetCarGear(CCar &car, int gear)
{
	if (car.SetGear(gear))
	{
		cout << "The car's gear has been setted successfully\n\n";
	}
	else if (!SpeedIsInGearLimit(car.GetSpeed(), gear))
	{
		cout << "The requesting gear can't be set at current speed\n";
		cout << "Now you can set gears:\n";
		cout << GearsToStr(GetAvailableGears(car.GetSpeed(), car.GetMoveDirection())) << endl << endl;
	}
	else if (!car.EngineIsTurnedOn())
	{
		cout << "The car's engine is stopped\n";
		cout << "You need to turn it on in order to be able to set a gear (except neutral gear)\n\n";
	}
	else
	{
		cout << "The new gear requires the car's direction change\n";
		cout << "In order to do it the car is needed to be stopped\n\n";
	}
}


void SetCarSpeed(CCar &car, int speed)
{
	if (car.SetSpeed(speed))
	{
		cout << "The car's speed has been set successfully\n\n";
	}
	else if (car.GetSpeed() < 0)
	{
		cout << "The speed must be 0 or positive number\n\n";
	}
	else if (car.GetGear() == 0)
	{
		cout << "The car's gear is neutral so the speed can only decrease\n";
		if ((car.GetSpeed()) > 0)
		{
			cout << "You can set a speed that is less than " << car.GetSpeed() << endl << endl;
		}
		else
		{
			cout << "The car is stopped and the speed can't be changed until another gear is selected\n\n";
		}
	}
	else if (!SpeedIsInGearLimit(speed, car.GetGear()))
	{
		cout << "Can't set such speed at current gear.\n";
		cout << "You can set any speed in range [" << GetMinGearSpeed(car.GetGear()) << "; " << GetMaxGearSpeed(car.GetGear()) << "]\n\n";
	}
}


void StopTheCar(CCar &car)
{
	if (car.TurnOffEngine())
	{
		cout << "The engine has been stopped\n\n";
	}
	else if (!car.EngineIsTurnedOn())
	{
		cout << "The engine is already stopped\n\n";
	}
	else if (car.GetGear() != 0)
	{
		cout << "The gear is not neutral. The car requires neutral gear to stop the engine\n\n";
	}
	else if (car.GetSpeed() != 0)
	{
		cout << "The car is still moving. You need to stop the car before turning the engine off\n\n";
	}
}


void StartTheCar(CCar &car)
{
	if (car.TurnOnEngine())
	{
		cout << "The engine has been started\n\n";
	}
	else
	{
		cout << "The engine is already working\n\n";
	}
}


string DirectionToString(CCar &car)
{
	string result;
	switch (car.GetMoveDirection())
	{
		case CCar::Direction::BACKWARD:
			result = "The car is moving backwards";
			break;
		case CCar::Direction::FORWARD:
			result = "The car is moving forward";
			break;
		case CCar::Direction::NOWHERE:
			result = "The car is not moving";
			break;
	}

	return result;
}


string GearToString(CCar &car)
{
	return "Gear is " + to_string(car.GetGear());
}


string SpeedToString(CCar &car)
{
	return "Speed is " + to_string(car.GetSpeed());
}


string EngineStateToString(CCar &car)
{
	string result;
	if (car.EngineIsTurnedOn())
	{
		result = "Engine is turned on";
	}
	else
	{
		result = "Engine is stopped";
	}

	return result;
}


void ShowInfo(CCar &car)
{
	cout << EngineStateToString(car) << endl;
	cout << SpeedToString(car) << endl;
	cout << GearToString(car) << endl;
	cout << DirectionToString(car) << endl << endl;
}


bool ProcessRequest(string const &userRequest, CCar &car)
{
	istringstream input(userRequest);
	string userCommand;
	input >> userCommand;
	boost::to_lower(userCommand);

	if (userCommand == "info")
	{
		ShowInfo(car);
	}
	else if (userCommand == "engineon")
	{
		StartTheCar(car);
	}
	else if (userCommand == "engineoff")
	{
		StopTheCar(car);
	}
	else if (userCommand == "setgear")
	{
		int gear;
		if (input >> gear)
		{
			SetCarGear(car, gear);
		}
		else
		{
			cout << "The gear must be an integer number\n";
		}
	}
	else if (userCommand == "setspeed")
	{
		int speed;
		if (input >> speed)
		{
			SetCarSpeed(car, speed);
		}
		else
		{
			cout << "The speed must be an integer number\n";
		}
	}
	else if (userCommand == "exit")
	{
		return false;
	}
	else
	{
		cout << "Uknown command \"" << userRequest << "\"\n\n";
	}

	return true;
}


void PrintProgramPrompt(ostream &output)
{
	output << MSG_DESCRIPTION;
	output << MSG_DELIMITER;
	output << MSG_USAGE;
	output << MSG_DELIMITER << endl;
}


void UserDialogLoop()
{
	PrintProgramPrompt(cout);
	CCar car;

	string userRequest;
	bool exitCommand = false;
	while (!exitCommand)
	{
		cout << MSG_COMMAND_PROMPT;
		cout << COMMAND_LINE_SYMBOL;
		getline(cin, userRequest);
		cout.clear();

		if (!ProcessRequest(userRequest, car))
		{
			exitCommand = true;
		}
	}
}


int _tmain()
{
	UserDialogLoop();

	return 0;
}

