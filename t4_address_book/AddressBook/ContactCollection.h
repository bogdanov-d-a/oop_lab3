#pragma once

#include "Contact.h"

class CContactCollection
{
public:
	typedef std::list<CContact> List;
	typedef std::vector<List::iterator> ListIterators;

	CContactCollection();
	void ReadRawData(std::istream &in);
	void WriteRawData(std::ostream &out) const;
	bool ChangedSinceLastRawDataReading() const;

	ListIterators SearchByName(std::string const& name);
	ListIterators SearchByPostAddress(CPostAddress const& address);
	ListIterators SearchByPhoneNumber(std::string const& number);
	ListIterators SearchByEmailAddress(std::string const& address);

	void RemoveContact(List::iterator elemIter);
	void EditContact(List::iterator elemIter, CContact const& newData);
	List::iterator AddContact(CContact const& contact);

	bool operator==(CContactCollection const& other) const;

private:
	List m_contacts;
	bool m_changed;

	ListIterators SearchByCondition(std::function<bool(CContact const&)> statementFunction);
	bool CheckNewContact(CContact const& contact, List::iterator exclude);
};
