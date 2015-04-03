// ReverseTextTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ReverseText/File.h"

const char TMP_FILE_NAME[] = "tmp";
const char WRITE_TEST_BUF[] = "write data buffer";
#define WRITE_TEST_BUF_LENGTH (sizeof(WRITE_TEST_BUF) - 1)

struct FileFixture
{
	CFile file;
};

BOOST_FIXTURE_TEST_SUITE(File, FileFixture)

BOOST_AUTO_TEST_CASE(FileIsClosedByDefault)
{
	BOOST_CHECK(!file.IsOpened());
}

BOOST_AUTO_TEST_CASE(CheckOpenSuccess)
{
	BOOST_CHECK(file.Open("ReadMe.txt"));
	BOOST_CHECK(file.IsOpened());
}

BOOST_AUTO_TEST_CASE(CheckOpenError)
{
	BOOST_CHECK(!file.Open("nonexistentfile"));
	BOOST_CHECK(!file.IsOpened());
}

BOOST_AUTO_TEST_CASE(CanBeClosed)
{
	file.Open("ReadMe.txt");
	file.Close();
	BOOST_CHECK(!file.IsOpened());
}

BOOST_AUTO_TEST_CASE(CheckGetChar)
{
	file.Open("ReadMe.txt");
	BOOST_CHECK_EQUAL(file.GetChar(), '=');
	BOOST_CHECK_EQUAL(file.GetChar(), '=');
	BOOST_CHECK_EQUAL(file.GetChar(), '=');

	file.Open("ReverseTextTester.cpp");
	BOOST_CHECK_EQUAL(file.GetChar(), '/');
	BOOST_CHECK_EQUAL(file.GetChar(), '/');
	BOOST_CHECK_EQUAL(file.GetChar(), ' ');
}

BOOST_AUTO_TEST_CASE(CheckPutChar)
{
	const char TEST_CHAR = '@';

	BOOST_REQUIRE(file.Open(TMP_FILE_NAME, "w"));
	BOOST_CHECK(file.PutChar(TEST_CHAR));

	file.Open(TMP_FILE_NAME);
	BOOST_CHECK_EQUAL(file.GetChar(), TEST_CHAR);
}

BOOST_AUTO_TEST_CASE(CheckEOF)
{
	file.Open(TMP_FILE_NAME, "w");
	file.PutChar('%');

	file.Open(TMP_FILE_NAME);
	BOOST_CHECK(!file.IsEndOfFile());

	file.GetChar();
	BOOST_CHECK(!file.IsEndOfFile());

	BOOST_CHECK(file.GetChar() == EOF);
	BOOST_CHECK(file.IsEndOfFile());
}

BOOST_AUTO_TEST_CASE(CheckLength)
{
	file.Open("ReadMe.txt");
	BOOST_CHECK_EQUAL(file.GetLength(), 1785);
}

BOOST_AUTO_TEST_CASE(CheckGetPosition)
{
	file.Open("ReadMe.txt");
	while (file.GetChar() != '\n') {};
	BOOST_CHECK_EQUAL(file.GetPosition(), 74);
}

BOOST_AUTO_TEST_CASE(CheckSeek)
{
	file.Open("ReadMe.txt");
	BOOST_CHECK(file.Seek(78));
	BOOST_CHECK_EQUAL(file.GetPosition(), 78);

	BOOST_CHECK_EQUAL(file.GetChar(), 'C');
	BOOST_CHECK_EQUAL(file.GetChar(), 'O');
	BOOST_CHECK_EQUAL(file.GetChar(), 'N');
}

BOOST_AUTO_TEST_CASE(CheckReadAndWrite)
{
	file.Open(TMP_FILE_NAME, "w");
	BOOST_CHECK_EQUAL(
		file.Write(WRITE_TEST_BUF, sizeof(char), WRITE_TEST_BUF_LENGTH),
		sizeof(char) * WRITE_TEST_BUF_LENGTH);

	file.Open(TMP_FILE_NAME);
	char readBuf[WRITE_TEST_BUF_LENGTH];
	BOOST_CHECK_EQUAL(
		file.Read(readBuf, sizeof(char), WRITE_TEST_BUF_LENGTH),
		sizeof(char) * WRITE_TEST_BUF_LENGTH);
	BOOST_CHECK_EQUAL(memcmp(WRITE_TEST_BUF, readBuf, WRITE_TEST_BUF_LENGTH), 0);
}

BOOST_AUTO_TEST_SUITE_END()
