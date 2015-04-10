#pragma once

class CName
{
public:
	CName(std::string const& str);
	CName(std::istream &in);
	void WriteRawData(std::ostream &out) const;
	bool CompareWithString(std::string const& str) const;
	bool operator==(CName const& other) const;
	std::string GetString() const;

private:
	std::string m_str;
	std::set<std::string> m_fields;
};
