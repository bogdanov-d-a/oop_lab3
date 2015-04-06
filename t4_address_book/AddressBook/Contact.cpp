#include "stdafx.h"
#include "Contact.h"

using namespace std;

CContact::CContact(CName const& name, CPostAddress const& address)
	:m_name(name)
	,m_postAddress(address)
{}

void CContact::AddPhoneNumber(string const& number)
{
	m_phoneNumbers.insert(number);
}

void CContact::AddEmailAddress(string const& address)
{
	m_emailAddresses.insert(address);
}

bool CContact::MatchesByName(string const& name) const
{
	return m_name.CompareWithString(name);
}
