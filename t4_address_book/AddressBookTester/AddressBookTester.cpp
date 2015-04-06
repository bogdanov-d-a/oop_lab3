// AddressBookTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AddressBook/Name.h"

using namespace std;

bool NameAndStringMatch(string const& firstName, string const& lastName,
	string const& patronymic, string const& searchStr)
{
	CName name(firstName, lastName, patronymic);
	return name.CompareWithString(searchStr);
}

BOOST_AUTO_TEST_CASE(EmptyStringMatches)
{
	BOOST_CHECK(NameAndStringMatch("FirstName", "LastName", "Patronymic", ""));
}

BOOST_AUTO_TEST_CASE(OneMatchWord)
{
	CName name("FirstName", "LastName", "Patronymic");
	BOOST_CHECK(name.CompareWithString("FirstName"));
	BOOST_CHECK(name.CompareWithString("LastName"));
	BOOST_CHECK(name.CompareWithString("Patronymic"));
}

BOOST_AUTO_TEST_CASE(RedundantSpaces)
{
	BOOST_CHECK(NameAndStringMatch("FirstName", "LastName", "Patronymic", "     FirstName    "));
}

BOOST_AUTO_TEST_CASE(SpecificationExamples)
{
	CName name("������", "������", "��������");

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
