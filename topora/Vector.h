#pragma once

#include <vector>

class Vector {
private:
	std::vector<float> data;
public:
	Vector();
	Vector(int n);
	Vector(const Vector& v);
	Vector(std::vector<float> data);
	~Vector();

	Vector& operator=(const Vector& v);
	float& operator[](int i);
	float operator[](int i) const;

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator*(float f) const;

	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(float f);

	int size() const;
};
