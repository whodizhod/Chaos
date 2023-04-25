#include <cmath>
#include "vec3.h"

using T = float;

// Length
template<typename T>
T Vec3<T>::getLength() {
	return sqrt(x * x + y * y + z * z);
}

template<typename T>
T getLength(const Vec3<T>& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Normal
template<typename T>
Vec3<T>& Vec3<T>::getNormal() {
	T length = getLength();
	if (length > 0) {
		T invLen = 1 / length;
		x *= invLen, y *= invLen, z *= invLen;
	}

	return *this;
}

template<typename T>
void getNormal(Vec3<T>& v) {
	T len = v.x * v.x + v.y * v.y + v.z * v.z;
	// Avoid division by 0
	if (len > 0) {
		T invLen = 1 / sqrt(len);
		v.x *= invLen, v.y *= invLen, v.z *= invLen;
	}
}

// Dot product
template<typename T>
T Vec3<T>::getDotProduct(const Vec3<T>& v) {
	return x * v.x + y * v.y + z * v.z;
}

template<typename T>
T getDotProduct(const Vec3<T>& a, const Vec3<T>& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product
template<typename T>
Vec3<T> Vec3<T>::getCrossProduct(const Vec3<T>& v) {
	return Vec3<T>(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

template<typename T>
Vec3<T> getCrossProduct(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3<T>(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

// Constructors
template<typename T>
Vec3<T>::Vec3() = default;

template<typename T>
Vec3<T>::Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

template<typename T>
Vec3<T>::Vec3(const T& xx) : x(xx), y(xx), z(xx) {}

// Operators
template<typename T>
Vec3<T> Vec3<T>::operator + (const Vec3<T>& v) {
	return Vec3<T>(x + v.x, y + v.y, z + v.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator - (const Vec3<T>& v) {
	return Vec3<T>(x - v.x, y - v.y, z - v.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator * (const T& r) {
	return Vec3<T>(x * r, y * r, z * r);
}

//Explicit instantiation
// Length_EI
template float Vec3<float>::getLength();
template float getLength(const Vec3<float>& v);

// Normal_EI
template Vec3<float>& Vec3<float>::getNormal();
template void getNormal(Vec3<float>& v);

// Dot product_EI
template float Vec3<float>::getDotProduct(const Vec3<float>& v);
template float getDotProduct(const Vec3<float>& a, const Vec3<float>& b);

// Cross product_EI
template Vec3<float> Vec3<float>::getCrossProduct(const Vec3<float>& v);
template Vec3<float> getCrossProduct(const Vec3<float>& a, const Vec3<float>& b);

// Constructors_EI
template Vec3<float>::Vec3();
template Vec3<float>::Vec3(float xx, float yy, float zz);
template Vec3<float>::Vec3(const float& xx);

// Operators_EI
template Vec3<float> Vec3<float>::operator + (const Vec3<float>& v);
template Vec3<float> Vec3<float>::operator - (const Vec3<float>& v);
template Vec3<float> Vec3<float>::operator * (const float& r);