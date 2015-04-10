#pragma once

#include "Name.h"
#include "PostAddress.h"

class CContact
{
public:
	CContact(CName const& name, CPostAddress const& address);

	CContact(CName const& name, CPostAddress const& address,
		std::set<std::string> const& phoneNumbers, std::set<std::string> const& emailAdresses);

	CContact(std::istream &in);
	void WriteRawData(std::ostream &out) const;

	void AddPhoneNumber(std::string const& number);
	void AddEmailAddress(std::string const& address);

	bool MatchesByName(std::string const& name) const;
	bool MatchesByPostAddress(CPostAddress const& address) const;
	bool MatchesByPhoneNumber(std::string const& number) const;
	bool MatchesByEmailAddress(std::string const& address) const;
	bool operator==(const CContact &other) const;

	std::string GetName() const;
	void PrintPostAddress(std::ostream &out) const;
	const std::set<std::string>& GetPhoneNumbers() const;
	const std::set<std::string>& GetEmailAddresses() const;

private:
	CName m_name;
	CPostAddress m_postAddress;
	std::set<std::string> m_phoneNumbers;
	std::set<std::string> m_emailAddresses;
};
