#pragma once

class CName
{
public:
	CName(std::string const& str);
	bool CompareWithString(std::string const& str) const;

private:
	std::string m_str;
	std::set<std::string> m_fields;
};
