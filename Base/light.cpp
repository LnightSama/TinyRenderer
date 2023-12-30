#include "geometry.h"
#include "light.h"
using namespace std;

void Light::revolve_yaw(float yaw)
{
    this->yaw = yaw;
    direction = vec3(std::cos(yaw / 180.0 * acos(-1)), std::sin(yaw / 180.0 * acos(-1)), std::sin(pitch / 180.0 * acos(-1)));
}

void Light::revolve_pitch(float pitch)
{
    this->pitch = pitch;
    direction.z = std::sin(pitch / 180.0 * acos(-1));
}
