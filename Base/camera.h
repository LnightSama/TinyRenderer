#pragma once
#include "geometry.h"

class Camera {

public:
    vec3 position; //坐标系位置
    float yaw; //Z轴旋转
    float pitch; //Y轴旋转
    vec3 forward; //向前向量
    vec3 rightward; //向右向量
    vec3 upward; //向上向量
    int  sight_distance;     //视距
    float velocity = 0.1;

    Camera(
        vec3 position = vec3(-50,0,0),
        float  yaw = 0,
        float  pitch = 0.0,
        int  sight_distance = 10
        ) : position(position), yaw(yaw), pitch(pitch),sight_distance(sight_distance) {
        set_coordinate_systems();
    }

    vec3 get_projection(vec3 v, bool isproject);
    void set_coordinate_systems();


    void revolve_yaw(float yaw);
    void revolve_pitch(float pitch);
};

