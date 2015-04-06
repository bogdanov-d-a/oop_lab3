#pragma once

#include "Contact.h"

class CContactCollection
{
public:
	typedef std::forward_list<CContact> ContactList;

	std::vector<ContactList::const_iterator> SearchByName(std::string const& name) const;

private:
	ContactList m_contacts;
};
