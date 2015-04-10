#pragma once

class CPostAddress
{
public:
	CPostAddress();

	CPostAddress(std::string const& city, std::string const& street,
		std::string const& building, std::string const& apartment);

	CPostAddress(std::istream &in);
	void WriteRawData(std::ostream &out) const;
	bool Compare(CPostAddress const &other) const;
	bool operator==(CPostAddress const &other) const;
	void Print(std::ostream &out) const;

private:
	std::string m_city;
	std::string m_street;
	std::string m_building;
	std::string m_apartment;

	static bool SameFields(std::string const& a, std::string const& b);
	static void PrintIfNotEmpty(std::string const& announce,
		std::string const& data, std::ostream &out);
};
