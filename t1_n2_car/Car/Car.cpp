// Car.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CCar.h"

std::string DirectionToString(CCar::Direction dir)
{
	switch (dir)
	{
	case CCar::Direction::FORWARD:
		return "moving forward";
	case CCar::Direction::STILL:
		return "still";
	case CCar::Direction::BACKWARD:
		return "moving backward";
	default:
		assert(false);
		return "undefined";
	}
}

bool ParseGiveIntCommand(std::string const& str, std::string const& matchStr, int &outVal)
{
	if (str.length() <= matchStr.length())
	{
		return false;
	}

	if (str.substr(0, matchStr.length()) != matchStr)
	{
		return false;
	}

	try
	{
		outVal = std::stoi(str.substr(matchStr.length()));
		return true;
	}
	catch (std::invalid_argument const& e)
	{
		(void)e;
		return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CCar car;

	std::string userStr;
	while (std::getline(std::cin, userStr))
	{
		int tmpVal;

		if (userStr == "Info")
		{
			std::cout << "Engine is " << (car.EngineTurnedOn() ? "on" : "off") << "\n";
			std::cout << "Car is " << DirectionToString(car.GetDirection()) << "\n";
			std::cout << "Speed is " << car.GetSpeed() << "\n";
			std::cout << "Gear is " << car.GetGear() << "\n";
		}
		else if (userStr == "EngineOn")
		{
			if (!car.TurnOnEngine())
			{
				std::cout << "Could not turn engine on\n";
			}
		}
		else if (userStr == "EngineOff")
		{
			if (!car.TurnOffEngine())
			{
				std::cout << "Could not turn engine off\n";
			}
		}
		else if (ParseGiveIntCommand(userStr, "SetGear ", tmpVal))
		{
			switch (car.SetGear(tmpVal))
			{
			case CCar::SetGearResult::INCORRECT_GEAR:
				std::cout << "Gear is not valid\n";
				break;
			case CCar::SetGearResult::SPEED_OUT_OF_RANGE:
				std::cout << "Can't switch gear because of current speed\n";
				break;
			case CCar::SetGearResult::UNSUITABLE_DIRECTION:
				std::cout << "Direction can't be changed so rapidly\n";
				break;
			case CCar::SetGearResult::ENGINE_OFF:
				std::cout << "Can't set non-neutral gear while engine is off\n";
			}
		}
		else if (ParseGiveIntCommand(userStr, "SetSpeed ", tmpVal))
		{
			switch (car.SetSpeed(tmpVal))
			{
			case CCar::SetSpeedResult::OUT_OF_RANGE:
				std::cout << "Speed is out of range\n";
				break;
			case CCar::SetSpeedResult::UNSUITABLE_SPEED:
				std::cout << "Speed is not suitable for this gear\n";
				break;
			case CCar::SetSpeedResult::NO_SLOWDOWN_ON_NEUTRAL:
				std::cout << "On neutral gear slowdown is required\n";
			}
		}
		else
		{
			std::cout << "Unknown command\n";
		}
	}

	return 0;
}
