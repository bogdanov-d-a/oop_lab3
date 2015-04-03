#include "stdafx.h"
#include "File.h"

CFile::CFile()
	:m_file(nullptr)
{}

CFile::~CFile()
{
	Close();
}

bool CFile::Open(const char fileName[], const char mode[])
{
	Close();
	
	if (fopen_s(&m_file, fileName, mode) != 0)
	{
		m_file = nullptr;
	}

	return IsOpened();
}

void CFile::Close()
{
	if (IsOpened())
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

bool CFile::IsOpened() const
{
	return (m_file != nullptr);
}

bool CFile::IsEndOfFile() const
{
	return (IsOpened() && feof(m_file));
}

int CFile::GetChar()
{
	if (!IsOpened())
	{
		return FILE_ERROR;
	}

	clearerr(m_file);

	const int curChar = getc(m_file);
	const bool hasError = (ferror(m_file) != 0);

	return (hasError ? FILE_ERROR : curChar);
}

bool CFile::PutChar(char c)
{
	return (IsOpened() && fputc(c, m_file) == c);
}

long int CFile::GetLength() const
{
	if (!IsOpened())
	{
		return -1;
	}

	const long int oldOffset = GetPosition();

	if (oldOffset == -1 || fseek(m_file, 0, SEEK_END) != 0)
	{
		return -1;
	}

	const long int endOffset = GetPosition();
	fseek(m_file, oldOffset, SEEK_SET);
	return endOffset;
}

bool CFile::Seek(long int offset)
{
	if (!IsOpened())
	{
		return false;
	}

	clearerr(m_file);

	const bool resultGood = (fseek(m_file, offset, SEEK_SET) == 0);
	const bool errorIndicatorSet = (ferror(m_file) != 0);

	return (!errorIndicatorSet && resultGood);
}

long int CFile::GetPosition() const
{
	return (IsOpened() ? ftell(m_file) : -1);
}

long int CFile::Write(const void * ptr, size_t size, size_t count)
{
	return (IsOpened() && (size * count <= LONG_MAX)
		? fwrite(ptr, size, count, m_file)
		: -1);
}

long int CFile::Read(void * ptr, size_t size, size_t count)
{
	return (IsOpened() && (size * count <= LONG_MAX)
		? fread(ptr, size, count, m_file)
		: -1);
}
