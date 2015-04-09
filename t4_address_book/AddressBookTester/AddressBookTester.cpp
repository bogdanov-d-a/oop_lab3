// AddressBookTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AddressBook/Name.h"
#include "../AddressBook/PostAddress.h"

using namespace std;

bool NameAndStringMatch(string const& name, string const& str)
{
	CName nameObj(name);
	return nameObj.CompareWithString(str);
}

BOOST_AUTO_TEST_CASE(EmptyStringMatchesName)
{
	BOOST_CHECK(NameAndStringMatch("FirstName LastName Patronymic", ""));
}

BOOST_AUTO_TEST_CASE(OneMatchNameWord)
{
	CName name("FirstName LastName Patronymic");
	BOOST_CHECK(name.CompareWithString("FirstName"));
	BOOST_CHECK(name.CompareWithString("LastName"));
	BOOST_CHECK(name.CompareWithString("Patronymic"));
}

BOOST_AUTO_TEST_CASE(NameRedundantSpaces)
{
	BOOST_CHECK(NameAndStringMatch("FirstName  LastName Patronymic  ", "     FirstName    "));
}

BOOST_AUTO_TEST_CASE(SpecificationNames)
{
	CName name("Иванов Сергей Петрович");

	BOOST_CHECK(name.CompareWithString("Сергей иванов"));
	BOOST_CHECK(name.CompareWithString("Иванов Сергей"));
	BOOST_CHECK(name.CompareWithString("Сергей Петрович"));
	BOOST_CHECK(name.CompareWithString("Иванов ПетровиЧ"));
	BOOST_CHECK(name.CompareWithString("Иванов"));
	BOOST_CHECK(name.CompareWithString("Петрович"));
	BOOST_CHECK(name.CompareWithString("Сергей Петрович Иванов"));
	BOOST_CHECK(name.CompareWithString("Иванов Сергей Петрович"));

	BOOST_CHECK(!name.CompareWithString("Сергеев Иван Петрович"));
	BOOST_CHECK(!name.CompareWithString("Иванов Иван Петрович"));
	BOOST_CHECK(!name.CompareWithString("Иван"));
	BOOST_CHECK(!name.CompareWithString("Семён Семёныч Горбунков"));
}

BOOST_AUTO_TEST_CASE(EmptyPostAddressesAreSame)
{
	CPostAddress addr1;
	CPostAddress addr2;
	BOOST_CHECK(addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(SameFullPostAddresses)
{
	CPostAddress addr1("city", "street", "building", "apartment");
	CPostAddress addr2(addr1);
	BOOST_CHECK(addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(DifferentFullPostAddresses)
{
	CPostAddress addr1("city", "street", "building", "apartment");
	CPostAddress addr2("city2", "street", "building2", "apartment");
	BOOST_CHECK(!addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(SamePartialPostAddresses)
{
	CPostAddress addr1("city", "street", "building", "apartment");
	CPostAddress addr2("city", "street", "", "");
	BOOST_CHECK(addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(DifferentPartialPostAddresses)
{
	CPostAddress addr1("city", "street", "building", "apartment");
	CPostAddress addr2("city2", "street", "", "");
	BOOST_CHECK(!addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(TestPostAddressCaseInsensitivity)
{
	CPostAddress addr1("city", "street", "building", "apartment");
	CPostAddress addr2("City", "StrEEt", "BUildiNG", "aPARTment");
	BOOST_CHECK(addr1.Compare(addr2));
}

BOOST_AUTO_TEST_CASE(TestNameRawData)
{
	CName name("TestName");
	ostringstream rawDataOut;
	name.WriteRawData(rawDataOut);
	BOOST_CHECK_EQUAL(rawDataOut.str(), "8@TestName");

	istringstream rawDataIn(rawDataOut.str());
	CName name2(rawDataIn);
	BOOST_CHECK(name == name2);
}
