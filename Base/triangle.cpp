#include <iostream>
#include "triangle.h"
#include "tgaimage.h"
#include "geometry.h"
#include "model.h"
using namespace std;

void Triangle::tinting(std::vector<vec3> vectors, TGAImage& image, TGAColor color) {
	//                       Top,Bottom,        Right,left
	std::vector<int> area = { 0, image.height(), 0, image.width() };
	if (vectors.size() != 3) return;
	
	for (int i = 0; i < vectors.size(); i++) {

		vectors[i].x = (vectors[i].x + 1.) * image.width() / 2;
		vectors[i].y = (vectors[i].y + 1.) * image.height() / 2;

		if (area[0] < vectors[i].y) area[0] = vectors[i].y;
		if (area[1] > vectors[i].y) area[1] = vectors[i].y;
		if (area[2] < vectors[i].x) area[2] = vectors[i].x;
		if (area[3] > vectors[i].x) area[3] = vectors[i].x;

	}


	for (int y = area[1]; y <= area[0]; y++) {
		for (int x = area[3]; x <= area[2]; x++) {
			if (inside(vectors, x + 0.5, y + 0.5))
			{
				image.set(x, y, color);
			}
			
		}
	}
	
}

bool Triangle::inside(std::vector<vec3> vectors, double x, double y) {
	
	double direction[3] = { 0., 0. ,0. };
	for (int i = 0; i < 3; i++) {
		vec3 v0 = vectors[i];
		vec3 v1 = vectors[(i + 1) % 3];
		direction[i] = (y - v0.y) * (v1.x - v0.x) - (x - v0.x) * (v1.y - v0.y);
	}

	double i = std::abs(direction[0]) + std::abs(direction[1]) + std::abs(direction[2]);
	double j = std::abs(direction[0]  + direction[1] + direction[2]);
	
	if (i == j)
	{
		return true;
	}
	return false;
}

std::vector<int> Triangle::box(std::vector<vec3> vectors, int w, int h) {
	std::vector<int> area = { 0, h, 0, w };
	
	for (int i = 0; i < vectors.size(); i++) {

		if (area[0] < vectors[i].y) area[0] = vectors[i].y;
		if (area[1] > vectors[i].y) area[1] = vectors[i].y;
		if (area[2] < vectors[i].x) area[2] = vectors[i].x;
		if (area[3] > vectors[i].x) area[3] = vectors[i].x;
	}
	return area;
}