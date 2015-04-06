#include "stdafx.h"
#include "ContactCollection.h"

using namespace std;

CContactCollection::ContactListConstIterators
CContactCollection::SearchByName(string const& name) const
{
	return SearchByCondition([&name](CContact const& contact)
	{
		return contact.MatchesByName(name);
	});
}

CContactCollection::ContactListConstIterators
CContactCollection::SearchByPostAddress(CPostAddress const& address) const
{
	return SearchByCondition([&address](CContact const& contact)
	{
		return contact.MatchesByPostAddress(address);
	});
}

CContactCollection::ContactListConstIterators
CContactCollection::SearchByCondition(function<bool(CContact const&)> statementFunction) const
{
	vector<ContactList::const_iterator> result;

	for (auto contactIter = m_contacts.cbegin(); contactIter != m_contacts.cend(); ++contactIter)
	{
		if (statementFunction(*contactIter))
		{
			result.push_back(contactIter);
		}
	}

	return result;
}
