#include "stdafx.h"
#include "../driver/Car.h"

BOOST_AUTO_TEST_SUITE(CarTests)

	struct CreatedCar
	{
		CCar car;
	};
	struct TurnedOnCar : CreatedCar
	{
		TurnedOnCar()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_CASE(Default_state_is_stopped, CreatedCar)
	{
		BOOST_CHECK(!car.EngineIsTurnedOn());
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::NOWHERE);
	}

	BOOST_FIXTURE_TEST_SUITE(Can_be_turned_on, CreatedCar)
		BOOST_AUTO_TEST_CASE(after_create)
		{
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.EngineIsTurnedOn());			
		}	

		BOOST_AUTO_TEST_CASE(after_stop)
		{
			car.TurnOnEngine();
			car.TurnOffEngine();

			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.EngineIsTurnedOn());
		}
	BOOST_AUTO_TEST_SUITE_END()	

	BOOST_FIXTURE_TEST_CASE(Cant_be_turned_on_when_it_already_is, TurnedOnCar)
	{		
		BOOST_CHECK(!car.TurnOnEngine());
		BOOST_CHECK(car.EngineIsTurnedOn());
	}

	BOOST_FIXTURE_TEST_SUITE(Can_be_turned_off, TurnedOnCar)
		BOOST_AUTO_TEST_CASE(after_start)
		{
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.EngineIsTurnedOn());
		}
		
		BOOST_AUTO_TEST_CASE(after_move_and_stop)
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(10);
			car.SetGear(0);
			car.SetSpeed(0);
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.EngineIsTurnedOn());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Cant_be_turned_off)
		BOOST_FIXTURE_TEST_CASE(after_create, CreatedCar)
		{
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(!car.EngineIsTurnedOn());
		}

		BOOST_FIXTURE_TEST_CASE(after_stop, TurnedOnCar)
		{
			car.TurnOffEngine();
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(!car.EngineIsTurnedOn());
		}

		BOOST_FIXTURE_TEST_CASE(when_gear_is_not_neutral, TurnedOnCar)
		{
			car.SetGear(1);
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(car.EngineIsTurnedOn());
		}
						
		BOOST_FIXTURE_TEST_CASE(when_speed_is_not_zero, TurnedOnCar)
		{
			car.SetGear(1);
			car.SetSpeed(10);
			car.SetGear(0);
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(car.EngineIsTurnedOn());
		}
	BOOST_AUTO_TEST_SUITE_END()
	

	void CheckSetFullRangeOfSpeedsByGear(CCar &car, int gear)
	{	
		BOOST_CHECK(car.SetGear(gear));
		BOOST_REQUIRE_EQUAL(car.GetGear(), gear);

		for (int v = CCar::SPEED_RANGE.at(gear).min; v <= CCar::SPEED_RANGE.at(gear).max; ++v)
		{
			BOOST_CHECK(car.SetSpeed(v));
			BOOST_CHECK_EQUAL(car.GetSpeed(), v);
		}
	}

	void CheckSetSpeedNeutralGearDeceleration(CCar &car)
	{
		int initialSpeed = car.GetSpeed();
		BOOST_REQUIRE(initialSpeed != 0);
		car.SetGear(0);
		BOOST_REQUIRE_EQUAL(car.GetGear(), 0);

		BOOST_CHECK(car.SetSpeed(initialSpeed - 1));
		BOOST_CHECK_EQUAL(car.GetSpeed(), initialSpeed - 1);
		BOOST_CHECK(car.SetSpeed(0));
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_FIXTURE_TEST_CASE(Can_set_speed, TurnedOnCar)
	{
		CheckSetFullRangeOfSpeedsByGear(car, -1);
		car.SetSpeed(0);
		CheckSetFullRangeOfSpeedsByGear(car, 1);
		CheckSetFullRangeOfSpeedsByGear(car, 2);
		CheckSetFullRangeOfSpeedsByGear(car, 3);
		CheckSetFullRangeOfSpeedsByGear(car, 4);
		CheckSetFullRangeOfSpeedsByGear(car, 5);
		
		CheckSetSpeedNeutralGearDeceleration(car);
	}

	void CheckSetSpeedErrorOutOfGearLimit(CCar &car, int gear)
	{
		car.SetSpeed(CCar::SPEED_RANGE.at(gear).min);
		BOOST_REQUIRE_EQUAL(car.GetSpeed(), CCar::SPEED_RANGE.at(gear).min);		
		car.SetGear(gear);
		BOOST_REQUIRE_EQUAL(car.GetGear(), gear);

		int lastSpeed = car.GetSpeed();
		BOOST_CHECK(!car.SetSpeed(CCar::SPEED_RANGE.at(gear).min - 1));
		BOOST_CHECK_EQUAL(car.GetSpeed(), lastSpeed);
		BOOST_CHECK(!car.SetSpeed(CCar::SPEED_RANGE.at(gear).max + 1));
		BOOST_CHECK_EQUAL(car.GetSpeed(), lastSpeed);
	}

	void CheckSetSpeedErrorNeutralGearAcceleration(CCar &car)
	{
		int initialSpeed = car.GetSpeed();
		BOOST_REQUIRE(initialSpeed != 0);
		car.SetGear(0);
		BOOST_REQUIRE_EQUAL(car.GetGear(), 0);

		BOOST_CHECK(!car.SetSpeed(initialSpeed + 1));
		BOOST_CHECK_EQUAL(car.GetSpeed(), initialSpeed);
		BOOST_CHECK(!car.SetSpeed(initialSpeed + 0));
		BOOST_CHECK_EQUAL(car.GetSpeed(), initialSpeed);
	}

	void CheckSetSpeedErrorTurnedOffEngine(CCar &car)
	{
		car.SetGear(0);
		car.SetSpeed(0);
		car.TurnOffEngine();
		BOOST_REQUIRE_EQUAL(car.EngineIsTurnedOn(), false);

		BOOST_CHECK_EQUAL(car.SetSpeed(1), false);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		BOOST_CHECK_EQUAL(car.SetSpeed(10), false);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		BOOST_CHECK_EQUAL(car.SetSpeed(0), false);
	}

	BOOST_FIXTURE_TEST_SUITE(Cant_set_speed, TurnedOnCar)
		BOOST_AUTO_TEST_CASE(that_is_out_of_gear_limit, TurnedOnCar)
		{
			CheckSetSpeedErrorOutOfGearLimit(car, -1);
			CheckSetSpeedErrorOutOfGearLimit(car, 1);
			CheckSetSpeedErrorOutOfGearLimit(car, 2);
			CheckSetSpeedErrorOutOfGearLimit(car, 3);
			CheckSetSpeedErrorOutOfGearLimit(car, 4);
			CheckSetSpeedErrorOutOfGearLimit(car, 5);
		}

		BOOST_AUTO_TEST_CASE(to_acclerate_on_neutral_gear)
		{
			car.SetGear(1);
			car.SetSpeed(10);
			CheckSetSpeedErrorNeutralGearAcceleration(car);
		}
			
		BOOST_AUTO_TEST_CASE(when_engine_is_turned_off)
		{
			car.TurnOffEngine();
			CheckSetSpeedErrorTurnedOffEngine(car);
		}
	BOOST_AUTO_TEST_SUITE_END()
	

	void CheckSetSpecificGear(CCar &car, int gear)
	{
		for (int v = CCar::SPEED_RANGE.at(gear).min; v < CCar::SPEED_RANGE.at(gear).max; ++v)
		{
			car.SetSpeed(v);
			BOOST_REQUIRE_EQUAL(car.GetSpeed(), v);

			BOOST_CHECK(car.SetGear(gear));
			BOOST_CHECK_EQUAL(car.GetGear(), gear);
		}
	}

	void CheckSetNeutalGear(CCar &car)
	{
		BOOST_CHECK(car.SetGear(0));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

	void CheckSetNeutralGearFromAllGears(CCar &car)
	{
		car.SetSpeed(0);
		CheckSetNeutalGear(car);
		
		car.SetGear(-1);
		CheckSetNeutalGear(car);
		for (int gear = 1; gear <= 5; ++gear)
		{
			car.SetSpeed(CCar::SPEED_RANGE.at(gear).min);
			car.SetGear(gear);
			CheckSetNeutalGear(car);
			car.SetGear(gear);
		}
	}

	BOOST_AUTO_TEST_CASE(SetGear)
	{
		CCar car;
		car.TurnOnEngine();
		
		CheckSetSpecificGear(car, -1);
		car.SetSpeed(0);
		CheckSetSpecificGear(car, 1);
		CheckSetSpecificGear(car, 2);
		CheckSetSpecificGear(car, 3);
		CheckSetSpecificGear(car, 4);
		CheckSetSpecificGear(car, 5);

		CheckSetNeutralGearFromAllGears(car);
	}

	// speed < 0 - car will be moving backwards
	// speed > 0 - car will be moving forward
	void SetSpecificSpeed(CCar &car, int speed)
	{
		car.SetGear(0);
		car.SetSpeed(0);
		
		int gear = (speed == 0) ? 0 : (speed < 0) ? -1 : 1;
		int curSpeed = 0;

		car.SetGear(gear);
		car.SetSpeed(curSpeed);

		while (curSpeed != speed)
		{
			curSpeed = (speed > 0) ? ++curSpeed : --curSpeed;

			if (curSpeed > CCar::SPEED_RANGE.at(gear).max)
			{
				++gear;
			}

			car.SetGear(gear);
			car.SetSpeed(abs(curSpeed));
		}
	}

	void CheckSetGearError(CCar &car, int gear)
	{
		int lastGear = car.GetGear();
		BOOST_CHECK(!car.SetGear(gear));
		BOOST_CHECK_EQUAL(car.GetGear(), lastGear);
	}

	bool SpeedIsOutOfRange(int speed, int gear)
	{
		//speed = (gear < 0) ? (-1 * speed) : speed;
		int minSpeed = (gear < 0) ? (-1 * CCar::SPEED_RANGE.at(gear).max) : CCar::SPEED_RANGE.at(gear).min;
		int maxSpeed = (gear < 0) ? (-1 * CCar::SPEED_RANGE.at(gear).min) : CCar::SPEED_RANGE.at(gear).max;
		return ((speed < minSpeed) || (speed > maxSpeed));
	}

	void CheckSetGearErrorSpeedOutOfRangeAllSpeeds(CCar &car, int gear)
	{
		const int SPEED_MIN = -1 * CCar::SPEED_RANGE.at(-1).max;
		const int SPEED_MAX = CCar::SPEED_RANGE.at(5).max;
		
		for (int v = SPEED_MIN; v <= SPEED_MAX; ++v)
		{
			if (SpeedIsOutOfRange(v, gear))
			{
				SetSpecificSpeed(car, v);
				CheckSetGearError(car, gear);
			}
		}
	}

	void CheckSetGearErrorTurnedOffEngine(CCar &car)
	{
		car.SetGear(0);
		car.SetSpeed(0);
		car.TurnOffEngine();
		BOOST_REQUIRE(!car.EngineIsTurnedOn());

		BOOST_CHECK(!car.SetGear(-1));
		BOOST_CHECK(!car.SetGear(1));
		BOOST_CHECK(!car.SetGear(2));
		BOOST_CHECK(!car.SetGear(3));
		BOOST_CHECK(!car.SetGear(4));
		BOOST_CHECK(!car.SetGear(5));
	}

	void CheckChangingDirectionError(CCar &car, int gear1, int gear2)
	{
		car.SetGear(0);
		car.SetSpeed(0);

		car.SetGear(gear1);
		car.SetSpeed(10);
		car.SetGear(0);
		BOOST_REQUIRE_EQUAL(car.GetGear(), 0);		
		BOOST_REQUIRE_EQUAL(car.GetSpeed(), 10);

		BOOST_CHECK(!car.SetGear(gear2));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

	BOOST_FIXTURE_TEST_SUITE(Cant_set_gear, TurnedOnCar)
		BOOST_AUTO_TEST_CASE(when_speed_is_out_of_range)
		{
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, -1);
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, 1);
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, 2);
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, 3);
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, 4);
			CheckSetGearErrorSpeedOutOfRangeAllSpeeds(car, 5);
		}

		BOOST_AUTO_TEST_CASE(when_engine_is_turned_off)
		{
			CheckSetGearErrorTurnedOffEngine(car);
		}

		BOOST_AUTO_TEST_CASE(when_it_requires_of_changing_the_direction)
		{
			CheckChangingDirectionError(car, 1, -1);
			CheckChangingDirectionError(car, -1, 1);
		}
	BOOST_AUTO_TEST_SUITE_END()


	void SetSpecificGear(CCar &car, int gear)
	{
		car.SetGear(0);
		car.SetSpeed(0);
		for (int g = 0; g != gear;)
		{
			g = (gear > 0) ? ++g : --g;
			car.SetSpeed(CCar::SPEED_RANGE.at(g).min);
			car.SetGear(g);
		}
	}

	BOOST_AUTO_TEST_CASE(Move_direction_can_be_changed)
	{
		CCar car;
		car.TurnOnEngine();
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::NOWHERE);

		SetSpecificGear(car, 1);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::NOWHERE);
		car.SetSpeed(10);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::FORWARD);

		SetSpecificGear(car, -1);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::NOWHERE);
		car.SetSpeed(10);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::BACKWARD);

		car.SetSpeed(0);
		BOOST_CHECK(car.GetMoveDirection() == CCar::Direction::NOWHERE);
	}

BOOST_AUTO_TEST_SUITE_END()
