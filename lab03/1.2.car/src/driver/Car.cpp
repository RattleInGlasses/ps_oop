#include "stdafx.h"
#include <math.h>
#include "Car.h"


using namespace std;

map<int, CCar::Range> const CCar::SPEED_RANGE =
{
	{ -1, {  0,  20 } },
	{  0, {  0, 150 } },
	{  1, {  0,  30 } },
	{  2, { 20,  50 } },
	{  3, { 30,  60 } },
	{  4, { 40,  90 } },
	{  5, { 50, 150 } },
};


// private functions


bool CCar::GearForCurrentDirection(int gear) const
{
	return ((gear <= 0) && (m_direction == Direction::BACKWARD)
		|| ((gear >= 0) && (m_direction == Direction::FORWARD)));
}


bool CCar::SpeedIsInRange(int speed, int gear) const
{
	return (SPEED_RANGE.find(gear) != SPEED_RANGE.end())
		? ((speed >= SPEED_RANGE.at(gear).min) && (speed <= SPEED_RANGE.at(gear).max))
		: false;
}


// public functions


CCar::CCar() :
m_engineIsTurnedOn(false),
m_speed(0),
m_gear(0),
m_direction(Direction::NOWHERE)
{
}


bool CCar::TurnOnEngine()
{
	if (m_engineIsTurnedOn)
	{
		return false;
	}

	m_engineIsTurnedOn = true;
	return true;
}


bool CCar::TurnOffEngine()
{
	if ((!m_engineIsTurnedOn) || (m_gear != 0) || (m_speed != 0))
	{
		return false;
	}
	
	m_engineIsTurnedOn = false;
	return true;
}


bool CCar::EngineIsTurnedOn() const
{
	return m_engineIsTurnedOn;
}


bool CCar::SetGear(int gear)
{
	if ((!EngineIsTurnedOn()) && (gear != 0))
	{
		return false;
	}	
	
	if (!GearForCurrentDirection(gear) && (m_speed != 0))
	{
		return false;
	}	
	
	if (!SpeedIsInRange(m_speed, gear))
	{
		return false;
	}	
	
	m_gear = gear;

	return true;
}


int CCar::GetGear() const
{
	return m_gear;
}


bool CCar::SetSpeed(int speed)
{
	if (!EngineIsTurnedOn())
	{
		return false;
	}
	
	if ((m_gear == 0) && (speed >= m_speed))
	{
		return false;
	}
	
	if (!SpeedIsInRange(speed, m_gear))
	{
		return false;
	}
	
	m_speed = speed;

	if (speed > 0)
	{
		m_direction = (m_gear < 0) ? Direction::BACKWARD : (m_gear > 0) ? Direction::FORWARD : m_direction;
	}
	else
	{
		m_direction = Direction::NOWHERE;
	}

	return true;
}


int CCar::GetSpeed() const
{
	return m_speed;
}


CCar::Direction CCar::GetMoveDirection() const
{
	return m_direction;
}
