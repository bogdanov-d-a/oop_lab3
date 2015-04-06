#include "stdafx.h"
#include "StringUtils.h"

using namespace std;

typedef function<void(char)> SendCharFunction;
typedef function<void(string const&)> SendStringFunction;

const locale loc("rus_rus.866");

void FlushBuffer(string &buffer, SendStringFunction callback)
{
	if (!buffer.empty())
	{
		callback(buffer);
		buffer.clear();
	}
}

void SplitWords(istream &input, SendCharFunction whitespaceCallback, SendStringFunction wordCallback)
{
	string buffer;

	char curChar;
	while (input.get(curChar))
	{
		if (curChar == ' ')
		{
			FlushBuffer(buffer, wordCallback);
			whitespaceCallback(curChar);
		}
		else
		{
			buffer.push_back(curChar);
		}
	}

	FlushBuffer(buffer, wordCallback);
}

set<string> GetStringWords(string const& str)
{
	set<string> result;
	istringstream srcStream(str);

	SplitWords(srcStream, [](char c){},
		[&result](string const& str){ result.insert(str); });

	return result;
}

string ToLower(string const& str)
{
	string result;
	result.resize(str.length());
	transform(str.cbegin(), str.cend(), result.begin(), tolower);
	return result;
}

bool CaseInsensitiveMatch(string const& a, string const& b)
{
	return (ToLower(a) == ToLower(b));
}
