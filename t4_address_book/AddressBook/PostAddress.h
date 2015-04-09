#pragma once

class CPostAddress
{
public:
	CPostAddress();

	CPostAddress(std::string const& city, std::string const& street,
		std::string const& building, std::string const& apartment);

	bool Compare(CPostAddress const &other) const;

private:
	std::string m_city;
	std::string m_street;
	std::string m_building;
	std::string m_apartment;

	static bool SameFields(std::string const& a, std::string const& b);
};
