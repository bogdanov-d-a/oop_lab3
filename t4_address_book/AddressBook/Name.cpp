#include "stdafx.h"
#include "Name.h"
#include "StringUtils.h"

using namespace std;

CName::CName(string const& str)
	:m_str(str)
	,m_fields(GetStringWords(str))
{
	if (m_fields.empty())
	{
		throw invalid_argument("Name can't be empty");
	}
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
