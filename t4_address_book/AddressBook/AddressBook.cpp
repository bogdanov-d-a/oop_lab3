// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CAddressBook.h"

using namespace std;

string SetToString(set<string> const& s)
{
	string result;

	bool printedFirst = false;
	for (auto elem : s)
	{
		if (printedFirst)
		{
			result.push_back(' ');
		}

		result += elem;
		printedFirst = true;
	}

	return result;
}

void PrintSetIfNonempty(string const& announce, set<string> const& s)
{
	if (!s.empty())
	{
		cout << announce << SetToString(s) << endl;
	}
}

string ReadString()
{
	string result;

	if (!getline(cin, result))
	{
		return string();
	}

	return result;
}

int ReadInt(int errVal)
{
	try
	{
		return stoi(ReadString());
	}
	catch (invalid_argument const& e)
	{
		(void)e;
		return errVal;
	}
}

string PromptString(string const& prompt)
{
	cout << prompt;
	return ReadString();
}

CPostAddress PromptPostAddress()
{
	return CPostAddress(PromptString("Enter city: "),
		PromptString("Enter street: "),
		PromptString("Enter building: "),
		PromptString("Enter apartment: "));
}

void HandleSearchRequest(CContactCollection const& collection)
{
	cout << "Choose search criteria:" << endl;
	cout << "1. Name" << endl;
	cout << "2. Post address" << endl;
	cout << "3. Phone number" << endl;
	cout << "4. Email address" << endl;

	const int answer = ReadInt(0);
	CContactCollection::SearchResults searchResults;

	switch (answer)
	{
	case 1:
		searchResults = collection.SearchByName(PromptString("Enter name: "));
		break;

	case 2:
		searchResults = collection.SearchByPostAddress(PromptPostAddress());
		break;

	// finish this

	default:
		cout << "Wrong answer" << endl;
		return;
	}

	for (auto searchResult : searchResults)
	{
		cout << "ID: " << searchResult.ind << endl;

		auto const& data = *searchResult.it;
		cout << "Name: " << data.GetName() << endl;
		data.PrintPostAddress(cout);
		PrintSetIfNonempty("Phone numbers: ", data.GetPhoneNumbers());
		PrintSetIfNonempty("Email adresses: ", data.GetEmailAddresses());
	}
}

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

		const int answer = ReadInt(0);
		switch (answer)
		{
		case 1:
			HandleSearchRequest(collection);
			break;

		// finish this

		case 5:
			stopLoop = true;
			break;

		default:
			cout << "Wrong answer" << endl;
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
