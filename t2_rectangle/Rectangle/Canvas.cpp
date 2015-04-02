#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(Size width, Size height)
	:m_data(height, width, ' ')
{}

CCanvas::Size CCanvas::GetWidth() const
{
	return m_data.GetColumnCount();
}

CCanvas::Size CCanvas::GetHeight() const
{
	return m_data.GetRowCount();
}

void CCanvas::Clear(char code)
{
	if (CharValid(code))
	{
		m_data.Clear(code);
	}
}

void CCanvas::SetPixel(Coord x, Coord y, char code)
{
	if (m_data.CheckCoords(y, x) && CharValid(code))
	{
		m_data(y, x) = code;
	}
}

char CCanvas::GetPixel(Coord x, Coord y) const
{
	return (m_data.CheckCoords(y, x) ? m_data(y, x) : ' ');
}

void CCanvas::Write(std::ostream &ostream) const
{
	for (size_t row = 0; row < m_data.GetRowCount(); ++row)
	{
		for (size_t column = 0; column < m_data.GetColumnCount(); ++column)
		{
			ostream << m_data(row, column);
		}
		ostream << "\n";
	}
}

bool CCanvas::CharValid(unsigned char code)
{
	return (code >= ' ');
}
