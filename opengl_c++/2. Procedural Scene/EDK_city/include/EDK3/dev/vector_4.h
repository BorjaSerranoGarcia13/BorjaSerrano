#ifndef __Vector4_H__
#define __Vector4_H__ 1

#include "vector_3.h"
#include "matrix_3.h"

class Vector4 {
public:

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 a, float w);
	Vector4(float a);
	Vector4(float* values_array);
	Vector4(const Vector4& other);
	~Vector4();
	
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator+(float value) const;
	void operator+=(const Vector4& other);
	void operator+=(float value);
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator-(float value) const;
	void operator -=(const Vector4& other);
	void operator -=(float value);

	Vector4 operator*(float value) const;
	void operator*=(float value);
	Vector4 operator/(float value) const;
	void operator/=(float value);
	bool operator==(const Vector4& other);
	bool operator!=(const Vector4& other);
	void operator=(const Vector4& other);

	float Magnitude() const;
	void Normalize();
	Vector4 Normalized() const;
	void Scale(Vector4 scale);
	float SqrMagnitude() const;

	static float Distance(const Vector4& a, const Vector4& b);
	static float DotProduct(Vector4 a, Vector4 b);
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float index);	

	static const Vector4 one;
	static const Vector4 zero;

	float x;
	float y;
	float z;
	float w;

};

inline Vector4::Vector4() { 
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

inline Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline Vector4::Vector4(Vector3 a, float w) {
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = w;
}

inline Vector4::Vector4(float a) {
	this->x = a;
	this->y = a;
	this->z = a;
	this->w = a;
}

inline Vector4::Vector4(float* values_array) {
	x = values_array[0];
	y = values_array[1];
	z = values_array[2];
	w = values_array[3];
}

inline Vector4::Vector4(const Vector4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

inline Vector4::~Vector4() { }

inline float Vector4::Magnitude() const{
	return sqrt(x * x + y * y + z * z + w * w);
}

inline void Vector4::Normalize() {
	float num = sqrt(x * x + y * y + z * z + w * w);
	x /= num;
	y /= num;
	z /= num;
	w /= num;
}

inline Vector4 Vector4::Normalized() const {
	float num = sqrt(x * x + y * y + z * z + w * w);
	return Vector4(x / num, y / num, z / num, w / num);
}

inline void Vector4::Scale(Vector4 scale) {	
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	w *= scale.w;
}

inline float Vector4::SqrMagnitude() const {
	return x * x + y * y + z * z + w * w;
}

inline float Vector4::Distance(const Vector4& a, const Vector4& b) {
	Vector4 tmp;
	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;
	tmp.w = a.w - b.w;
	return sqrt(tmp.x * tmp.x + tmp.y *tmp.y + tmp.z * tmp.z + tmp.w * tmp.w);
}

inline float Vector4::DotProduct(Vector4 a, Vector4 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t) {	
	return Vector4(Vector3((b.x - a.x) * MathUtils::Clamp(t, 0, 1) + a.x,
		(b.y - a.y) * MathUtils::Clamp(t, 0, 1) + a.y,
		(b.z - a.z) * MathUtils::Clamp(t, 0, 1) + a.z),
		(b.w - a.w) * MathUtils::Clamp(t, 0, 1) + a.w);
}

inline Vector4 Vector4::operator+(const Vector4& other) const{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

inline Vector4 Vector4::operator+(float value) const{
	return Vector4(x + value, y + value, z + value, w + value);
}

inline void Vector4::operator+=(const Vector4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
}

inline void Vector4::operator+=(float value) {
	x += value;
	y += value;
	z += value;
	w += value;
}

inline Vector4 Vector4::operator-(const Vector4& other) const{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

inline Vector4 Vector4::operator-(float value) const{
	return Vector4(x - value, y - value, z - value, w - value);
}

inline void Vector4::operator -=(const Vector4& other) {	
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
}

inline void Vector4::operator -=(float value) {
	x -= value;
	y -= value;
	z -= value;
	w -= value;
}

inline Vector4 Vector4::operator*(float value) const{
	return Vector4(x * value, y * value, z * value, w * value);
}

inline void Vector4::operator*=(float value) {
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

inline Vector4 Vector4::operator/(float value) const{
	return Vector4(x / value, y / value, z / value, w / value);
}

inline void Vector4::operator/=(float value) {
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

inline bool Vector4::operator==(const Vector4& other) {
	if (x == other.x && y == other.y && z == other.z && w == other.w) {
		return true;
	}
	else return false;
}
inline bool Vector4::operator!=(const Vector4& other) {
	if (x != other.x && y != other.y && z != other.z && w != other.w) {
		return true;
	}
	else return false;

}
inline void Vector4::operator=(const Vector4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

#endif 
