#include "stdafx.h"
#include "Contact.h"
#include "StringUtils.h"
#include "RawDataUtils.h"

using namespace std;

CContact::CContact(CName const& name, CPostAddress const& address)
	:m_name(name)
	,m_postAddress(address)
{}

CContact::CContact(istream &in)
	:m_name(in)
	,m_postAddress(in)
	,m_phoneNumbers(RawData::ReadStringSet(in))
	,m_emailAddresses(RawData::ReadStringSet(in))
{}

void CContact::WriteRawData(ostream &out) const
{
	m_name.WriteRawData(out);
	m_postAddress.WriteRawData(out);
	RawData::WriteStringSet(m_phoneNumbers, out);
	RawData::WriteStringSet(m_emailAddresses, out);
}

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

bool CContact::operator==(const CContact &other) const
{
	return (m_name == other.m_name &&
		m_postAddress == other.m_postAddress &&
		m_phoneNumbers == other.m_phoneNumbers &&
		m_emailAddresses == other.m_emailAddresses);
}

string CContact::GetName() const
{
	return m_name.GetString();
}

void CContact::PrintPostAddress(std::ostream &out) const
{
	m_postAddress.Print(out);
}

const set<string>& CContact::GetPhoneNumbers() const
{
	return m_phoneNumbers;
}

const set<string>& CContact::GetEmailAddresses() const
{
	return m_emailAddresses;
}
