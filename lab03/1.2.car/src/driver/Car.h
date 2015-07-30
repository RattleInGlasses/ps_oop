#pragma once
#include <map>

class CCar
{
public:
	enum class Direction
	{
		BACKWARD,
		FORWARD,
		NOWHERE
	};

	struct Range
	{
		int min;
		int max;
	};

public:
	CCar();
	~CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool EngineIsTurnedOn() const;
	bool SetGear(int gear);
	int GetGear() const;
	bool SetSpeed(int speed);
	int GetSpeed() const;
	Direction GetMoveDirection() const;

private:
	bool GearForCurrentDirection(int gear) const;
	bool SpeedIsInRange(int speed, int gear) const;

public:
	std::map<int, CCar::Range> const static SPEED_RANGE;

private:
	bool m_engineIsTurnedOn;
	Direction m_direction;
	int m_speed;
	int m_gear;
};

