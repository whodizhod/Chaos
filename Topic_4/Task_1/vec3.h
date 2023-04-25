#ifndef VEC3_H
#define VEC3_H

template <typename T>
class Vec3 {
public:
	T getLength();
	Vec3<T>& getNormal();
	T getDotProduct(const Vec3<T>& v);
	Vec3<T> getCrossProduct(const Vec3<T>& v);

	Vec3<T> operator + (const Vec3<T>& v);
	Vec3<T> operator - (const Vec3<T>& v);
	Vec3<T> operator * (const T& r);

	Vec3();
	explicit Vec3(T xx, T yy, T zz);
	explicit Vec3(const T& xx);

	T x = 0;
	T y = 0;
	T z = 0;
};

template<typename T>
T getLength(const Vec3<T>& v);

template<typename T>
void getNormal(Vec3<T>& v);

template<typename T>
T getDotProduct(const Vec3<T>& a, const Vec3<T>& b);

template<typename T>
Vec3<T> getCrossProduct(const Vec3<T>& a, const Vec3<T>& b);
#endif