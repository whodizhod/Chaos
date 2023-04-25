#include "vec3.h"
#include "triangle.h"

template<typename T>
Triangle<T>::Triangle() = default;

template<typename T>
Triangle<T>::Triangle(Vec3<T> xx, Vec3<T> yy, Vec3<T> zz) : t0(xx), t1(yy), t2(zz) {}

// Explicit instantiation
template Triangle<float>::Triangle();
template Triangle<float>::Triangle(Vec3<float> xx, Vec3<float> yy, Vec3<float> zz);