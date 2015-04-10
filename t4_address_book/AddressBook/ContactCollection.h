#pragma once

#include "Contact.h"

class CContactCollection
{
public:
	void ReadRawData(std::istream &in);
	void WriteRawData(std::ostream &out) const;

	typedef std::list<CContact> ContactList;
	typedef std::vector<ContactList::iterator> ContactListIterators;

	ContactListIterators SearchByName(std::string const& name);
	ContactListIterators SearchByPostAddress(CPostAddress const& address);
	ContactListIterators SearchByPhoneNumber(std::string const& number);
	ContactListIterators SearchByEmailAddress(std::string const& address);

	void RemoveContact(ContactList::iterator elemIter);
	void EditContact(ContactList::iterator elemIter, CContact const& newData);
	void AddContact(CContact const& contact);

	bool operator==(CContactCollection const& other) const;

private:
	ContactList m_contacts;
	ContactListIterators SearchByCondition(std::function<bool(CContact const&)> statementFunction);
};
