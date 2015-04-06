#include "stdafx.h"
#include "ContactCollection.h"

using namespace std;

CContactCollection::ContactListIterators
CContactCollection::SearchByName(string const& name)
{
	return SearchByCondition([&name](CContact const& contact)
	{
		return contact.MatchesByName(name);
	});
}

CContactCollection::ContactListIterators
CContactCollection::SearchByPostAddress(CPostAddress const& address)
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByPostAddress(address);
	});
}

CContactCollection::ContactListIterators
CContactCollection::SearchByPhoneNumber(string const& number)
{
	return SearchByCondition([&number](CContact const& contact)
	{
		return contact.MatchesByPhoneNumber(number);
	});
}

CContactCollection::ContactListIterators
CContactCollection::SearchByEmailAddress(string const& address)
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByEmailAddress(address);
	});
}

void CContactCollection::RemoveContact(ContactList::iterator elemIter)
{
	m_contacts.erase(elemIter);
}

void CContactCollection::EditContact(ContactList::iterator elemIter, CContact const& newData)
{
	*elemIter = newData;
}

CContactCollection::ContactListIterators
CContactCollection::SearchByCondition(function<bool(CContact const&)> statementFunction)
{
	vector<ContactList::iterator> result;

	for (auto contactIter = m_contacts.begin(); contactIter != m_contacts.end(); ++contactIter)
	{
		if (statementFunction(*contactIter))
		{
			result.push_back(contactIter);
		}
	}

	return result;
}
