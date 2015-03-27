#pragma once

#include "Range.h"

class CCar
{
public:
	enum class Direction { FORWARD, STILL, BACKWARD };
	typedef int Speed;
	typedef int Gear;

	enum class SetGearResult {
		SUCCESS,
		INCORRECT_GEAR,
		SPEED_OUT_OF_RANGE,
		UNSUITABLE_DIRECTION };

	enum class SetSpeedResult {
		SUCCESS,
		OUT_OF_RANGE,
		UNSUITABLE_SPEED,
		ACCELERATION_ON_NEUTRAL };

	static const Gear GEAR_MIN = -1;
	static const Gear GEAR_MAX = 5;

	CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	SetSpeedResult SetSpeed(Speed speed);
	SetGearResult SetGear(Gear gear);
	bool EngineTurnedOn() const;
	Direction GetDirection() const;
	Speed GetSpeed() const;
	Gear GetGear() const;

private:
	static const int SPEED_MAX = INT_MAX;
	static const std::map<Gear, Range<Speed>> GearSpeedRanges;

	bool m_isTurnedOn;
	Direction m_direction;
	Speed m_speed;
	Gear m_gear;

	static bool SpeedMatchesGear(Speed speed, Gear gear);
};
