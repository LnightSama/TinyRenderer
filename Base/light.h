#pragma once
#include "geometry.h"

class Light {

public:

    vec3 direction;
    float yaw; //Z轴旋转
    float pitch; //Y轴旋转
    vec3 position;
    double power;
    vec3 light_color;

    Light(
        vec3 position = vec3(-1, 0, 0),
        double power = 10,
        vec3 light_color = vec3(255, 255, 255)
    ) : position(position), power(power), light_color(light_color) {
        direction = vec3(std::cos(yaw / 180.0 * acos(-1)), std::sin(yaw / 180.0 * acos(-1)), std::sin(pitch / 180.0 * acos(-1)));
    }

    void revolve_yaw(float yaw);
    void revolve_pitch(float pitch);
};
