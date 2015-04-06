#pragma once

#include "Name.h"
#include "PostAddress.h"

class CContact
{
public:
	CContact(CName const& name, CPostAddress const& address);
	void AddPhoneNumber(std::string const& number);
	void AddEmailAddress(std::string const& address);
	bool MatchesByName(std::string const& name) const;
	bool MatchesByPostAddress(CPostAddress const& address) const;

private:
	CName m_name;
	CPostAddress m_postAddress;
	std::set<std::string> m_phoneNumbers;
	std::set<std::string> m_emailAddresses;
};
