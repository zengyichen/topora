#include "Vector.h"

Vector::Vector() {
}

Vector::Vector(int n) {
	data.resize(n);
}

Vector::Vector(const Vector& v) {
	data = v.data;
}

Vector::Vector(std::vector<float> data) {
	this->data = data;
}

Vector::~Vector() {
}

Vector& Vector::operator=(const Vector& v) {
	if (this != &v) {
		data = v.data;
	}
	return *this;
}

float& Vector::operator[](int i) {
	return data[i];
}

float Vector::operator[](int i) const {
	return data[i];
}

Vector Vector::operator+(const Vector& v) const {
	Vector res(data.size());
	for (int i = 0; i < data.size(); i++) {
		res.data[i] = data[i] + v.data[i];
	}
	return res;
}

Vector Vector::operator-(const Vector& v) const {
	Vector res(data.size());
	for (int i = 0; i < data.size(); i++) {
		res.data[i] = data[i] - v.data[i];
	}
	return res;
}

Vector Vector::operator*(float f) const {
	Vector res(data.size());
	for (int i = 0; i < data.size(); i++) {
		res.data[i] = data[i] * f;
	}
	return res;
}

Vector& Vector::operator+=(const Vector& v) {
	for (int i = 0; i < data.size(); i++) {
		data[i] += v.data[i];
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	for (int i = 0; i < data.size(); i++) {
		data[i] -= v.data[i];
	}
	return *this;
}

Vector& Vector::operator*=(float f) {
	for (int i = 0; i < data.size(); i++) {
		data[i] *= f;
	}
	return *this;
}

int Vector::size() const {
	return data.size();
}
