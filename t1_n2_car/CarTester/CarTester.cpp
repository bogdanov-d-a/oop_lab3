// CarTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Car/CCar.h"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

BOOST_AUTO_TEST_CASE(EngineOffByDefault)
{
	BOOST_CHECK(!car.EngineTurnedOn());
}

BOOST_AUTO_TEST_CASE(EngineCanBeTurnedOn)
{
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(car.EngineTurnedOn());
}

BOOST_AUTO_TEST_CASE(GearRangeCheckWorks)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.SetGear(-2) == CCar::SetGearResult::INCORRECT_GEAR);
	BOOST_CHECK(car.SetGear(-1) != CCar::SetGearResult::INCORRECT_GEAR);
	BOOST_CHECK(car.SetGear(5) != CCar::SetGearResult::INCORRECT_GEAR);
	BOOST_CHECK(car.SetGear(6) == CCar::SetGearResult::INCORRECT_GEAR);
}

BOOST_AUTO_TEST_CASE(CanSwitchOntoNeutralWhenOff)
{
	BOOST_CHECK(car.SetGear(0) == CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 0);

	BOOST_CHECK(car.SetGear(-1) != CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 0);

	BOOST_CHECK(car.SetGear(1) != CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 0);

	BOOST_CHECK(car.SetGear(5) != CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(BasicDrivingWithSpeedAndGear)
{
	car.TurnOnEngine();

	BOOST_CHECK(car.SetGear(1) == CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 1);

	BOOST_CHECK(car.SetSpeed(31) == CCar::SetSpeedResult::UNSUITABLE_SPEED);
	BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

	BOOST_CHECK(car.SetSpeed(15) == CCar::SetSpeedResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetSpeed(), 15);

	BOOST_CHECK(car.SetGear(2) == CCar::SetGearResult::SPEED_OUT_OF_RANGE);
	BOOST_CHECK_EQUAL(car.GetGear(), 1);

	BOOST_CHECK(car.SetSpeed(30) == CCar::SetSpeedResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetSpeed(), 30);

	BOOST_CHECK(car.SetGear(2) == CCar::SetGearResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetGear(), 2);

	BOOST_CHECK(car.SetSpeed(40) == CCar::SetSpeedResult::SUCCESS);
	BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
}

BOOST_AUTO_TEST_CASE(SpeedIsNeverNegative)
{
	car.TurnOnEngine();
	car.SetGear(1);

	BOOST_CHECK(car.SetSpeed(-1) == CCar::SetSpeedResult::OUT_OF_RANGE);
	BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
}

BOOST_AUTO_TEST_CASE(NeutralGearSlowdownOnly)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	BOOST_CHECK(car.SetGear(0) == CCar::SetGearResult::SUCCESS);

	BOOST_CHECK(car.SetSpeed(31) == CCar::SetSpeedResult::NO_SLOWDOWN_ON_NEUTRAL);
	BOOST_CHECK(car.SetSpeed(30) == CCar::SetSpeedResult::NO_SLOWDOWN_ON_NEUTRAL);
	BOOST_CHECK(car.SetSpeed(29) == CCar::SetSpeedResult::SUCCESS);
}

BOOST_AUTO_TEST_CASE(NoReverseWhileMovingForward)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(1);
	BOOST_CHECK(car.SetGear(-1) == CCar::SetGearResult::UNSUITABLE_DIRECTION);
}

BOOST_AUTO_TEST_CASE(NoForwardGearWhileMovingBackward)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(1);
	BOOST_CHECK(car.SetGear(0) == CCar::SetGearResult::SUCCESS);
	BOOST_CHECK(car.SetGear(1) == CCar::SetGearResult::UNSUITABLE_DIRECTION);
}

BOOST_AUTO_TEST_CASE(EngineCanBeTurnedOffOnlyIfCarStillAndGearNeutral)
{
	car.TurnOnEngine();

	car.SetGear(1);
	BOOST_CHECK(!car.TurnOffEngine());
	BOOST_CHECK(car.EngineTurnedOn());

	car.SetSpeed(1);
	BOOST_CHECK(!car.TurnOffEngine());
	BOOST_CHECK(car.EngineTurnedOn());

	car.SetGear(0);
	BOOST_CHECK(!car.TurnOffEngine());
	BOOST_CHECK(car.EngineTurnedOn());

	car.SetSpeed(0);
	BOOST_CHECK(car.TurnOffEngine());
	BOOST_CHECK(!car.EngineTurnedOn());
}

BOOST_AUTO_TEST_CASE(TurnEngineOnTwice)
{
	car.TurnOnEngine();
	BOOST_CHECK(!car.TurnOnEngine());
	BOOST_CHECK(car.EngineTurnedOn());
}

BOOST_AUTO_TEST_CASE(TurnEngineOffTwice)
{
	car.TurnOffEngine();
	BOOST_CHECK(!car.TurnOffEngine());
	BOOST_CHECK(!car.EngineTurnedOn());
}

BOOST_AUTO_TEST_CASE(SetGearToSameMode)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	BOOST_CHECK(car.SetGear(-1) == CCar::SetGearResult::SUCCESS);
}

BOOST_AUTO_TEST_SUITE_END()
