﻿#include "Matrix.h"

#include <cassert>
#include <algorithm>


Matrix::Matrix() : _columns_count(0), _rows_count(0), _matrix(nullptr) {}

Matrix::Matrix(size_t rows_count, size_t columns_count)
	: _rows_count(rows_count), _columns_count(columns_count)
{
	_matrix = Row::CreateRowArray(rows_count, columns_count);
}

Matrix::Matrix(const Matrix& source)
	: _rows_count(source._rows_count), _columns_count(source._columns_count)
{
	_matrix = Row::CreateRowArray(_rows_count);

	for (size_t i = 0; i < _rows_count; i++)
	{
		_matrix[i] = source._matrix[i];
	}
}

Row& Matrix::operator[](size_t index)
{
	//if (index < 0 || index >= _rows_count)
	//	throw std::out_of_range("Invalid row index: " + index);

	assert(index >= 0 && index < _rows_count);

	return _matrix[index];
}

const Row& Matrix::operator[](size_t index) const
{
	if (index < 0 || index >= _rows_count)
		throw std::out_of_range("Invalid row index: " + index);

	return _matrix[index];
}

Matrix& Matrix::operator=(const Matrix& cpy_from)
{
	this->~Matrix();

	this->_rows_count = cpy_from._rows_count;
	this->_columns_count = cpy_from._columns_count;

	this->_matrix = Row::CreateRowArray(_columns_count);

	for (size_t i = 0; i < _rows_count; i++)
	{
		this->_matrix[i] = cpy_from._matrix[i];
	}

	return *this;
}

Matrix Matrix::operator*(const Matrix& multiplier) const
{
	assert(_columns_count == multiplier._rows_count);

	Matrix temp(_rows_count, multiplier._columns_count);
	for (int i = 0; i < _rows_count; i++)
		for (int j = 0; j < multiplier._columns_count; j++) 
		{
			temp[i][j] = 0;
			for (int k = 0; k < _columns_count; k++)
				temp[i][j] += _matrix[i][k] * multiplier[k][j];
		}
	return temp;
}

Matrix& Matrix::operator*=(const Matrix& multiplier)
{
	assert(_columns_count == multiplier._rows_count);

	for (int i = 0; i < _rows_count; i++)
		for (int j = 0; j < multiplier._columns_count; j++)
		{
			double temp = 0;
			for (int k = 0; k < _columns_count; k++)
				temp += _matrix[i][k] * multiplier[k][j];
			this->_matrix[i][j] = temp;
		}
	return *this;
}

Matrix::~Matrix()
{
	//for (int i = 0; i < _rows_count; ++i)
	//	_matrix[i].~Row();

	delete[] _matrix;

	//delete[] reinterpret_cast<char*>(_matrix);
}

size_t Matrix::get_rows_count() const
{
	return this->_rows_count;
}

size_t Matrix::get_columns_count() const
{
	return this->_columns_count;
}

void Matrix::SetRandom(int scatter)
{
	for (int i = 0; i < _rows_count; i++) {
		for (int j = 0; j < _columns_count; j++) {
			_matrix[i][j] = 1 + rand() % scatter;
		}
	}
}

void Matrix::setToZero()
{
	for (int i = 0; i < _rows_count; i++) {
		for (int j = 0; j < _columns_count; j++) {
			_matrix[i][j] = 0;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Matrix& matr)
{
	for (int i = 0; i < matr._rows_count; i++)
	{
		os << std::endl;
		for (int j = 0; j < matr._columns_count; j++)
		{
			os << matr._matrix[i][j] << " ";
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

Row::Row() : _numbers_count(0), _numbers(nullptr) {}

Row::Row(size_t size) : _numbers_count(size)
{
	_numbers = new double[_numbers_count];
}

Row::Row(const Row& source) 
	: _numbers_count(source._numbers_count),
	  _numbers(new double[source._numbers_count])
{
	std::copy(source._numbers, source._numbers + _numbers_count, _numbers);
	// memcpy(_numbers, source._numbers, sizeof(double) * _numbers_count);
}

double& Row::operator[](size_t index)
{
	//if (index < 0 || index >= _numbers_count)
	//	throw std::out_of_range("Invalid column index: " + index);

	assert(index >= 0 && index < _numbers_count);
	
	return _numbers[index];
}

const double& Row::operator[](size_t index) const
{
	//if (index < 0 || index >= _numbers_count)
	//	throw std::out_of_range("Invalid column index: " + index);

	assert(index >= 0 && index < _numbers_count);

	return _numbers[index];
}

Row* Row::CreateRowArray(size_t count, size_t columns_count)
{
	
	Row* rows = new Row[count];

	if (columns_count)
		for (int i = 0; i < count; i++)
		{
			rows[i]._numbers_count = columns_count;
			rows[i]._numbers = new double[columns_count];
		}
	return rows;

	//// Виділення пам'яті без виклику дефолтного конструктора (при видаленні потребує кастингу в char*)
	//char* rows_memory = new char[sizeof(Row) * count];
	//Row* rows = reinterpret_cast<Row*>(rows_memory);

	//for (int i = 0; i < count; ++i)
	//	new(rows + i) Row(columns_count);

	//return rows;
}

Row& Row::operator=(const Row& cpy_from)
{
	this->~Row();

	new (this) Row(cpy_from._numbers_count);
	std::copy(cpy_from._numbers,
		cpy_from._numbers + _numbers_count, _numbers);

	//this->_numbers_count = cpy_from._numbers_count;
	//this->_numbers = new double[_numbers_count];
	//memcpy(_numbers, cpy_from._numbers, sizeof(double) * _numbers_count);

	return *this;
}

Row Row::operator+(const Row& term) const
{
	assert(this->_numbers_count == term._numbers_count);

	Row temp(_numbers_count);
	for (int i = 0; i < _numbers_count; i++)
		temp[i] = _numbers[i] + term[i];

	return temp;
}

Row Row::operator-(const Row& subtractor) const
{
	assert(this->_numbers_count == subtractor._numbers_count);

	Row temp(_numbers_count);
	for (int i = 0; i < _numbers_count; i++)
		temp[i] = _numbers[i] - subtractor[i];

	return temp;
}

Row Row::operator*(double multiplier) const
{
	Row temp(_numbers_count);
	for (int i = 0; i < _numbers_count; i++)
		temp[i] = _numbers[i] * multiplier;

	return temp;
}

Row Row::operator/(double divider) const
{
	assert(divider > kPrecision);

	Row temp(_numbers_count);
	for (int i = 0; i < _numbers_count; i++)
		temp[i] = _numbers[i] / divider;

	return temp;
}

Row& Row::operator+=(const Row& term)
{
	assert(this->_numbers_count == term._numbers_count);

	for (int i = 0; i < _numbers_count; i++)
		_numbers[i] += term[i];

	return *this;
}

Row& Row::operator-=(const Row& subtractor)
{
	assert(this->_numbers_count == subtractor._numbers_count);

	for (int i = 0; i < _numbers_count; i++)
		_numbers[i] -= subtractor[i];

	return *this;
}

Row& Row::operator*=(double multiplier)
{
	for (int i = 0; i < _numbers_count; i++)
		_numbers[i] *= multiplier;

	return *this;
}

Row& Row::operator/=(double divider)
{
	assert(divider > kPrecision);

	for (int i = 0; i < _numbers_count; i++)
		_numbers[i] /= divider;

	return *this;
}

Row::~Row()
{
	delete[] _numbers;
	_numbers_count = 0;
}