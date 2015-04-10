#include "stdafx.h"
#include "CAddressBook.h"

using namespace std;

CContactCollection& CAddressBook::GetContactCollection()
{
	return m_collection;
}

void CAddressBook::LoadFromFile(const char fileName[])
{
	ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		throw runtime_error("Can't open input file");
	}
	m_collection.ReadRawData(inFile);
}

void CAddressBook::SaveToFile(const char fileName[])
{
	ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		throw runtime_error("Can't open output file");
	}
	m_collection.WriteRawData(outFile);
}
