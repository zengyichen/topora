#include "Camera.h"
#include <cmath>
#include <vector>

Camera::Camera() {
	innerMat = Matrix(3, 3);
	innerMat(0, 0) = 1;
	innerMat(1, 1) = 1;
	innerMat(2, 2) = 1;

	outerMat = Matrix(3, 4);
	outerMat(0, 0) = 1;
	outerMat(1, 1) = 1;
	outerMat(2, 2) = 1;
}

Camera& Camera::move(Vector v) {

	Matrix res = outerMat.partial(3, 3) * v;

	Matrix debug = outerMat.partial(3, 3);

	outerMat(0, 3) += v[0];
	outerMat(1, 3) += v[1];
	outerMat(2, 3) += v[2];

	return *this;
}

Camera& Camera::rotate(Vector v) {
	Matrix rotX(3, 3);
	rotX(0, 0) = 1;
	rotX(1, 1) = cos(v[0]);
	rotX(1, 2) = -sin(v[0]);
	rotX(2, 1) = sin(v[0]);
	rotX(2, 2) = cos(v[0]);

	Matrix rotY(3, 3);
	rotY(0, 0) = cos(v[1]);
	rotY(0, 2) = sin(v[1]);
	rotY(1, 1) = 1;
	rotY(2, 0) = -sin(v[1]);
	rotY(2, 2) = cos(v[1]);

	Matrix rotZ(3, 3);
	rotZ(0, 0) = cos(v[2]);
	rotZ(0, 1) = -sin(v[2]);
	rotZ(1, 0) = sin(v[2]);
	rotZ(1, 1) = cos(v[2]);
	rotZ(2, 2) = 1;

	Vector tmp(3);
	tmp[0] = outerMat(0, 3);
	tmp[1] = outerMat(1, 3);
	tmp[2] = outerMat(2, 3);

	outerMat = rotX * rotY * rotZ * outerMat;

	// 旋转后，平移的值不变
	outerMat(0, 3) = tmp[0];
	outerMat(1, 3) = tmp[1];
	outerMat(2, 3) = tmp[2];

	/*
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%.2lf ", outerMat(i, j));
		}
		puts("");
	}
	*/

	return *this;
}

Vector Camera::project(Vector v) const {
	float tmp[4] = {v[0], v[1], v[2], 1};
	Matrix res = innerMat * outerMat * Matrix(4, 1, tmp);

	if (res(2, 0) < 0.001) {
		return Vector({ -1, -1 }); // error
		//puts("err");
	}
	return Vector({res(0, 0) / res(2, 0), res(1, 0) / res(2, 0)});
}
