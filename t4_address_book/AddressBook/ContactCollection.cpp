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

CContactCollection::SearchResults
CContactCollection::SearchByName(string const& name) const
{
	return SearchByCondition([&name](CContact const& contact)
	{
		return contact.MatchesByName(name);
	});
}

CContactCollection::SearchResults
CContactCollection::SearchByPostAddress(CPostAddress const& address) const
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByPostAddress(address);
	});
}

CContactCollection::SearchResults
CContactCollection::SearchByPhoneNumber(string const& number) const
{
	return SearchByCondition([&number](CContact const& contact)
	{
		return contact.MatchesByPhoneNumber(number);
	});
}

CContactCollection::SearchResults
CContactCollection::SearchByEmailAddress(string const& address) const
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByEmailAddress(address);
	});
}

void CContactCollection::RemoveContact(size_t elemInd)
{
	m_contacts.erase(GetContactData(elemInd));
	m_changed = true;
}

void CContactCollection::EditContact(size_t elemInd, CContact const& newData)
{
	if (elemInd >= m_contacts.size())
	{
		throw runtime_error("Index is out of bounds");
	}

	if (!CheckNewContact(newData, elemInd))
	{
		throw runtime_error("Duplicate email address found");
	}

	auto it = m_contacts.begin();
	advance(it, elemInd);

	*it = newData;
	m_changed = true;
}

size_t CContactCollection::AddContact(CContact const& contact)
{
	if (!CheckNewContact(contact, m_contacts.size()))
	{
		throw runtime_error("Duplicate email address found");
	}

	m_contacts.push_back(contact);
	m_changed = true;
	return (m_contacts.size() - 1);
}

bool CContactCollection::operator==(CContactCollection const& other) const
{
	return (m_contacts == other.m_contacts);
}

CContactCollection::List::const_iterator
CContactCollection::GetContactData(size_t index) const
{
	if (index >= m_contacts.size())
	{
		throw runtime_error("Index is out of bounds");
	}

	auto it = m_contacts.cbegin();
	advance(it, index);
	return it;
}

CContactCollection::SearchResults
CContactCollection::SearchByCondition(function<bool(CContact const&)> cond) const
{
	SearchResults results;

	SearchResult curResult;
	for (curResult.ind = 0, curResult.it = m_contacts.cbegin();
		curResult.it != m_contacts.cend(); ++curResult.ind, ++curResult.it)
	{
		assert(curResult.ind < m_contacts.size());

		if (cond(*curResult.it))
		{
			results.push_back(curResult);
		}
	}

	return results;
}

bool CContactCollection::CheckNewContact(CContact const& contact, size_t exclude) const
{
	const set<string>& contactEmails = contact.GetEmailAddresses();

	for (auto contactEmail : contactEmails)
	{
		const SearchResults foundData = SearchByEmailAddress(contactEmail);
		const bool nothingFound = foundData.empty();
		const bool onlyExcludedFound = (foundData.size() == 1 && foundData.back().ind == exclude);
		const bool emailIsNotDuplicate = (nothingFound || onlyExcludedFound);

		if (!emailIsNotDuplicate)
		{
			return false;
		}
	}

	return true;
}
