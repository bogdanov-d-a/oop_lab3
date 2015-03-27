#include "stdafx.h"
#include "CCar.h"

CCar::CCar():
	m_isTurnedOn(false),
	m_direction(Direction::STILL),
	m_speed(0),
	m_gear(0)
{}

bool CCar::TurnOnEngine()
{
	const bool success = !m_isTurnedOn;
	m_isTurnedOn = true;
	return success;
}

bool CCar::TurnOffEngine()
{
	if (!m_isTurnedOn)
	{
		return false;
	}

	m_isTurnedOn = !(m_gear == 0 && m_direction == Direction::STILL);
	return !m_isTurnedOn;
}

CCar::SetSpeedResult CCar::SetSpeed(Speed speed)
{
	if (speed < 0)
	{
		return SetSpeedResult::OUT_OF_RANGE;
	}

	if (m_gear == 0)
	{
		if (speed >= m_speed)
		{
			return SetSpeedResult::NO_SLOWDOWN_ON_NEUTRAL;
		}

		if (speed == 0)
		{
			m_direction = Direction::STILL;
		}

		m_speed = speed;
		return SetSpeedResult::SUCCESS;
	}

	if (!SpeedMatchesGear(speed, m_gear))
	{
		return SetSpeedResult::UNSUITABLE_SPEED;
	}

	m_speed = speed;
	m_direction = (m_gear < 0 ? Direction::BACKWARD : Direction::FORWARD);
	return SetSpeedResult::SUCCESS;
}

CCar::SetGearResult CCar::SetGear(Gear gear)
{
	if (gear < GEAR_MIN || gear > GEAR_MAX)
	{
		return SetGearResult::INCORRECT_GEAR;
	}

	if (!m_isTurnedOn && gear != 0)
	{
		return SetGearResult::ENGINE_OFF;
	}

	if (!SpeedMatchesGear(m_speed, gear))
	{
		return SetGearResult::SPEED_OUT_OF_RANGE;
	}

	if (gear < 0 && m_direction == Direction::FORWARD || gear > 0 && m_direction == Direction::BACKWARD)
	{
		return SetGearResult::UNSUITABLE_DIRECTION;
	}

	m_gear = gear;
	return SetGearResult::SUCCESS;
}

const std::map<CCar::Gear, Range<CCar::Speed>> CCar::GearSpeedRanges = {
	{ -1, { 0, 20 } },
	{ 0, { 0, SPEED_MAX } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

bool CCar::SpeedMatchesGear(Speed speed, Gear gear)
{
	return GearSpeedRanges.find(gear)->second.In(speed);
}

bool CCar::EngineTurnedOn() const
{
	return m_isTurnedOn;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

CCar::Speed CCar::GetSpeed() const
{
	return m_speed;
}

CCar::Gear CCar::GetGear() const
{
	return m_gear;
}
