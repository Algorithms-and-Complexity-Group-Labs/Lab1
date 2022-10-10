#include "Matrix.h"


Matrix::Matrix(size_t rows_count, size_t columns_count)
	: _rows_count(rows_count), _columns_count(columns_count)
{
	_matrix = new double* [rows_count];
	for (size_t i = 0; i < rows_count; i++)
		_matrix[i] = new double[columns_count];
}

Matrix::Matrix(const Matrix& matr)
	: _rows_count(matr._rows_count), _columns_count(matr._columns_count)
{
	this->_matrix = new double* [_rows_count];
	for (size_t i = 0; i < _rows_count; i++)
	{
		_matrix[i] = new double[_columns_count];
		for (size_t j = 0; j < _columns_count; j++)
			this->_matrix[i][j] = matr._matrix[i][j];
	}
}

Matrix& Matrix::operator=(const Matrix& matr)	
{
	this->~Matrix();

	this->_rows_count = matr._rows_count;
	this->_columns_count = matr._columns_count;

	this->_matrix = new double* [_rows_count];
	for (size_t i = 0; i < _rows_count; i++)
	{
		_matrix[i] = new double[_columns_count];
		for (size_t j = 0; j < _columns_count; j++)
			_matrix[i][j] = matr._matrix[i][j];
	}

	return *this;
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < _rows_count; i++)
		delete[] _matrix[i];
	delete[] _matrix;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matr)
{
	for (int i = 0; i < matr._rows_count; i++)
	{
		os << std::endl;
		for (int j = 0; j < matr._columns_count; j++)
		{
			os << matr._matrix[i][j];
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& matr)
{
	for (int i = 0; i < matr._rows_count; i++)
	{
		for (int j = 0; j < matr._columns_count; j++)
		{
			is >> matr._matrix[i][j];
		}
	}
	return is;
}
