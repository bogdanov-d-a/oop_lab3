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
