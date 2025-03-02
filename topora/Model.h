#ifndef MODEL_H
#define MODEL_H

#include "Vector.h"
#include "Camera.h"
#include "UI.h"
#include <vector>

#define PI (3.14159265)
#define ARC(x) ((x) * PI / 180)

enum ModelType {
	TO,
	PO,
	RA
};

class Model {
private:
	std::vector<Vector> points;
	std::vector<std::pair<int, int> > edges;
public:
	// cube
	Model();
	
	Model& buildTO(int sliceNum, int edgeNum, std::vector<float> radius, int pointOffset, float angleOffset);
	Model& buildPO(int xRange, int yRange, float x2Coef, float y2Coef, float xyCoef, float xCoef, float yCoef);
	Model& buildRA(int sliceNum, float sinRatio, int sinArg, float cosRatio, int cosArg, float base);

	void renderAscii(Camera &camera, UI &ui);
};

#endif
