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

BOOST_AUTO_TEST_SUITE_END()
