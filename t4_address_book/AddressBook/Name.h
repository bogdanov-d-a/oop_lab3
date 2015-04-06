#pragma once

class CName
{
public:
	CName(std::string const& firstName, std::string const& lastName, std::string const& patronymic);
	bool CompareWithString(std::string const& str) const;

private:
	std::string m_fields[3];
	bool WordIncluded(std::string const& word) const;
};
