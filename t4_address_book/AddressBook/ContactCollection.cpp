#include "stdafx.h"
#include "ContactCollection.h"

using namespace std;

vector<CContactCollection::ContactList::const_iterator> CContactCollection::SearchByName(string const& name) const
{
	vector<ContactList::const_iterator> result;

	for (auto contactIter = m_contacts.cbegin(); contactIter != m_contacts.cend(); ++contactIter)
	{
		if (contactIter->MatchesByName(name))
		{
			result.push_back(contactIter);
		}
	}

	return result;
}
