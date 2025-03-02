#pragma once

#include "Vector.h"
#include "Matrix.h"

// �˴��� K = I����Ϊ��׼���

class Camera {
private:
	Matrix innerMat, outerMat;
public:
	Camera();
	Camera& move(Vector v);
	Camera& rotate(Vector v);
	
	// ������v���������ϵ�µĶ�ά����
	// ���޷�ͶӰ�򷵻� (-1, -1)
	Vector project(Vector v) const;
};
