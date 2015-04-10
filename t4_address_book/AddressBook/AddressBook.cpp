// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CAddressBook.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const char DB_FILENAME[] = "database.txt";

	CAddressBook addressBook;
	CContactCollection &collection = addressBook.GetContactCollection();

	try
	{
		addressBook.LoadFromFile(DB_FILENAME);
	}
	catch (runtime_error const& e)
	{
		(void)e;
		cout << "Database was not loaded; it will be created on save attempt." << endl;
	}

	bool stopLoop = false;
	do
	{
		cout << "Choose an action:" << endl;
		cout << "1. Search contact" << endl;
		cout << "2. Add contact" << endl;
		cout << "3. Edit contact" << endl;
		cout << "4. Remove contact" << endl;
		cout << "5. Quit" << endl;

		string curLine;
		if (!getline(cin, curLine))
		{
			stopLoop = true;
		}
		else
		{
			int answer;
			try
			{
				answer = stoi(curLine);

				switch (answer)
				{
				case 5:
					stopLoop = true;
					break;
				default:
					cout << "Number is out of range" << endl;
				}
			}
			catch (invalid_argument const& e)
			{
				cout << "Wrong answer format" << endl;
			}
		}
	}
	while (!stopLoop);

	if (collection.ChangedSinceLastRawDataReading())
	{
		cout << "Database has been modified. Enter Y or y to rewrite file before exit." << endl;

		char answer;
		cin >> answer;

		if (answer == 'Y' || answer == 'y')
		{
			try
			{
				addressBook.SaveToFile(DB_FILENAME);
			}
			catch (runtime_error const& e)
			{
				cout << e.what() << endl;
			}
		}
	}

	return 0;
}
