#pragma once

namespace RawData
{
	const char STOP_CHAR = '@';
	size_t ReadSizeUntilStopChar(std::istream &in);

	void WriteString(std::string const& str, std::ostream &out);
	std::string ReadString(std::istream &in);

	void WriteStringSet(std::set<std::string> const& s, std::ostream &out);
	std::set<std::string> ReadStringSet(std::istream &in);
}
