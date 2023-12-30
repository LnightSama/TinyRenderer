#include <iostream>
#include "line.h"


//Line::Line(const int i) : i(i) {}

void Line::toTriangle(std::vector<vec3> vectors, TGAImage& image, TGAColor color) {
	for (int j = 0; j < 3; j++) {
		vec3 v0 = vectors[j];
		vec3 v1 = vectors[(j + 1) % 3];

		// 因为模型空间取值范围是 [-1, 1]^3，我们要把模型坐标平移到屏幕坐标中
		// 下面 (point + 1) * width(height) / 2 的操作学名为视口变换（Viewport Transformation）
		int x0 = (v0.x + 1.) * image.width() / 2.;
		int y0 = (v0.y + 1.) * image.height() / 2.;
		int x1 = (v1.x + 1.) * image.width() / 2.;
		int y1 = (v1.y + 1.) * image.height() / 2.;

		// 画线
		aline(x0, y0, x1, y1, image, color);
	}
}

void Line::cline(
	int x1, int y1,
	int x2, int y2,
	TGAImage& image, TGAColor color) {
	const float dl = 0.01;
	int dx = x2 - x1;
	int dy = y2 - y1;
	for (float t = 0.0; t < 1.0; t += dl) {
		int x = x1 + dx * t;
		int y = y1 + dy * t;
		image.set(x, y, color);
	}
}

void Line::bline(
	int x1, int y1,
	int x2, int y2,
	TGAImage& image, TGAColor color) {
	float x = x1;
	float y = y1;
	float step = std::abs(x2 - x1);
	float dlx = (x2 - x1) / step;
	float dly = (y2 - y1) / step;

	for (int i = 1; i < step; i++) {
		image.set(x, y, color);
		x = x + dlx;
		y = y + dly;
	}
}

void Line::aline(
	int x1, int y1,
	int x2, int y2,
	TGAImage& image, TGAColor color) {
	float x = x1;
	float y = y1;
	int dx = x2 - x1;
	int dy = y2 - y1;
	float step;
	float dlx, dly;

	// 根据 dx 和 dy 的长度决定基准
	if (std::abs(dx) >= std::abs(dy)) {
		step = std::abs(dx);
	}
	else {
		step = std::abs(dy);
	}

	dlx = dx / step;
	dly = dy / step;

	for (int i = 1; i < step; i++) {
		image.set(x, y, color);
		x = x + dlx;
		y = y + dly;
	}
}

void Line::mline(
	int x1, int y1,
	int x2, int y2,
	TGAImage& image, TGAColor color) {

	float k = (y1 - y2) / (x1 - x2);

	float b = y1 - k * x1;

}
