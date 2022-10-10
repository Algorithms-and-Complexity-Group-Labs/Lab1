#pragma once

#include <iostream>


class Matrix
{
public:
	Matrix(size_t rows_count, size_t columns_count);
	Matrix(const Matrix&);

	Matrix& operator=(const Matrix&);
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::istream& operator >>(std::istream&, Matrix&);

	~Matrix();

private:
	double** _matrix;
	size_t _rows_count, _columns_count;
};