#include "stdafx.h"
#include "PostAddress.h"
#include "StringUtils.h"
#include "RawDataUtils.h"

using namespace std;

CPostAddress::CPostAddress()
{}

CPostAddress::CPostAddress(string const& city, string const& street,
	string const& building, string const& apartment)
	:m_city(city)
	,m_street(street)
	,m_building(building)
	,m_apartment(apartment)
{}

CPostAddress::CPostAddress(istream &in)
	:m_city(RawData::ReadString(in))
	,m_street(RawData::ReadString(in))
	,m_building(RawData::ReadString(in))
	,m_apartment(RawData::ReadString(in))
{}

void CPostAddress::WriteRawData(ostream &out) const
{
	RawData::WriteString(m_city, out);
	RawData::WriteString(m_street, out);
	RawData::WriteString(m_building, out);
	RawData::WriteString(m_apartment, out);
}

bool CPostAddress::Compare(CPostAddress const &other) const
{
	return (SameFields(m_city, other.m_city) &&
		SameFields(m_street, other.m_street) &&
		SameFields(m_building, other.m_building) &&
		SameFields(m_apartment, other.m_apartment));
}

bool CPostAddress::operator==(CPostAddress const &other) const
{
	return (m_city == other.m_city &&
		m_street == other.m_street &&
		m_building == other.m_building &&
		m_apartment == other.m_apartment);
}

void CPostAddress::Print(ostream &out) const
{
	PrintIfNotEmpty("City: ", m_city, out);
	PrintIfNotEmpty("Street: ", m_street, out);
	PrintIfNotEmpty("Building: ", m_building, out);
	PrintIfNotEmpty("Apartment: ", m_apartment, out);
}

bool CPostAddress::SameFields(string const& a, string const& b)
{
	return (a.empty() || b.empty() || CaseInsensitiveMatch(a, b));
}

void CPostAddress::PrintIfNotEmpty(std::string const& announce,
	std::string const& data, std::ostream &out)
{
	if (!data.empty())
	{
		out << announce << data << endl;
	}
}
