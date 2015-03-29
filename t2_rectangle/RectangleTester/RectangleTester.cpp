// RectangleTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Rectangle/CRectangle.h"

bool CheckIntersection(CRectangle a, CRectangle const& b, bool willPass, CRectangle const& result)
{
	if (a.Intersect(b) != willPass)
	{
		return false;
	}

	return a == result;
}

BOOST_AUTO_TEST_CASE(BasicPropertiesAreWorking)
{
	CRectangle rect(20, -5, 30, 10);

	BOOST_CHECK_EQUAL(rect.GetLeft(), 20);
	BOOST_CHECK_EQUAL(rect.GetTop(), -5);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 30);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 10);
	BOOST_CHECK_EQUAL(rect.GetRight(), 50);
	BOOST_CHECK_EQUAL(rect.GetBottom(), 5);

	rect.SetLeft(-10);
	BOOST_CHECK_EQUAL(rect.GetLeft(), -10);

	rect.SetTop(30);
	BOOST_CHECK_EQUAL(rect.GetTop(), 30);

	rect.SetWidth(70);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 70);

	rect.SetHeight(40);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 40);

	BOOST_CHECK_EQUAL(rect.GetRight(), 60);
	BOOST_CHECK_EQUAL(rect.GetBottom(), 70);

	rect.SetRight(50);
	BOOST_CHECK_EQUAL(rect.GetRight(), 50);

	rect.SetBottom(80);
	BOOST_CHECK_EQUAL(rect.GetBottom(), 80);
}

BOOST_AUTO_TEST_CASE(NoNegativeSizes)
{
	CRectangle rect(20, -5, -30, -10);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 0);

	rect.SetWidth(1);
	rect.SetHeight(1);

	rect.SetWidth(-5);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 0);

	rect.SetHeight(-60);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
}

BOOST_AUTO_TEST_CASE(TestArea)
{
	CRectangle rect(20, -5, 30, 10);
	BOOST_CHECK_EQUAL(rect.GetArea(), 300);

	rect.SetHeight(0);
	BOOST_CHECK_EQUAL(rect.GetArea(), 0);
}

BOOST_AUTO_TEST_CASE(TestPerimeter)
{
	CRectangle rect(20, -5, 30, 10);
	BOOST_CHECK_EQUAL(rect.GetPerimeter(), 80);

	rect.SetWidth(0);
	BOOST_CHECK_EQUAL(rect.GetPerimeter(), 20);
}

BOOST_AUTO_TEST_CASE(TestMove)
{
	CRectangle rect(5, -15, 5, 20);
	rect.Move(-20, 40);

	BOOST_CHECK_EQUAL(rect.GetLeft(), -15);
	BOOST_CHECK_EQUAL(rect.GetRight(), -10);
	BOOST_CHECK_EQUAL(rect.GetTop(), 25);
	BOOST_CHECK_EQUAL(rect.GetBottom(), 45);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 5);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 20);
}

BOOST_AUTO_TEST_CASE(TestScale)
{
	CRectangle rect(5, -15, 5, 20);
	rect.Scale(5, 2);

	BOOST_CHECK_EQUAL(rect.GetLeft(), 5);
	BOOST_CHECK_EQUAL(rect.GetTop(), -15);
	BOOST_CHECK_EQUAL(rect.GetWidth(), 25);
	BOOST_CHECK_EQUAL(rect.GetHeight(), 40);
}

BOOST_AUTO_TEST_CASE(TestScaleWithNegatives)
{
	CRectangle rect1(5, -15, 5, 20);
	CRectangle rect2(rect1);

	rect1.Scale(-1 ,4);
	BOOST_CHECK(rect1 == rect2);

	rect1.Scale(5, -8);
	BOOST_CHECK(rect1 == rect2);

	rect1.Scale(-2, -1);
	BOOST_CHECK(rect1 == rect2);
}

BOOST_AUTO_TEST_CASE(TestIntersection)
{
	BOOST_CHECK(CheckIntersection(
		CRectangle(1, 1, 5, 5),
		CRectangle(3, 3, 5, 5),
		true,
		CRectangle(3, 3, 3, 3)
	));

	BOOST_CHECK(CheckIntersection(
		CRectangle(1, 1, 2, 2),
		CRectangle(3, 2, 2, 2),
		true,
		CRectangle(3, 2, 0, 1)
	));

	BOOST_CHECK(CheckIntersection(
		CRectangle(1, 1, 2, 2),
		CRectangle(3, 3, 2, 2),
		true,
		CRectangle(3, 3, 0, 0)
	));

	BOOST_CHECK(CheckIntersection(
		CRectangle(1, 1, 2, 2),
		CRectangle(5, 5, 2, 2),
		false,
		CRectangle(1, 1, 0, 0)
	));
}
