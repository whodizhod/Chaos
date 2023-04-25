#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"

template <typename T>
class Triangle {
public:
	Triangle();
	Triangle(Vec3<T> xx, Vec3<T> yy, Vec3<T> zz);

	Vec3<T> t0;
	Vec3<T> t1;
	Vec3<T> t2;
};
#endif