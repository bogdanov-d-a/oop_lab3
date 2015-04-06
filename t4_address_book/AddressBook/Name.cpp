#include "stdafx.h"
#include "Name.h"
#include "StringUtils.h"

using namespace std;

CName::CName(string const& str)
	:m_str(str)
	,m_fields(GetStringWords(str))
{}

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
