#include "stdafx.h"
#include "PostAddress.h"

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

bool CPostAddress::operator==(CPostAddress const &other) const
{
	return (SameFields(m_city, other.m_city) &&
		SameFields(m_street, other.m_street) &&
		SameFields(m_building, other.m_building) &&
		SameFields(m_apartment, other.m_apartment));
}

bool CPostAddress::operator!=(CPostAddress const &other) const
{
	return !(*this == other);
}

bool CPostAddress::SameFields(string const& a, string const& b)
{
	return (a.empty() || b.empty() || a == b);
}
