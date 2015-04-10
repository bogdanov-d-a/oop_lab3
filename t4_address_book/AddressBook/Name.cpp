#include "stdafx.h"
#include "Name.h"
#include "StringUtils.h"
#include "RawDataUtils.h"

using namespace std;

CName::CName(string const& str)
	:m_str(str)
	,m_fields(GetStringWords(str))
{
	if (m_fields.empty())
	{
		throw runtime_error("Name can't be empty");
	}
}

CName::CName(istream &in)
	:CName(RawData::ReadString(in))
{}

void CName::WriteRawData(ostream &out) const
{
	RawData::WriteString(m_str, out);
}

bool CName::CompareWithString(string const& str) const
{
	const set<string> strWordSet = GetStringWords(str);

	for (auto strWord : strWordSet)
	{
		if (m_fields.find(strWord) == m_fields.cend())
		{
			return false;
		}
	}

	return true;
}

bool CName::operator==(CName const& other) const
{
	return (m_str == other.m_str);
}

string CName::GetString() const
{
	return m_str;
}
