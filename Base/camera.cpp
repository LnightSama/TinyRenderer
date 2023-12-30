#include "camera.h"
#include "geometry.h"
using namespace std;

vec3 Camera::get_projection(vec3 v, bool isproject) {
    vec3 ret = v - position;
    double x = isproject ? sight_distance : forward * ret;
    return vec3((rightward * (ret * sight_distance / x)), (upward * (ret * sight_distance / x)), (forward * ret));
}

void Camera::set_coordinate_systems()
{
    forward = vec3(std::cos(yaw / 180.0 * acos(-1)), std::sin(yaw / 180.0 * acos(-1)), std::sin(pitch / 180.0 * acos(-1)));
    rightward = vec3(std::cos((yaw + 90) / 180.0 * acos(-1)), std::sin((yaw + 90) / 180.0 * acos(-1)), 0);
    upward = cross(forward, rightward).normalize();
}

void Camera::revolve_yaw(float yaw)
{
    this->yaw = yaw;
    set_coordinate_systems();
}

void Camera::revolve_pitch(float pitch)
{
    if(pitch >= -90 && pitch <= 90) this->pitch = pitch;
    set_coordinate_systems();
}
