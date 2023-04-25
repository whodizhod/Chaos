#include <iostream>
#include "triangle.h"
#include "vec3.h"

using Vec3_f = Vec3 <float>;
using Triangle_f = Triangle <float>;

int main() {

	Vec3_f A(1.0f, 1.0f, 1.0f);
	Vec3_f B(2.0f, 2.0f, 2.0f);
	Vec3_f C(3.0f, 3.0f, 3.0f);

	Triangle_f triangle(A,B,C);

	std::cout << "Vector 1: " << triangle.t0.x << " " << triangle.t0.y << " " << triangle.t0.z << " " << std::endl;
	std::cout << "Vector 2: " << triangle.t1.x << " " << triangle.t1.y << " " << triangle.t1.z << " " << std::endl;
	std::cout << "Vector 3: " << triangle.t2.x << " " << triangle.t2.y << " " << triangle.t2.z << " " << std::endl;

	return 0;
}