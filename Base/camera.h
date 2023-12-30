#pragma once
#include "geometry.h"

class Camera {

public:
    vec3 position; //����ϵλ��
    float yaw; //Z����ת
    float pitch; //Y����ת
    vec3 forward; //��ǰ����
    vec3 rightward; //��������
    vec3 upward; //��������
    int  sight_distance;     //�Ӿ�
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

