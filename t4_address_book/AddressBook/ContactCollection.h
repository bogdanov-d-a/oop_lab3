#pragma once

#include "Contact.h"

class CContactCollection
{
public:
	typedef std::forward_list<CContact> ContactList;
	typedef std::vector<ContactList::const_iterator> ContactListConstIterators;

	ContactListConstIterators SearchByName(std::string const& name) const;
	ContactListConstIterators SearchByPostAddress(CPostAddress const& address) const;

private:
	ContactList m_contacts;

	ContactListConstIterators SearchByCondition(
		std::function<bool(CContact const&)> statementFunction) const;
};
