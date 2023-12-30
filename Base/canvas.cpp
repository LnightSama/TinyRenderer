#include <iostream>
#include "tgaimage.h"
#include "homework.h"
#include <time.h>
using namespace std;

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor black = TGAColor(0, 0, 0, 255);

int main() {
	//std::vector<int> temps;
	//temps[4] = 3;
	//for (int i = 0;i < nums.size();i++) {
	//	std::cout << temps[4] << std::endl;
	//	
	//}
	//Solution solution;
	//std::cout << solution.longestPalindrome("babad") << std::endl;
	clock_t start = clock();
	Homework::test_homework();
	clock_t finish = clock();
	double duration = (double)(finish - start);

	///////////////////////////////////////
	printf("Time collapsed: %f s\n", duration / 1000);
	//Texture texture("obj/20220523180628.tga");
	////std::cout << texture.width << " " << texture.height << std::endl;
	//TGAImage image(700, 700, TGAImage::RGB);
	//for (int i = 0; i < 700; i++) {
	//	for (int j = 0; j < 700; j++) {
	//		TGAColor color = texture.bilinear_interpolation(i / 700.0, j / 700.0);
	//		//std::cout << static_cast<unsigned int>(color[2]) << " ";
	//		//std::cout << static_cast<unsigned int>(color[1]) << " ";
	//		//std::cout << static_cast<unsigned int>(color[0]) << " ";
	//		//std::cout << std::endl;
	//		image.set(i, j, color);

	//	}
	//}
	//image.flip_horizontally();
	////image.flip_vertically();
	//image.write_tga_file("output/lesson05.tga");
	return 0;
}

//int main4() {
//	//Camera camera(vec3(1, -1, -1), 1080, 1080, 1000);
//	//cout << "���������ǰ������" << camera.forward << endl;
//	//cout << "�����������������" << camera.rightward << endl;
//	//cout << "�����������������" << camera.upward << endl;
//	//cout << endl;
//	//cout << "�������������ϵ�����꣺" << camera.position << endl;
//	//vec3 v = vec3(3, 2, 1);//��������ϵĳ��
//	//vec3 v1 = vec3((v - camera.position) * camera.rightward, (v - camera.position) * camera.upward, (v - camera.position) * camera.forward);
//	//cout << "ĳ������������ϵ�µ����꣺" << v << endl;
//	//cout << "�仯��ĳ�����������ϵ�µ����꣺" << v1 << endl;
//	//cout << endl;
//	//vec3 origin = vec3(0, 0, 0);//��������ϵԭ��
//	//origin = vec3((origin - camera.position) * camera.rightward, (origin - camera.position) * camera.upward, (origin - camera.position) * camera.forward);
//	//cout << "�仯��ԭ�����������ϵ�µ����꣺" << origin << endl;
//	//vec3 v2 = vec3((v1 - origin) * vec3(1, 0, 0), (v1 - origin) * vec3(1, 0, 0), (v1 - origin) * vec3(0, 0, 1));
//	////Homework::first_homework();
//	//cout << "�仯��ĳ������������ϵ�µ����꣺" << v2 << endl;
//
//	Camera camera(vec3(1, -1, -1), 1080, 1080, 1000);
//	cout << "���������ǰ������" << camera.forward << endl;
//	cout << "�����������������" << camera.rightward << endl;
//	cout << "�����������������" << camera.upward << endl;
//	cout << endl;
//	cout << "�������������ϵ�����꣺" << camera.position << endl;
//
//	vec3 v = vec3(3, 2, 1);//��������ϵĳ��
//
//	vec3 v1 = vec3(v * camera.rightward, v * camera.upward, v * camera.forward);
//	v1 = v1 + camera.position;
//
//	cout << "ĳ������������ϵ�µ����꣺" << v << endl;
//	cout << "�仯��ĳ�����������ϵ�µ����꣺" << v1 << endl;
//	cout << endl;
//
//	vec3 origin = vec3(0, 0, 0);//��������ϵԭ��
//	origin = origin + camera.position;
//
//	cout << "�仯��ԭ�����������ϵ�µ����꣺" << origin << endl;
//
//	vec3 v2 = vec3(v1 * vec3(1, 0, 0), v1 * vec3(0, 1, 0), v1 * vec3(0, 0, 1));
//	v2 = v2 + (camera.position);
//	//Homework::first_homework();
//	cout << "�仯��ĳ������������ϵ�µ����꣺" << v2 << endl;
//	return 0;
//}
//
//int main3() {
//	int width = 1024;
//	int height = 1024;
//	std::vector<std::vector<vec4>> depth(width, std::vector<vec4>(height, vec4(0,0,0,INT_MIN)));
//	//ͼ��
//	TGAImage image(width, height, TGAImage::RGB);
//	//����
//	Line line;
//	//����
//	Light light(vec3(1, 0, 0), 0., white, depth);
//	//���
//	Camera camera(vec3(0, 1, 1), image.width(), image.height(), 1000);
//	// ʵ����ģ��
//	Model* model = new Model("obj/models/spot/spot_triangulated_good.obj");
//	Texture texture("obj/models/spot/hmap.jpg");
//	// ѭ��ģ���������������
//	for (int i = 0; i < model->nfaces(); i++) {
//		//std::vector<int> face = model->face(i);
//		std::vector<vec3> vectors = {
//			model->vert(i, 0),
//			model->vert(i, 1),
//			model->vert(i, 2),
//			model->normal(i, 0),
//			model->normal(i, 1),
//			model->normal(i, 2)
//		};
//		std::vector<vec2> colors = {
//			model->uv(i, 0),
//			model->uv(i, 1),
//			model->uv(i, 2)
//		};
//		//
//		//vectors = camera.rotation_formula(vectors);
//		//double length = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
//
//		//cout << normal << endl;
//		//cout << static_cast<unsigned int>(color.bgra[2]) << " " << static_cast<unsigned int>(color.bgra[1]) << " " << static_cast<unsigned int>(color.bgra[0]) << " " << static_cast<unsigned int>(color.bgra[3]) << endl;
//
//		light.tinting(vectors, colors, image, camera, texture);
//		//line.toTriangle(vectors, image, color);
//
//		//triangle.tinting(vectors, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
//	}
//	
//	//image.set(100, 126, red);
//	//image.flip_vertically();
//	image.write_tga_file("output/lesson06.tga");
//	return 0;
//}
//
//int main2() {
//	int width = 1024;
//	int height = 1024;
//
//	TGAImage image(width, height, TGAImage::RGB);
//	Line line;
//
//	// ʵ����ģ��
//	Model *model = new Model("obj/item1.obj");
//
//	// ѭ��ģ���������������
//	for (int i = 0; i < model->nfaces(); i++) {
//		std::vector<int> face = model->face(i);
//
//		// ѭ���������������㣬ÿ����������һ����
//		for (int j = 0; j < 3; j++) {
//			vec3 v0 = model->vert(face[j]);
//			vec3 v1 = model->vert(face[(j + 1) % 3]);
//
//			// ��Ϊģ�Ϳռ�ȡֵ��Χ�� [-1, 1]^3������Ҫ��ģ������ƽ�Ƶ���Ļ������
//			// ���� (point + 1) * width(height) / 2 �Ĳ���ѧ��Ϊ�ӿڱ任��Viewport Transformation��
//			int x0 = (v0.x + 1.) * width / 2.;
//			int y0 = (v0.y + 1.) * height / 2.;
//			int x1 = (v1.x + 1.) * width / 2.;
//			int y1 = (v1.y + 1.) * height / 2.;
//
//			// ����
//			line.aline(x0, y0, x1, y1, image, white);
//		}
//	}
//	//image.flip_vertically();
//	image.write_tga_file("output.tga");
//	return 0;
//}
//
//int main1() {
//	TGAImage image(1000, 1000, TGAImage::RGB);
//	Line line;
//	//image.set(52, 41, red);
//	//std::vector<std::uint8_t>::const_iterator it;
//	//int i = 0;
//	//for (it = image.data.begin(); it != image.data.end(); it++)
//	//{
//	//	cout << "��ӡ�ˣ�" << *it << "������" << i++ << endl;
//	//	return 0;
//	//}
//	int a[8][4] = {
//		{0, 0, 1000, 1000 },
//			{0, 500, 1000, 500 },
//			{500, 0, 500, 1000 },
//			{1000, 0, 0, 1000 },
//			{0, 750, 1000, 250 },
//			{0, 250, 1000, 750 },
//			{750, 0, 250, 1000 },
//			{250, 0, 750, 1000 },
//	};
//	for (int x = 0; x < 8; x++)
//	{
//		line.aline(a[x][0], a[x][1], a[x][2], a[x][3], image, white);
//	}
//	image.flip_vertically();
//	image.write_tga_file("output/lesson00.tga");
//	
//	return 0;
//}

