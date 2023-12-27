#ifndef CAMERAH
#define CAMERAH

#include "vector.h"
#include "ray.h"

class Camera
{
    public:
        __device__ Camera(vec3 lookfrom, vec3 lookat, vec3 up, float vfov, float aspect);

        __device__ ray getRay(float u, float v)
        { return ray(world_origin, camera_origin + u*horizontal + v*vertical - world_origin); }

        vec3 world_origin;
        vec3 camera_origin;
        vec3 horizontal;
        vec3 vertical;
};

__device__ Camera::Camera(vec3 lookfrom, vec3 lookat, vec3 up, float vfov, float aspect)
{
    float theta = vfov * M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    vec3 w = unit_vector(lookfrom - lookat);
    vec3 u = unit_vector(cross(up, w));
    vec3 v = cross(w, u);
    world_origin = lookfrom;
    camera_origin = lookfrom - half_width*u - half_height*v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
}

#endif
