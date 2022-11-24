#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "vector_2.h"

class Matrix2x2 {
public:

	Matrix2x2();
	Matrix2x2(float a[4]);
	Matrix2x2(float value);
	Matrix2x2(const Vector2& a, const Vector2& b); 
	Matrix2x2(const Matrix2x2& copy);
	~Matrix2x2();
	Matrix2x2 Identity() const;
	Matrix2x2 Multiply(const Matrix2x2& other) const;
	float Determinant() const;
	Matrix2x2 Adjoint() const;
	Vector2 GetLine(int line) const;
	Vector2 GetColum(int line) const;

	Matrix2x2 Inverse() const;
	Matrix2x2 Transpose() const;

	inline Matrix2x2 operator+(const Matrix2x2& other) const;
	inline void operator+=(const Matrix2x2& other);
	inline Matrix2x2 operator+(float value) const;
	inline void operator+=(float value);
	inline Matrix2x2 operator-(const Matrix2x2& other) const;
	inline void operator-=(const Matrix2x2& other);
	inline Matrix2x2 operator-(float value) const;
	inline void operator-=(float value);

	inline Matrix2x2 operator*(float value) const;
	inline void operator*=(float value);
	inline Matrix2x2 operator/(float value) const;
	inline void operator/=(float value);

	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	inline void operator=(const Matrix2x2& other);

	float m[4];
};


inline Matrix2x2::Matrix2x2() {
	m[0] = 0.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
}

inline Matrix2x2::Matrix2x2(float a[4]) {
	m[0] = a[0];
	m[1] = a[1];
	m[2] = a[2];
	m[3] = a[3];
}

inline Matrix2x2::Matrix2x2(float a) {
	m[0] = a;
	m[1] = a;
	m[2] = a;
	m[3] = a;
}

inline Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	m[0] = a.x;
	m[1] = a.y;
	m[2] = b.x;
	m[3] = b.y;
}

inline Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	m[0] = copy.m[0];
	m[1] = copy.m[1];
	m[2] = copy.m[2];
	m[3] = copy.m[3];
}

inline Matrix2x2::~Matrix2x2() {
}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	float tmp[4];
	tmp[0] = m[0] + other.m[0];
	tmp[1] = m[1] + other.m[1];
	tmp[2] = m[2] + other.m[2];
	tmp[3] = m[3] + other.m[3];
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	m[0] += other.m[0];
	m[1] += other.m[1];
	m[2] += other.m[2];
	m[3] += other.m[3];
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	float tmp[4];
	tmp[0] = m[0] + value;
	tmp[1] = m[1] + value;
	tmp[2] = m[2] + value;
	tmp[3] = m[3] + value;
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator+=(float value) {
	m[0] += value;
	m[1] += value;
	m[2] += value;
	m[3] += value;
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	float tmp[4];
	tmp[0] = m[0] - other.m[0];
	tmp[1] = m[1] - other.m[1];
	tmp[2] = m[2] - other.m[2];
	tmp[3] = m[3] - other.m[3];
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	m[0] -= other.m[0];
	m[1] -= other.m[1];
	m[2] -= other.m[2];
	m[3] -= other.m[3];
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {	
	float tmp[4];
	tmp[0] = m[0] - value;
	tmp[1] = m[1] - value;
	tmp[2] = m[2] - value;
	tmp[3] = m[3] - value;
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator-=(float value) {
	m[0] -= value;
	m[1] -= value;
	m[2] -= value;
	m[3] -= value;
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	float tmp[4];
	tmp[0] = m[0] * value;
	tmp[1] = m[1] * value;
	tmp[2] = m[2] * value;
	tmp[3] = m[3] * value;
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator*=(float value) {
	m[0] *= value;
	m[1] *= value;
	m[2] *= value;
	m[3] *= value;
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	float tmp[4];
	tmp[0] /= value;
	tmp[1] /= value;
	tmp[2] /= value;
	tmp[3] /= value;
	return Matrix2x2(tmp);
}

inline void Matrix2x2::operator/=(float value) {
	m[0] /= value;
	m[1] /= value;
	m[2] /= value;
	m[3] /= value;
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const {
	return true;
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	return true;
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
}

inline Matrix2x2 Matrix2x2::Identity() const {
	return Matrix2x2();
}

inline float Matrix2x2::Determinant() const {
	return 0.0f;
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Adjoint() const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Transpose() const {
	return Matrix2x2();
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	return Vector2();
}

inline Vector2 Matrix2x2::GetColum(int line) const {	
	return Vector2();
}


#endif
