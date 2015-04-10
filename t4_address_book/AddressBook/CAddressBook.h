#pragma once

#include "ContactCollection.h"

class CAddressBook
{
public:
	CContactCollection& GetContactCollection();
	void LoadFromFile(const char fileName[]);
	void SaveToFile(const char fileName[]);

private:
	CContactCollection m_collection;
};
