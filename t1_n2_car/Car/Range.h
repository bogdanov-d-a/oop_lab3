#pragma once

template <typename Type>
struct Range
{
	Type lb, rb;

	bool In(Type a) const
	{
		return (a >= lb && a <= rb);
	}
};
