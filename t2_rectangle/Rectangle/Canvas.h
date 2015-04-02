#pragma once

#include "Matrix.h"

class CCanvas
{
public:
	typedef unsigned Size;
	typedef int Coord;

	CCanvas(Size width, Size height);
	Size GetWidth() const;
	Size GetHeight() const;
	void Clear(char code = ' ');
	void SetPixel(Coord x, Coord y, char code);
	char GetPixel(Coord x, Coord y) const;
	void Write(std::ostream &ostream) const;

private:
	CMatrix<char> m_data;

	static bool CharValid(unsigned char code);
};
