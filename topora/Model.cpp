#include "Model.h"
#include "UI.h"

Model::Model() {
	points.clear();
	points.push_back(Vector({ 0, 0, 0 }));
	points.push_back(Vector({ 1, 0, 0 }));
	points.push_back(Vector({ 1, 1, 0 }));
	points.push_back(Vector({ 0, 1, 0 }));
	points.push_back(Vector({ 0, 0, 1 }));
	points.push_back(Vector({ 1, 0, 1 }));
	points.push_back(Vector({ 1, 1, 1 }));
	points.push_back(Vector({ 0, 1, 1 }));

	edges = {
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},
		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4},
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7}
	};
}

void Model::renderAscii(Camera &camera, UI &ui) {
	for (auto edge : edges) {
		Vector p1 = points[edge.first];
		Vector p2 = points[edge.second];
		int x1 = p1[0], y1 = p1[1], z1 = p1[2];
		Vector p1p = camera.project(p1);

		int x2 = p2[0], y2 = p2[1], z2 = p2[2];
		Vector p2p = camera.project(p2);

		// printf("(%.2lf, %.2lf), (%.2lf, %.2lf)\n ", p1p[0], p1p[1], p2p[0], p2p[1]);

		if (p1p[0] == -1 && p1p[1] == -1) continue;
		if (p2p[0] == -1 && p2p[1] == -1) continue;

		ui.drawLine(p1p[0], p1p[1], p2p[0], p2p[1]);
	}
}

Model& Model::buildTO(int sliceNum, int edgeNum, std::vector<float> radius, int pointOffset, float angleOffset) {

	if (edgeNum < 2) { // invalid
		return *this;
	}

	points.clear();
	edges.clear();

	for (int i = 0; i < sliceNum; i++) {
		for (int j = 0; j < edgeNum; j++) {
			float angle = 2 * PI * j / edgeNum + ARC(angleOffset * i);
			points.push_back(Vector({
				radius[i] * (float)cos(angle),
				radius[i] * (float)sin(angle),
				(float)1.0 * i / sliceNum }));
			if (i == 0 || i == sliceNum - 1) {
				edges.push_back({ i * edgeNum + j, i * edgeNum + (j + 1) % edgeNum });
			}

			if (i > 0) {
				edges.push_back({ i * edgeNum + j, (i - 1) * edgeNum + (j + pointOffset) % edgeNum });
			}
		}
	}

}

Model& Model::buildPO(int xRange, int yRange, float x2Coef, float y2Coef, float xyCoef, float xCoef, float yCoef) {

	points.clear();
	edges.clear();

	for (int x = -xRange; x <= xRange; x++) {
		for (int y = -yRange; y <= yRange; y++) {
			points.push_back(Vector({
				x * x * x2Coef + y * y * y2Coef + x * y * xyCoef + x * xCoef + y * yCoef,
				(float)x,
				(float)y
				}));
		}
	}

	for (int x = -xRange; x <= xRange; x++) {
		for (int y = -yRange; y <= yRange; y++) {
			if (y < yRange) {
				edges.push_back({ (x + xRange) * (2 * yRange + 1) + y + yRange, (x + xRange) * (2 * yRange + 1) + y + yRange + 1 });
			}
			if (x < xRange) {
				edges.push_back({ (x + xRange) * (2 * yRange + 1) + y + yRange, (x + xRange + 1) * (2 * yRange + 1) + y + yRange });
			}
		}
	}


	return *this;
}

Model& Model::buildRA(int sliceNum, float sinCoef, int sinArg, float cosCoef, int cosArg, float base) {

	points.clear();
	edges.clear();

	for (int i = 0; i < sliceNum; i ++) {
		float angle = i * 360 / sliceNum;

		float len = cosCoef * cos(ARC(angle * cosArg)) + sinCoef * sin(ARC(angle * sinArg)) + base;

		points.push_back(Vector({
			len * (float)cos(ARC(angle)),
			len * (float)sin(ARC(angle)),
			0
		}));
		edges.push_back({ i, (i + 1) % sliceNum });
	}

	return *this;
}