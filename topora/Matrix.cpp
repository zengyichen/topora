#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	data = new float[rows * cols];
	for (int i = 0; i < rows * cols; i++) {
		data[i] = 0;
	}
}

Matrix::Matrix(int rows, int cols, float* data) {
	this->rows = rows;
	this->cols = cols;
	this->data = new float[rows * cols];
	for (int i = 0; i < rows * cols; i++) {
		this->data[i] = data[i];
	}
}

Matrix::Matrix(const Matrix& m) {
	rows = m.rows;
	cols = m.cols;
	data = new float[rows * cols];
	for (int i = 0; i < rows * cols; i++) {
		data[i] = m.data[i];
	}
}

Matrix::~Matrix() {
	delete[] data;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (this != &m) {
		delete[] data;
		rows = m.rows;
		cols = m.cols;
		data = new float[rows * cols];
		for (int i = 0; i < rows * cols; i++) {
			data[i] = m.data[i];
		}
	}
	return *this;
}

float& Matrix::operator()(int i, int j) {
	return data[i * cols + j];
}

float Matrix::operator()(int i, int j) const {
	return data[i * cols + j];
}

Matrix Matrix::operator+(const Matrix& m) const {
	Matrix res(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		res.data[i] = data[i] + m.data[i];
	}
	return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
	Matrix res(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		res.data[i] = data[i] - m.data[i];
	}
	return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
	Matrix res(rows, m.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			res(i, j) = 0;
			for (int k = 0; k < cols; k++) {
				res(i, j) += data[i * cols + k] * m(k, j);
			}
		}
	}
	return res;
}

Matrix Matrix::operator*(float f) const {
	Matrix res(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		res.data[i] = data[i] * f;
	}
	return res;
}

Matrix Matrix::operator*(const Vector& v) const {
	Matrix res(rows, 1);
	for (int i = 0; i < rows; i++) {
		res(i, 0) = 0;
		for (int j = 0; j < cols; j++) {
			res(i, 0) += data[i * cols + j] * v[j];
		}
	}
	return res;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	for (int i = 0; i < rows * cols; i++) {
		data[i] += m.data[i];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	for (int i = 0; i < rows * cols; i++) {
		data[i] -= m.data[i];
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	*this = *this * m;
	return *this;
}

Matrix& Matrix::operator*=(float f) {
	for (int i = 0; i < rows * cols; i++) {
		data[i] *= f;
	}
	return *this;
}

Matrix Matrix::partial(int partitialRows, int partitialCols) const {
	Matrix res(partitialRows, partitialCols);
	for (int i = 0; i < partitialRows; i++) {
		for (int j = 0; j < partitialCols; j++) {
			res(i, j) = data[i * cols + j];
		}
	}
	return res;
}

Matrix Matrix::transpose() const {
	Matrix res(cols, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res(j, i) = data[i * cols + j];
		}
	}
	return res;
}

int Matrix::getRows() const {
	return rows;
}

int Matrix::getCols() const {
	return cols;
}

float* Matrix::getData() const {
	return data;
}
