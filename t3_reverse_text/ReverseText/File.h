#pragma once

class CFile
{
public:
	static const int FILE_ERROR = -2;

	CFile();
	~CFile();
	bool Open(const char fileName[], const char mode[] = "r");
	void Close();
	bool IsOpened() const;
	bool IsEndOfFile() const;
	int GetChar();
	bool PutChar(char c);
	long int GetLength() const;
	bool Seek(long int offset);
	long int GetPosition() const;
	long int Write(const void * ptr, size_t size, size_t count);
	long int Read(void * ptr, size_t size, size_t count);

private:
	FILE *m_file;
};
