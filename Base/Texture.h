#pragma once
#include "tgaimage.h"
#include "geometry.h"

class Texture {
private:
	TGAImage image;

public:
	Texture(const std::string& name)
	{
		image = TGAImage(200, 200, TGAImage::RGB);
		if (image.read_tga_file(name))
		{
			width = image.width();
			height = image.height();
		}
	}

	int width, height;

	vec3 getColor(float u, float v)
	{
		TGAColor c = image.get(u * image.width(), v * image.height());
		//auto u_img = u * width;
		//auto v_img = (1 - v) * height;
		//TGAColor c = image.get(v_img, u_img);
		return vec3{ (double)c[2],(double)c[1],(double)c[0] } / 255.;
	}

	TGAColor bilinear_interpolation(float u, float v)
	{
		float u_img = u * width;
		float v_img = (1 - v) * height;
		int u0 = u_img;
		int v0 = v_img;
		vec2 u1 = vec2(u0, v0);
		vec2 u2 = u1;
		vec2 u3 = u1;
		vec2 u4 = u1;
		
		if (u_img - u1.x < 0.0f)
		{
			std::cout << u << " " << v << std::endl;
			u2.x -= 1;
			u4.x -= 1;
		}
		else {
			u2.x += 1;
			u4.x += 1;
		}
		if (v_img - u1.y < 0.0f)
		{
			std::cout << u << " " << v << std::endl;
			u3.y -= 1;
			u4.y -= 1;
		}
		else {
			u3.y += 1;
			u4.y += 1;
		}
		//std::cout << u1 << " ";
		//std::cout << u2 << " ";
		//std::cout << u3 << " ";
		//std::cout << u4 << " ";
		//std::cout << std::endl;
		std::vector<TGAColor> colors = {
			image.get(u1.y, u1.x),
			image.get(u2.y, u2.x),
			image.get(u3.y, u3.x),
			image.get(u4.y, u4.x)
		};
		float x = abs(u_img - u0);
		float y = abs(v_img - v0);
		//std::cout << x << " " << y << std::endl;
		TGAColor a = colors[0] * (1.0 - x) + colors[1] * x;
		TGAColor b = colors[2] * (1.0 - x) + colors[3] * x;
		return a * (1.0 - y) + b * y;
	}

	vec3 get_normal_map(float u, float v) {
		TGAColor color = bilinear_interpolation(u, v);
		int x = static_cast<unsigned int>(color[2]);
		int y = static_cast<unsigned int>(color[1]);
		int z = static_cast<unsigned int>(color[0]);
	}


};