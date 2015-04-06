// AddressBookTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AddressBook/Name.h"

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
	CName name("������ ������ ��������");

	BOOST_CHECK(name.CompareWithString("������ ������"));
	BOOST_CHECK(name.CompareWithString("������ ������"));
	BOOST_CHECK(name.CompareWithString("������ ��������"));
	BOOST_CHECK(name.CompareWithString("������ ��������"));
	BOOST_CHECK(name.CompareWithString("������"));
	BOOST_CHECK(name.CompareWithString("��������"));
	BOOST_CHECK(name.CompareWithString("������ �������� ������"));
	BOOST_CHECK(name.CompareWithString("������ ������ ��������"));

	BOOST_CHECK(!name.CompareWithString("������� ���� ��������"));
	BOOST_CHECK(!name.CompareWithString("������ ���� ��������"));
	BOOST_CHECK(!name.CompareWithString("����"));
	BOOST_CHECK(!name.CompareWithString("���� ������ ���������"));
}
