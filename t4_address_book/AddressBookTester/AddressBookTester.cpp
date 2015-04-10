// AddressBookTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AddressBook/Name.h"
#include "../AddressBook/PostAddress.h"
#include "../AddressBook/Contact.h"
#include "../AddressBook/ContactCollection.h"

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
	CName name1("TestName");
	ostringstream rawDataOut;
	name1.WriteRawData(rawDataOut);
	BOOST_CHECK_EQUAL(rawDataOut.str(), "8@TestName");

	istringstream rawDataIn(rawDataOut.str());
	CName name2(rawDataIn);
	BOOST_CHECK(name1 == name2);
}

BOOST_AUTO_TEST_CASE(TestPostAddressRawData)
{
	CPostAddress addr1("long city name", "street", "building", "apartment");
	ostringstream rawDataOut;
	addr1.WriteRawData(rawDataOut);
	BOOST_CHECK_EQUAL(rawDataOut.str(), "14@long city name6@street8@building9@apartment");

	istringstream rawDataIn(rawDataOut.str());
	CPostAddress addr2(rawDataIn);
	BOOST_CHECK(addr1 == addr2);
}

BOOST_AUTO_TEST_CASE(TestContactRawData)
{
	CContact contact1(CName("Some name"), CPostAddress("city", "street", "building", "apartment"));
	contact1.AddEmailAddress("some@email");
	contact1.AddEmailAddress("another@email");
	contact1.AddPhoneNumber("+12345678901");

	ostringstream rawDataOut;
	contact1.WriteRawData(rawDataOut);
	BOOST_CHECK_EQUAL(rawDataOut.str(),
		"9@Some name4@city6@street8@building9@apartment1@12@+123456789012@13@another@email10@some@email");

	istringstream rawDataIn(rawDataOut.str());
	CContact contact2(rawDataIn);
	BOOST_CHECK(contact1 == contact2);
}

BOOST_AUTO_TEST_CASE(TestContactCollectionRawData)
{
	CContactCollection col1;
	BOOST_CHECK(col1.AddContact(CContact(CName("1"), CPostAddress()))->MatchesByName("1"));
	BOOST_CHECK(col1.AddContact(CContact(CName("2"), CPostAddress()))->MatchesByName("2"));

	ostringstream rawDataOut;
	col1.WriteRawData(rawDataOut);
	BOOST_CHECK_EQUAL(rawDataOut.str(), "2@1@10@0@0@0@0@0@1@20@0@0@0@0@0@");

	istringstream rawDataIn(rawDataOut.str());
	CContactCollection col2;
	col2.ReadRawData(rawDataIn);
	BOOST_CHECK(col1 == col2);
}

BOOST_AUTO_TEST_CASE(TestContactCollectionEmailDuplicates)
{
	CContactCollection col;
	{
		CContact contact(CName("Name1"), CPostAddress());
		contact.AddEmailAddress("Common");
		contact.AddEmailAddress("Email1");
		col.AddContact(contact);
	}

	{
		CContact contact(CName("Name2"), CPostAddress());
		contact.AddEmailAddress("CoMMoN");
		contact.AddEmailAddress("Email2");

		bool exceptionCaught = false;
		try
		{
			col.AddContact(contact);
		}
		catch (runtime_error const& e)
		{
			(void)e;
			exceptionCaught = true;
		}
		BOOST_CHECK(exceptionCaught);
	}

	{
		CContact contact(CName("Name2"), CPostAddress());
		contact.AddEmailAddress("Email2");

		auto contactIter = col.AddContact(contact);
		col.EditContact(contactIter, contact);

		contact.AddEmailAddress("Common");

		bool exceptionCaught = false;
		try
		{
			col.EditContact(contactIter, contact);
		}
		catch (runtime_error const& e)
		{
			(void)e;
			exceptionCaught = true;
		}
		BOOST_CHECK(exceptionCaught);
	}
}
