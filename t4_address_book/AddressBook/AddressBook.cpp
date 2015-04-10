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

string PromptString(string const& prompt)
{
	cout << prompt;
	string result;
	getline(cin, result);
	return result;
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

	string line;
	if (!getline(cin, line))
	{
		return;
	}

	int answer;
	try
	{
		answer = stoi(line);
	}
	catch (invalid_argument const& e)
	{
		(void)e;
		cout << "Wrong answer format" << endl;
		return;
	}

	CContactCollection::SearchResults searchResults;

	switch (answer)
	{
	case 1:
	{
		cout << "Enter name: ";
		string name;
		if (!getline(cin, name))
		{
			return;
		}
		searchResults = collection.SearchByName(name);
		break;
	}

	case 2:
	{
		searchResults = collection.SearchByPostAddress(PromptPostAddress());
		break;
	}

	// finish this

	default:
		return;
	}

	for (auto searchResult : searchResults)
	{
		auto const& data = *searchResult.it;

		cout << "ID: " << searchResult.ind << endl;
		cout << "Name: " << data.GetName() << endl;
		data.PrintPostAddress(cout);

		set<string> const& phones = data.GetPhoneNumbers();
		if (!phones.empty())
		{
			cout << "Phone numbers: " << SetToString(phones) << endl;
		}

		set<string> const& emails = data.GetEmailAddresses();
		if (!emails.empty())
		{
			cout << "Email adresses: " << SetToString(emails) << endl;
		}
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
				case 1:
					HandleSearchRequest(collection);
					break;

				// finish this

				case 5:
					stopLoop = true;
					break;

				default:
					cout << "Number is out of range" << endl;
				}
			}
			catch (invalid_argument const& e)
			{
				(void)e;
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
