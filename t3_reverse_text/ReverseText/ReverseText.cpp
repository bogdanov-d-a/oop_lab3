// ReverseText.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "File.h"

using namespace std;

enum class ErrorType {
	SUCCESS,
	BAD_USAGE,
	INPUT_OPEN_ERROR,
	INPUT_GET_LENGTH_ERROR,
	OUTPUT_OPEN_ERROR,
	OUTPUT_WRITE_ERROR };

void ReverseVectorData(vector<char> &vector)
{
	for (size_t curSrc = 0; curSrc < vector.size() / 2; ++curSrc)
	{
		const size_t curTarg = (vector.size() - 1 - curSrc);
		assert(curSrc < curTarg);
		std::swap(vector[curSrc], vector[curTarg]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		assert(argc > 0);
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		return static_cast<int>(ErrorType::BAD_USAGE);
	}

	vector<char> data;

	{
		CFile inFile;
		if (!inFile.Open(argv[1]))
		{
			printf("Input file open error\n");
			return static_cast<int>(ErrorType::INPUT_OPEN_ERROR);
		}

		const long int maxInFileSize = inFile.GetLength();
		if (maxInFileSize == -1)
		{
			printf("Input file get length error\n");
			return static_cast<int>(ErrorType::INPUT_GET_LENGTH_ERROR);
		}

		data.resize(maxInFileSize);
		const long int inFileSize = inFile.Read(data.data(), sizeof(char), maxInFileSize);
		data.resize(inFileSize);
	}

	ReverseVectorData(data);

	CFile outFile;
	if (!outFile.Open(argv[2], "w"))
	{
		printf("Output file open error\n");
		return static_cast<int>(ErrorType::OUTPUT_OPEN_ERROR);
	}

	if (outFile.Write(data.data(), sizeof(char), data.size()) != sizeof(char) * data.size())
	{
		printf("Output file write error\n");
		return static_cast<int>(ErrorType::OUTPUT_WRITE_ERROR);
	}

	return static_cast<int>(ErrorType::SUCCESS);
}
