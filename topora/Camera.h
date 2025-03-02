#pragma once

#include "Vector.h"
#include "Matrix.h"

// 此处令 K = I，即为标准相机

class Camera {
private:
	Matrix innerMat, outerMat;
public:
	Camera();
	Camera& move(Vector v);
	Camera& rotate(Vector v);
	
	// 求向量v在相机坐标系下的二维坐标
	// 若无法投影则返回 (-1, -1)
	Vector project(Vector v) const;
};
