#pragma once

class CRectangle
{
public:
	typedef int Size;
	typedef int Coord;

	CRectangle(Coord left, Coord top, Size width, Size height);

	Size GetWidth() const;
	Size GetHeight() const;
	Coord GetLeft() const;
	Coord GetTop() const;
	Coord GetRight() const;
	Coord GetBottom() const;

	void SetWidth(Size width);
	void SetHeight(Size height);
	void SetLeft(Coord left);
	void SetTop(Coord top);
	void SetRight(Coord right);
	void SetBottom(Coord bottom);

	Size GetArea() const;
	Size GetPerimeter() const;

	void Move(Coord dx, Coord dy);
	void Scale(int sx, int sy);
	bool Intersect(CRectangle const& other);

private:
	struct Range { Coord start, end; };

	Coord m_left;
	Coord m_top;
	Size m_width;
	Size m_height;

	static int BlockNegativeValue(int value);
	static bool IntersectRanges(Range const& a, Range const& b, Range &result);
	static Size GetRangeSize(Range const& a);

	Range GetHorisontalRange() const;
	Range GetVerticalRange() const;
	void ResetSize();
};
