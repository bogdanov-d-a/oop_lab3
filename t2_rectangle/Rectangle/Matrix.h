#pragma once

template <typename Value>
class CMatrix
{
public:
	CMatrix(size_t rows, size_t columns, Value const& defVal)
		:m_rows(rows)
		,m_columns(columns)
		,m_data(rows * columns, defVal)
	{}

	Value& operator()(size_t row, size_t column)
	{
		return m_data[GetCellIndex(row, column)];
	}

	Value const& operator()(size_t row, size_t column) const
	{
		return m_data[GetCellIndex(row, column)];
	}

	size_t GetRowCount() const
	{
		return m_rows;
	}

	size_t GetColumnCount() const
	{
		return m_columns;
	}

	void Clear(Value const& val)
	{
		m_data.clear();
		m_data.resize(m_rows * m_columns, val);
	}

	bool CheckCoords(size_t row, size_t column) const
	{
		return ((row < m_rows) && (column < m_columns));
	}

private:
	std::vector<Value> m_data;
	size_t m_rows, m_columns;

	size_t GetCellIndex(size_t row, size_t column) const
	{
		assert(CheckCoords(row, column));
		return (row * m_columns + column);
	}
};
