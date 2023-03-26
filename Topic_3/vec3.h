template<typename T>
class Vec3
{
public:
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	explicit Vec3(const T& xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

	T x;
	T y;
	T z;
};

using Vec3f = Vec3<float>;