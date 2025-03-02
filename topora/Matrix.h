#pragma once

#include "Vector.h"

class Matrix {
	
	int rows, cols;
	float* data;

public:
	Matrix(int rows = 1, int cols = 1);
	Matrix(int rows, int cols, float* data);
	Matrix(const Matrix& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);
	float& operator()(int i, int j);
	float operator()(int i, int j) const;

	Matrix operator+(const Matrix& m) const;
	Matrix operator-(const Matrix& m) const;
	Matrix operator*(const Matrix& m) const;
	Matrix operator*(float f) const;

	Matrix operator*(const Vector& v) const;

	Matrix& operator+=(const Matrix& m);
	Matrix& operator-=(const Matrix& m);
	Matrix& operator*=(const Matrix& m);
	Matrix& operator*=(float f);

	Matrix partial(int row, int col) const;

	Matrix transpose() const;

	int getRows() const;
	int getCols() const;
	float* getData() const;
};
