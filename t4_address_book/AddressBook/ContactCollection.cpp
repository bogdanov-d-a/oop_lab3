#include "stdafx.h"
#include "ContactCollection.h"
#include "RawDataUtils.h"

using namespace std;

CContactCollection::CContactCollection()
	:m_changed(false)
{}

void CContactCollection::ReadRawData(istream &in)
{
	m_contacts.clear();
	const size_t size = RawData::ReadSizeUntilStopChar(in);
	for (size_t i = 0; i < size; ++i)
	{
		m_contacts.push_back(CContact(in));
	}

	m_changed = false;
}

void CContactCollection::WriteRawData(ostream &out) const
{
	out << m_contacts.size();
	out.put(RawData::STOP_CHAR);

	for (auto contact : m_contacts)
	{
		contact.WriteRawData(out);
	}
}

bool CContactCollection::ChangedSinceLastRawDataReading() const
{
	return m_changed;
}

CContactCollection::ListIterators
CContactCollection::SearchByName(string const& name)
{
	return SearchByCondition([&name](CContact const& contact)
	{
		return contact.MatchesByName(name);
	});
}

CContactCollection::ListIterators
CContactCollection::SearchByPostAddress(CPostAddress const& address)
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByPostAddress(address);
	});
}

CContactCollection::ListIterators
CContactCollection::SearchByPhoneNumber(string const& number)
{
	return SearchByCondition([&number](CContact const& contact)
	{
		return contact.MatchesByPhoneNumber(number);
	});
}

CContactCollection::ListIterators
CContactCollection::SearchByEmailAddress(string const& address)
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByEmailAddress(address);
	});
}

void CContactCollection::RemoveContact(List::iterator elemIter)
{
	m_contacts.erase(elemIter);
	m_changed = true;
}

void CContactCollection::EditContact(List::iterator elemIter, CContact const& newData)
{
	*elemIter = newData;
	m_changed = true;
}

void CContactCollection::AddContact(CContact const& contact)
{
	m_contacts.push_back(contact);
	m_changed = true;
}

bool CContactCollection::operator==(CContactCollection const& other) const
{
	return (m_contacts == other.m_contacts);
}

CContactCollection::ListIterators
CContactCollection::SearchByCondition(function<bool(CContact const&)> statementFunction)
{
	vector<List::iterator> result;

	for (auto contactIter = m_contacts.begin(); contactIter != m_contacts.end(); ++contactIter)
	{
		if (statementFunction(*contactIter))
		{
			result.push_back(contactIter);
		}
	}

	return result;
}
