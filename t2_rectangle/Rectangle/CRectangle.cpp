#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(Coord left, Coord top, Size width, Size height):
	m_left(left),
	m_top(top),
	m_width(BlockNegativeValue(width)),
	m_height(BlockNegativeValue(height))
{}

CRectangle::Size CRectangle::GetWidth() const
{
	return m_width;
}

CRectangle::Size CRectangle::GetHeight() const
{
	return m_height;
}

CRectangle::Coord CRectangle::GetLeft() const
{
	return m_left;
}

CRectangle::Coord CRectangle::GetTop() const
{
	return m_top;
}

CRectangle::Coord CRectangle::GetRight() const
{
	return m_left + m_width;
}

CRectangle::Coord CRectangle::GetBottom() const
{
	return m_top + m_height;
}

void CRectangle::SetWidth(Size width)
{
	m_width = BlockNegativeValue(width);
}

void CRectangle::SetHeight(Size height)
{
	m_height = BlockNegativeValue(height);
}

void CRectangle::SetLeft(Coord left)
{
	m_left = left;
}

void CRectangle::SetTop(Coord top)
{
	m_top = top;
}

void CRectangle::SetRight(Coord right)
{
	const Size grow = right - GetRight();
	SetWidth(m_width + grow);
}

void CRectangle::SetBottom(Coord bottom)
{
	const Size grow = bottom - GetBottom();
	SetHeight(m_height + grow);
}

CRectangle::Size CRectangle::GetArea() const
{
	return m_width * m_height;
}

CRectangle::Size CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

void CRectangle::Move(Coord dx, Coord dy)
{
	m_left += dx;
	m_top += dy;
}

void CRectangle::Scale(int sx, int sy)
{
	if (sx >= 0 && sy >= 0)
	{
		m_width *= sx;
		m_height *= sy;
	}
}

bool CRectangle::Intersect(CRectangle const& other)
{
	Range commonHorisontalRange;
	if (!IntersectRanges(GetHorisontalRange(), other.GetHorisontalRange(), commonHorisontalRange))
	{
		ResetSize();
		return false;
	}

	Range commonVerticalRange;
	if (!IntersectRanges(GetVerticalRange(), other.GetVerticalRange(), commonVerticalRange))
	{
		ResetSize();
		return false;
	}

	m_left = commonHorisontalRange.start;
	m_width = GetRangeSize(commonHorisontalRange);
	m_top = commonVerticalRange.start;
	m_height = GetRangeSize(commonVerticalRange);
	return true;
}

int CRectangle::BlockNegativeValue(int value)
{
	return ((value < 0) ? 0 : value);
}

bool CRectangle::IntersectRanges(Range const& a, Range const& b, Range &result)
{
	result.start = std::max<Coord>(a.start, b.start);
	result.end = std::min<Coord>(a.end, b.end);
	return (result.start <= result.end);
}

CRectangle::Size CRectangle::GetRangeSize(Range const& a)
{
	return a.end - a.start;
}

CRectangle::Range CRectangle::GetHorisontalRange() const
{
	return { m_left, GetRight() };
}

CRectangle::Range CRectangle::GetVerticalRange() const
{
	return { m_top, GetBottom() };
}

void CRectangle::ResetSize()
{
	m_width = 0;
	m_height = 0;
}
