#include "stdafx.h"
#include "RawDataUtils.h"

using namespace std;

size_t RawData::ReadSizeUntilStopChar(istream &in)
{
	string result;

	char tmpChar;
	while (in.get(tmpChar))
	{
		result.push_back(tmpChar);

		if (tmpChar == STOP_CHAR)
		{
			break;
		}
	}

	if (result.back() != STOP_CHAR)
		throw runtime_error("No stop character found");

	result.pop_back();
	return stoul(result);
}

void RawData::WriteString(string const& str, ostream &out)
{
	out << str.length();
	out.put(STOP_CHAR);
	out << str;
}

string RawData::ReadString(istream &in)
{
	const size_t strLen = ReadSizeUntilStopChar(in);
	vector<char> result(strLen + 1, '\0');
	in.read(result.data(), strLen);
	return string(result.data());
}

void RawData::WriteStringSet(set<string> const& s, ostream &out)
{
	out << s.size();
	out.put(STOP_CHAR);

	for (auto setElem : s)
	{
		WriteString(setElem, out);
	}
}

set<string> RawData::ReadStringSet(istream &in)
{
	const size_t size = ReadSizeUntilStopChar(in);
	set<string> result;

	for (size_t i = 0; i < size; ++i)
	{
		result.insert(ReadString(in));
	}

	return result;
}
