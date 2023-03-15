#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include <cmath>
#include <math_utils.h>

class Vector3 {

public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(float* values_array);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(float value) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(float value);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(float value) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(float value);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	void operator=(const Vector3& other);
	void operator=(float value);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};

inline Vector3::Vector3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

inline Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Vector3::Vector3(float *values_array) {
	x = values_array[0];
	y = values_array[1];
	z = values_array[2];
}

inline Vector3::Vector3(float value) {
	x = value;
	y = value;
	z = value;
}

inline Vector3::Vector3(const Vector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

inline Vector3::~Vector3() {}

inline float Vector3::Magnitude() const {
	return sqrt(SqrMagnitude());
}

inline void Vector3::Normalize() {	
	float num = Magnitude();
	x /= num;
	y /= num;
	z /= num;
}

inline Vector3 Vector3::Normalized() const {
	float num = Magnitude();
	return Vector3(x / num, y / num, z / num);
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& b)  {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3::Angle(const Vector3& a, const Vector3& b)  {
	float tmp = DotProduct(a, b);
	float tmp1 = a.Magnitude() * b.Magnitude();

	return acos (tmp / tmp1) ;
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)  {
	float Cx = a.y * b.z - a.z * b.y;
	float Cy = a.z * b.x - a.x * b.z;
	float Cz = a.x * b.y - a.y * b.x;
	 
	return Vector3(Cx,Cy,Cz);
}

inline float Vector3::SqrMagnitude() const {
	return x * x + y * y + z * z;
}

inline void Vector3::Scale(const Vector3& scale) {	
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	float clampedT = MathUtils::Clamp(t, 0, 1);
	return Vector3::LerpUnclamped(a, b, clampedT);
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	return Vector3((b.x - a.x) * t + a.x, (b.y - a.y) * t + a.y, (b.z - a.z) * t + a.z);
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	Vector3 tmp;
	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;
	return tmp.Magnitude();
}

inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {
	Vector3 temp = normal.Normalized();
	return Vector3(direction + (temp * -2.0f * DotProduct(direction, temp)));
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

inline Vector3 Vector3::operator+(float value) const {
	return Vector3(x + value, y + value, z + value);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

inline Vector3& Vector3::operator+=(float value) {
	x += value;
	y += value;
	z += value;
	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

inline Vector3 Vector3::operator-(float value) const {
	return Vector3(x - value, y - value, z - value);
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

inline Vector3& Vector3::operator-=(float value) {
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
	if (x == other.x && y == other.y && z == other.z){
		return true;
	}
	else return false;
}

inline bool Vector3::operator!=(const Vector3& other) const {
	if (x != other.x && y != other.y && z != other.z) {
		return true;
	}
	else return false;
}

inline void Vector3::operator=(const Vector3& other) {	
	x = other.x;
	y = other.y;
	z = other.z;
}

inline void Vector3::operator=(float value) {	
	x = value;
	y = value;
	z = value;
}

inline Vector3 Vector3::operator*(float value) const {
	
	return Vector3(x * value, y * value, z * value);
}

inline Vector3& Vector3::operator*=(float value) {	
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

inline Vector3 Vector3::operator/(float value) const {
	float valueInverse = 1 / value;
	return Vector3(x * valueInverse, y * valueInverse, z * valueInverse);
}

inline Vector3& Vector3::operator/=(float value) {	
	float valueInverse = 1 / value;
	x *= valueInverse;
	y *= valueInverse;
	z *= valueInverse;
	return *this;
}

#endif 
