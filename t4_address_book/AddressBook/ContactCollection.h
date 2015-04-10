#pragma once

#include "Contact.h"

class CContactCollection
{
public:
	typedef std::list<CContact> List;
	struct SearchResult
	{
		List::const_iterator it;
		size_t ind;
	};
	typedef std::vector<SearchResult> SearchResults;

	CContactCollection();
	void ReadRawData(std::istream &in);
	void WriteRawData(std::ostream &out) const;
	bool ChangedSinceLastRawDataReading() const;

	SearchResults SearchByName(std::string const& name) const;
	SearchResults SearchByPostAddress(CPostAddress const& address) const;
	SearchResults SearchByPhoneNumber(std::string const& number) const;
	SearchResults SearchByEmailAddress(std::string const& address) const;

	void RemoveContact(size_t elemInd);
	void EditContact(size_t elemInd, CContact const& newData);
	size_t AddContact(CContact const& contact);

	bool operator==(CContactCollection const& other) const;
	List::const_iterator GetContactData(size_t index) const;

private:
	List m_contacts;
	bool m_changed;

	SearchResults SearchByCondition(std::function<bool(CContact const&)> cond) const;
	bool CheckNewContact(CContact const& contact, size_t exclude) const;
};
