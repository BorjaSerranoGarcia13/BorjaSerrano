#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

// https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html

class Matrix3x3 {
public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(float value);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

	float m[9];
};


inline Matrix3x3::Matrix3x3() {
	m[0] = 0.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	m[4] = 0.0f;
	m[5] = 0.0f;
	m[6] = 0.0f;
	m[7] = 0.0f;
	m[8] = 0.0f;
}

inline Matrix3x3::Matrix3x3(float value) {
	m[0] = value;
	m[1] = value;
	m[2] = value;
	m[3] = value;
	m[4] = value;
	m[5] = value;
	m[6] = value;
	m[7] = value;
	m[8] = value;
}

inline Matrix3x3::Matrix3x3(float *values_array) {
	m[0] = values_array[0];
	m[1] = values_array[1];
	m[2] = values_array[2];
	m[3] = values_array[3];
	m[4] = values_array[4];
	m[5] = values_array[5];
	m[6] = values_array[6];
	m[7] = values_array[7];
	m[8] = values_array[8];
}

inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
	m[0] = a.x;
	m[1] = a.y;
	m[2] = a.z;
	m[3] = b.x;
	m[4] = b.y;
	m[5] = b.z;
	m[6] = c.x;
	m[7] = c.y;
	m[8] = c.z;
}

inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
	m[0] = copy.m[0];
	m[1] = copy.m[1];
	m[2] = copy.m[2];
	m[3] = copy.m[3];
	m[4] = copy.m[4];
	m[5] = copy.m[5];
	m[6] = copy.m[6];
	m[7] = copy.m[7];
	m[8] = copy.m[8];
}

inline Matrix3x3::~Matrix3x3() {

}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
	float tmp[9];
	tmp[0] = m[0] + other.m[0];
	tmp[1] = m[1] + other.m[1];
	tmp[2] = m[2] + other.m[2];
	tmp[3] = m[3] + other.m[3];
	tmp[4] = m[4] + other.m[4];
	tmp[5] = m[5] + other.m[5];
	tmp[6] = m[6] + other.m[6];
	tmp[7] = m[7] + other.m[7];
	tmp[8] = m[8] + other.m[8];
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
	float tmp[9];
	tmp[0] = m[0] + other.m[0];
	tmp[1] = m[1] + other.m[1];
	tmp[2] = m[2] + other.m[2];
	tmp[3] = m[3] + other.m[3];
	tmp[4] = m[4] + other.m[4];
	tmp[5] = m[5] + other.m[5];
	tmp[6] = m[6] + other.m[6];
	tmp[7] = m[7] + other.m[7];
	tmp[8] = m[8] + other.m[8];
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	float tmp[9];
	tmp[0] = m[0] + value;
	tmp[1] = m[1] + value;
	tmp[2] = m[2] + value;
	tmp[3] = m[3] + value;
	tmp[4] = m[4] + value;
	tmp[5] = m[5] + value;
	tmp[6] = m[6] + value;
	tmp[7] = m[7] + value;
	tmp[8] = m[8] + value;
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
	float tmp[9];
	tmp[0] = m[0] + value;
	tmp[1] = m[1] + value;
	tmp[2] = m[2] + value;
	tmp[3] = m[3] + value;
	tmp[4] = m[4] + value;
	tmp[5] = m[5] + value;
	tmp[6] = m[6] + value;
	tmp[7] = m[7] + value;
	tmp[8] = m[8] + value;
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	float tmp[9];
	tmp[0] = m[0] - other.m[0];
	tmp[1] = m[1] - other.m[1];
	tmp[2] = m[2] - other.m[2];
	tmp[3] = m[3] - other.m[3];
	tmp[4] = m[4] - other.m[4];
	tmp[5] = m[5] - other.m[5];
	tmp[6] = m[6] - other.m[6];
	tmp[7] = m[7] - other.m[7];
	tmp[8] = m[8] - other.m[8];
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
	float tmp[9];
	tmp[0] = m[0] - other.m[0];
	tmp[1] = m[1] - other.m[1];
	tmp[2] = m[2] - other.m[2];
	tmp[3] = m[3] - other.m[3];
	tmp[4] = m[4] - other.m[4];
	tmp[5] = m[5] - other.m[5];
	tmp[6] = m[6] - other.m[6];
	tmp[7] = m[7] - other.m[7];
	tmp[8] = m[8] - other.m[8];
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	float tmp[9];
	tmp[0] = m[0] - value;
	tmp[1] = m[1] - value;
	tmp[2] = m[2] - value;
	tmp[3] = m[3] - value;
	tmp[4] = m[4] - value;
	tmp[5] = m[5] - value;
	tmp[6] = m[6] - value;
	tmp[7] = m[7] - value;
	tmp[8] = m[8] - value;
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
	float tmp[9];
	tmp[0] = m[0] - value;
	tmp[1] = m[1] - value;
	tmp[2] = m[2] - value;
	tmp[3] = m[3] - value;
	tmp[4] = m[4] - value;
	tmp[5] = m[5] - value;
	tmp[6] = m[6] - value;
	tmp[7] = m[7] - value;
	tmp[8] = m[8] - value;
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	float tmp[9];
	tmp[0] = m[0] * value;
	tmp[1] = m[1] * value;
	tmp[2] = m[2] * value;
	tmp[3] = m[3] * value;
	tmp[4] = m[4] * value;
	tmp[5] = m[5] * value;
	tmp[6] = m[6] * value;
	tmp[7] = m[7] * value;
	tmp[8] = m[8] * value;
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator*=(float value) {
	float tmp[9];
	tmp[0] = m[0] * value;
	tmp[1] = m[1] * value;
	tmp[2] = m[2] * value;
	tmp[3] = m[3] * value;
	tmp[4] = m[4] * value;
	tmp[5] = m[5] * value;
	tmp[6] = m[6] * value;
	tmp[7] = m[7] * value;
	tmp[8] = m[8] * value;
	return Matrix3x3(tmp);
	
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	float tmp[9];
	tmp[0] = m[0] / value;
	tmp[1] = m[1] / value;
	tmp[2] = m[2] / value;
	tmp[3] = m[3] / value;
	tmp[4] = m[4] / value;
	tmp[5] = m[5] / value;
	tmp[6] = m[6] / value;
	tmp[7] = m[7] / value;
	tmp[8] = m[8] / value;
	return Matrix3x3(tmp);
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	float tmp[9];
	tmp[0] = m[0] / value;
	tmp[1] = m[1] / value;
	tmp[2] = m[2] / value;
	tmp[3] = m[3] / value;
	tmp[4] = m[4] / value;
	tmp[5] = m[5] / value;
	tmp[6] = m[6] / value;
	tmp[7] = m[7] / value;
	tmp[8] = m[8] / value;
	return Matrix3x3(tmp);
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	if (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2]
		&& m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5]
		&& m[6] == other.m[6] && m[7] == other.m[7] && m[8] == other.m[8]) {
		return true;
	}
	else {
		return false;
	}
}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	if (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2]
		&& m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5]
		&& m[6] == other.m[6] && m[7] == other.m[7] && m[8] == other.m[8]) {
		return false;
	}
	else {
		return true;
	}
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
	m[0] = other.m[0];
	m[1] = other.m[1];
	m[2] = other.m[2];
	m[3] = other.m[3];
	m[4] = other.m[4];
	m[5] = other.m[5];
	m[6] = other.m[6];
	m[7] = other.m[7];
	m[8] = other.m[8];
}

inline Matrix3x3 Matrix3x3::Identity(){
	float tmp[9];
	tmp[0] = 1.0f;
	tmp[1] = 0.0f;
	tmp[2] = 0.0f;

	tmp[3] = 0.0f;
	tmp[4] = 1.0f;
	tmp[5] = 0.0f;

	tmp[6] = 0.0f;
	tmp[7] = 0.0f;
	tmp[8] = 1.0f;

	return Matrix3x3(tmp);
}

inline float Matrix3x3::Determinant() const {
	float tmp = ((m[0] * m[4] * m[8]) + (m[3] * m[7] * m[2]) + (m[6] * m[1] * m[5])) -
		((m[3] * m[1] * m[8]) + (m[0] * m[7] * m[5]) + (m[6] * m[4] * m[2]));
	return tmp;
	
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	if (out.Determinant() == 0.0f)return false;
	 out.Adjoint().Transpose() / Determinant();
	return true;
}

inline bool Matrix3x3::Inverse() {	
	if (this->Determinant() == 0.0f)return false;
	*this = this->Adjoint().Transpose() / Determinant();
	return true;
}

inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {	
	float tmp[9];
	tmp[0] = 1.0f;
	tmp[1] = 0.0f;
	tmp[2] = mov_vector.x;
	tmp[3] = 0.0f;
	tmp[4] = 1.0f;
	tmp[5] = mov_vector.y;
	tmp[6] = 0.0f;
	tmp[7] = 0.0f;
	tmp[8] = 1.0f;
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	float tmp[9];
	tmp[0] = 1.0f;
	tmp[1] = 0.0f;
	tmp[2] = x;
	tmp[3] = 0.0f;
	tmp[4] = 1.0f;
	tmp[5] = y;
	tmp[6] = 0.0f;
	tmp[7] = 0.0f;
	tmp[8] = 1.0f;
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	float tmp[9];
	tmp[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
	tmp[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
	tmp[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];
	tmp[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
	tmp[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
	tmp[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];
	tmp[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
	tmp[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
	tmp[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];
	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	float tmp[9];
	tmp[0] = (m[4] * m[8] - (m[5] * m[7]));
	tmp[1] = -(m[3] * m[8] - (m[5] * m[6]));
	tmp[2] = (m[3] * m[7] - (m[4] * m[6]));
	tmp[3] = -(m[1] * m[8] - (m[2] * m[7]));
	tmp[4] = (m[0] * m[8] - (m[2] * m[6]));
	tmp[5] = -(m[0] * m[7] - (m[1] * m[6]));
	tmp[6] = (m[1] * m[5] - (m[2] * m[4]));
	tmp[7] = -(m[0] * m[8] - (m[2] * m[6]));
	tmp[8] = (m[0] * m[4] - (m[1] * m[3]));

	return Matrix3x3(tmp);
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	float tmp[9];
	tmp[0] = m[0];
	tmp[1] = m[3];
	tmp[2] = m[6];
	tmp[3] = m[1];
	tmp[4] = m[4];
	tmp[5] = m[7];
	tmp[6] = m[2];
	tmp[7] = m[5];
	tmp[8] = m[8];
	return Matrix3x3(tmp);
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	Vector3 tmp;
	switch (colum) {
	case 0: tmp.x = m[0]; tmp.y = m[3]; tmp.z = m[6]; break;
	case 1: tmp.x = m[1]; tmp.y = m[4]; tmp.z = m[7];  break;
	case 2: tmp.x = m[2]; tmp.y = m[5]; tmp.z = m[8];  break;
	}
	
	return Vector3(tmp);
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	Vector3 tmp;
	switch (line) {
	case 0: tmp.x = m[0]; tmp.y = m[1]; tmp.z = m[2]; break;
	case 1: tmp.x = m[3]; tmp.y = m[4]; tmp.z = m[5];  break;
	case 2: tmp.x = m[6]; tmp.y = m[7]; tmp.z = m[8];  break;
	}
	return Vector3(tmp);
}

#endif 