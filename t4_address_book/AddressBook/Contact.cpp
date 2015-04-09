#include "stdafx.h"
#include "Contact.h"
#include "StringUtils.h"

using namespace std;

CContact::CContact(CName const& name, CPostAddress const& address)
	:m_name(name)
	,m_postAddress(address)
{}

void CContact::AddPhoneNumber(string const& number)
{
	m_phoneNumbers.insert(ToLower(number));
}

void CContact::AddEmailAddress(string const& address)
{
	m_emailAddresses.insert(ToLower(address));
}

bool CContact::MatchesByName(string const& name) const
{
	return m_name.CompareWithString(name);
}

bool CContact::MatchesByPostAddress(CPostAddress const& address) const
{
	return (m_postAddress.Compare(address));
}

bool CContact::MatchesByPhoneNumber(string const& number) const
{
	return (m_phoneNumbers.find(ToLower(number)) != m_phoneNumbers.cend());
}

bool CContact::MatchesByEmailAddress(string const& address) const
{
	return (m_emailAddresses.find(ToLower(address)) != m_emailAddresses.cend());
}
