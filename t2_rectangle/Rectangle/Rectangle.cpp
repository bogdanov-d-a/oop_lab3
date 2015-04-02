// Rectangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CRectangle.h"
#include "Canvas.h"

using namespace std;

enum class CommandType { INIT, MOVE, SCALE, ERROR };

struct CommandFormat
{
	CommandType type;
	string prefix;
	size_t argCount;
};

struct Command
{
	CommandType type;
	vector<int> args;
};

vector<string> SplitString(string const& str, char delimiter, size_t partCount)
{
	assert(partCount > 0);

	vector<string> result;
	result.reserve(partCount);
	size_t startIndex = 0;

	while (result.size() < partCount && startIndex < str.length())
	{
		const size_t delimiterIndex = str.find(delimiter, startIndex);
		const bool delimiterFound = (delimiterIndex != string::npos);
		const size_t partLength = delimiterFound ? delimiterIndex - startIndex : string::npos;

		result.push_back(str.substr(startIndex, partLength));
		startIndex = delimiterFound ? delimiterIndex + 1 : string::npos;
	}

	return ((result.size() == partCount && startIndex == string::npos)
		? result
		: vector<string>());
}

vector<int> StrVectorToIntVector(vector<string> strVector)
{
	try
	{
		vector<int> result(strVector.size());

		transform(strVector.cbegin(), strVector.cend(),
			result.begin(), [](string const& str){ return stoi(str); });

		return result;
	}
	catch (invalid_argument const& e)
	{
		(void)e;
		return vector<int>();
	}
}

string GetCommandArgument(string const& str, string const& cmd)
{
	if (str.length() <= cmd.length())
	{
		return string();
	}

	if (str.substr(0, cmd.length()) != cmd)
	{
		return string();
	}

	return str.substr(cmd.length());
}

vector<int> TryParseCommand(string const& str, string const& cmd, size_t argCount)
{
	string argPart = GetCommandArgument(str, cmd);

	return (argPart.empty()
		? vector<int>()
		: StrVectorToIntVector(SplitString(argPart, ' ', argCount)));
}

Command ParseCommand(string const& str)
{
	static const vector<CommandFormat> cmdFormatList = {
		{ CommandType::INIT, "Rectangle ", 4 },
		{ CommandType::MOVE, "Move ", 2 },
		{ CommandType::SCALE, "Scale ", 2 }
	};

	for (auto const& cmdFormat : cmdFormatList)
	{
		Command result;
		result.args = TryParseCommand(str, cmdFormat.prefix, cmdFormat.argCount);
		if (!result.args.empty())
		{
			result.type = cmdFormat.type;
			return result;
		}
	}

	return { CommandType::ERROR, vector<int>() };
}

bool ApplyCommand(Command const& cmd, CRectangle &rect)
{
	switch (cmd.type)
	{
	case CommandType::INIT:
		rect.SetLeft(cmd.args[0]);
		rect.SetTop(cmd.args[1]);
		rect.SetWidth(cmd.args[2]);
		rect.SetHeight(cmd.args[3]);
		return true;

	case CommandType::MOVE:
		rect.Move(cmd.args[0], cmd.args[1]);
		return true;

	case CommandType::SCALE:
		rect.Scale(cmd.args[0], cmd.args[1]);
		return true;

	default:
		return false;
	}
}

bool ApplyCommand(string const& cmd, CRectangle &rect)
{
	return ApplyCommand(ParseCommand(cmd), rect);
}

CRectangle ReadFromStream(istream &stream)
{
	CRectangle rect(0, 0, 0, 0);

	string curCmd;
	while (getline(stream, curCmd))
	{
		ApplyCommand(curCmd, rect);
	}

	return rect;
}

void PrintRectangleData(CRectangle const& rect, string const& name)
{
	cout << name << ":\n";
	cout << "\tLeft top: (" << rect.GetLeft() << "; " << rect.GetTop() << ")\n";
	cout << "\tSize: " << rect.GetWidth() << " * " << rect.GetHeight() << "\n";
	cout << "\tRight bottom: (" << rect.GetRight() << "; " << rect.GetBottom() << ")\n";
	cout << "\tArea: " << rect.GetArea() << "\n";
	cout << "\tPerimeter: " << rect.GetPerimeter() << "\n";
}

void FillRectangle(CRectangle const& rect, char code, CCanvas &canvas)
{
	for (CRectangle::Coord x = rect.GetLeft(); x < rect.GetRight(); ++x)
	{
		for (CRectangle::Coord y = rect.GetTop(); y < rect.GetBottom(); ++y)
		{
			canvas.SetPixel(x, y, code);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3 && argc != 4)
	{
		assert(argc > 0);
		cout << "Usage: " << argv[0] << " <rectangle file 1> <rectangle file 2> [drawing file]\n";
		return 1;
	}

	CRectangle rect1 = ReadFromStream(ifstream(argv[1]));
	PrintRectangleData(rect1, "Rectangle 1");

	CRectangle rect2 = ReadFromStream(ifstream(argv[2]));
	PrintRectangleData(rect2, "Rectangle 2");

	CRectangle intersectedRect(rect1);
	intersectedRect.Intersect(rect2);
	PrintRectangleData(intersectedRect, "Intersection rectangle");

	CCanvas canvas(60, 20);
	FillRectangle(rect1, '+', canvas);
	FillRectangle(rect2, '-', canvas);
	FillRectangle(intersectedRect, '#', canvas);
	
	if (argc == 4)
	{
		canvas.Write(ofstream(argv[3]));
	}
	else
	{
		canvas.Write(cout);
	}

	return 0;
}
