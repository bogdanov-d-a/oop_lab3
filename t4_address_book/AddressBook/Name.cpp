#include "stdafx.h"
#include "Name.h"
#include "StringUtils.h"

using namespace std;

CName::CName(string const& firstName, string const& lastName, string const& patronymic)
{
	m_fields[0] = firstName;
	m_fields[1] = lastName;
	m_fields[2] = patronymic;
}

bool CName::CompareWithString(string const& str) const
{
	set<string> strWordSet = GetStringWords(str);

	for (auto strWord : strWordSet)
	{
		if (!WordIncluded(strWord))
		{
			return false;
		}
	}

	return true;
}

bool CName::WordIncluded(std::string const& word) const
{
	for (auto field : m_fields)
	{
		if (CaseInsensitiveMatch(word, field))
		{
			return true;
		}
	}
	
	return false;
}
