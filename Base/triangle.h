#pragma once
#include <vector>
#include "tgaimage.h"
#include "geometry.h"

class Triangle {

private:
	int i = 0;

public:
	void tinting(std::vector<vec3> vectors, TGAImage& image, TGAColor color); // 着色

	bool inside(std::vector<vec3> vectors, double x, double y); //判断像素点是否在三角形面里

	std::vector<int> box(std::vector<vec3> vectors, int w, int h);


};
