#pragma once
#include "tgaimage.h"
#include "geometry.h"

class Line {

private:
	int i = 0;

public:
	Line() = default;
	//TGAImage(const int i);

	void toTriangle(std::vector<vec3> vectors, TGAImage& image, TGAColor color);

	void cline(
		int x1, int y1,
		int x2, int y2,
		TGAImage& image, TGAColor color);

	void bline(
		int x1, int y1,
		int x2, int y2,
		TGAImage& image, TGAColor color);

	void aline(
		int x1, int y1,
		int x2, int y2,
		TGAImage& image, TGAColor color);

	void mline(
		int x1, int y1,
		int x2, int y2,
		TGAImage& image, TGAColor color);

};
